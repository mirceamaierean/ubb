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
  Reservation? reservationToDelete;

  void _showDeleteConfirmationDialog(Reservation reservation) {
    setState(() {
      reservationToDelete = reservation;
    });

    showDialog(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Confirm Deletion'),
          content:
              const Text('Are you sure you want to delete this reservation?'),
          actions: [
            TextButton(
              onPressed: () {
                Navigator.of(context).pop();
              },
              child: const Text('Cancel'),
            ),
            TextButton(
              onPressed: () {
                if (reservationToDelete != null) {
                  final reservationRepository =
                      Provider.of<ReservationRepository>(context,
                          listen: false);
                  ReservationController.deleteReservation(
                    id: reservationToDelete!.id,
                    repository: reservationRepository,
                  );
                  setState(() {
                    reservationToDelete = null;
                  });
                }
                Navigator.of(context).pop();
              },
              style: TextButton.styleFrom(foregroundColor: Colors.red),
              child: const Text('Delete'),
            ),
          ],
        );
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    final reservationRepository = Provider.of<ReservationRepository>(context);
    final carRepository = Provider.of<CarRepository>(context);

    return Scaffold(
      appBar: AppBar(
        title: const Text('All Rentals'),
      ),
      body: ListView.builder(
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
              _showDeleteConfirmationDialog(reservation);
              return false;
            },
            child: ListTile(
              title: Text(
                '${car.make} ${car.model}',
                style:
                    TextStyle(fontWeight: FontWeight.bold, color: Colors.black),
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
    );
  }

  String _formatDate(DateTime date) {
    return '${date.month}/${date.day}/${date.year}';
  }
}
