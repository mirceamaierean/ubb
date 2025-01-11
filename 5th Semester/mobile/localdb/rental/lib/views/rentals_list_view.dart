import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:rental/controller/reservation_controller.dart';
import 'package:rental/repository/car_repository.dart';
import 'package:rental/repository/reservation_repository.dart';
import '../models/reservation.dart';
import 'edit_rental_view.dart';

class RentalsListView extends StatefulWidget {
  const RentalsListView({super.key});

  @override
  RentalsListViewState createState() => RentalsListViewState();
}

class RentalsListViewState extends State<RentalsListView> {
  bool isLoading = false;

  Future<void> _showDeleteConfirmationDialog(
      Reservation reservation, ReservationRepository repository) async {
    final bool shouldDelete = await showDialog(
          context: context,
          builder: (context) {
            return AlertDialog(
              title: const Text('Confirm Deletion'),
              content: const Text(
                  'Are you sure you want to delete this reservation?'),
              actions: [
                TextButton(
                  onPressed: () => Navigator.of(context).pop(false),
                  child: const Text('Cancel'),
                ),
                TextButton(
                  onPressed: () => Navigator.of(context).pop(true),
                  style: TextButton.styleFrom(foregroundColor: Colors.red),
                  child: const Text('Delete'),
                ),
              ],
            );
          },
        ) ??
        false;

    if (shouldDelete) {
      await _deleteReservation(reservation, repository);
    }
  }

  Future<void> _deleteReservation(
      Reservation reservation, ReservationRepository repository) async {
    setState(() {
      isLoading = true;
    });

    try {
      await ReservationController.deleteReservation(
        id: reservation.id,
        repository: repository,
      );

      if (mounted) {
        await showDialog(
          context: context,
          builder: (context) => AlertDialog(
            title: const Text('Delete Successful'),
            content:
                const Text('The reservation has been successfully deleted.'),
            actions: [
              TextButton(
                onPressed: () => Navigator.of(context).pop(),
                child: const Text('OK'),
              ),
            ],
          ),
        );
      }
    } catch (error) {
      if (mounted) {
        await showDialog(
          context: context,
          builder: (context) => AlertDialog(
            title: const Text('Delete Failed'),
            content: Text(
              'Failed to delete the reservation. This is on our end. Try again later!',
              style: const TextStyle(color: Colors.red),
            ),
            actions: [
              TextButton(
                onPressed: () => Navigator.of(context).pop(),
                child: const Text('OK'),
              ),
            ],
          ),
        );
      }
    } finally {
      if (mounted) {
        setState(() {
          isLoading = false;
        });
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    final reservationRepository = Provider.of<ReservationRepository>(context);
    final carRepository = Provider.of<CarRepository>(context);

    return Scaffold(
      appBar: AppBar(
        title: const Text('All Rentals'),
      ),
      body: Stack(
        children: [
          ListView.builder(
            itemCount: reservationRepository.reservations.length,
            itemBuilder: (context, index) {
              final reservation = reservationRepository.reservations[index];
              final car = carRepository.getCarById(reservation.carId);

              return Dismissible(
                key: Key(reservation.id),
                direction: DismissDirection.endToStart,
                background: Container(
                  alignment: Alignment.centerRight,
                  padding: const EdgeInsets.symmetric(horizontal: 20.0),
                  color: Colors.red,
                  child: const Icon(Icons.delete, color: Colors.white),
                ),
                confirmDismiss: (direction) async {
                  await _showDeleteConfirmationDialog(
                      reservation, reservationRepository);
                  return false; // Prevent auto-dismiss after swipe
                },
                child: ListTile(
                  title: Text(
                    '${car.make} ${car.model}',
                    style: const TextStyle(
                        fontWeight: FontWeight.bold, color: Colors.black),
                  ),
                  subtitle: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text('Total Price: \$${reservation.totalPrice}'),
                      Text('Start: ${_formatDate(reservation.startDate)}'),
                      Text('End: ${_formatDate(reservation.endDate)}'),
                    ],
                  ),
                  onTap: () {
                    Navigator.of(context).push(
                      MaterialPageRoute(
                        builder: (context) =>
                            EditRentalView(reservation: reservation),
                      ),
                    );
                  },
                ),
              );
            },
          ),
          if (isLoading)
            const Center(
              child: CircularProgressIndicator(),
            ),
        ],
      ),
    );
  }

  String _formatDate(DateTime date) {
    return '${date.month}/${date.day}/${date.year}';
  }
}
