import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../controller/reservation_controller.dart';
import '../repository/car_repository.dart';
import '../repository/reservation_repository.dart';
import '../models/reservation.dart';

class EditRentalView extends StatefulWidget {
  final Reservation reservation;

  const EditRentalView({
    required this.reservation,
    super.key,
  });

  @override
  EditRentalViewState createState() => EditRentalViewState();
}

class EditRentalViewState extends State<EditRentalView> {
  late DateTime startDate;
  late DateTime endDate;
  bool isLoading = false;

  @override
  void initState() {
    super.initState();
    startDate = widget.reservation.startDate;
    endDate = widget.reservation.endDate;
  }

  int calculateTotalPrice({
    required DateTime startDate,
    required DateTime endDate,
    required int price,
  }) {
    final int days = endDate.difference(startDate).inDays;
    return days > 0 ? days * price : price; // Ensure at least 1 day's price
  }

  Future<void> _selectDate({
    required DateTime initialDate,
    required DateTime firstDate,
    required Function(DateTime) onDateSelected,
  }) async {
    final DateTime? picked = await showDatePicker(
      context: context,
      initialDate: initialDate,
      firstDate: firstDate,
      lastDate: DateTime(2100),
    );
    if (picked != null) {
      onDateSelected(picked);
    }
  }

  Future<void> _updateReservation(
      Reservation updatedReservation, ReservationRepository repository) async {
    setState(() {
      isLoading = true; // Show loading indicator
    });

    try {
      await ReservationController.updateReservation(
        reservation: updatedReservation,
        repository: repository,
      );

      if (mounted) {
        // Show success popup
        showDialog(
          context: context,
          builder: (context) => AlertDialog(
            title: const Text('Update Successful'),
            content: const Text('Your reservation details have been updated.'),
            actions: [
              TextButton(
                onPressed: () {
                  Navigator.of(context).pop(); // Close the dialog
                  Navigator.of(context).pop(); // Return to the previous screen
                },
                child: const Text('OK'),
              ),
            ],
          ),
        );
      }
    } catch (error) {
      if (mounted) {
        // Show failure popup
        showDialog(
          context: context,
          builder: (context) => AlertDialog(
            title: const Text('Update Failed'),
            content: Text(
              'Failed to update reservation! That\'s on our end, not yours! Please try again later.',
              style: const TextStyle(color: Colors.red),
            ),
            actions: [
              TextButton(
                onPressed: () {
                  Navigator.of(context).pop(); // Close the dialog
                },
                child: const Text('OK'),
              ),
            ],
          ),
        );
      }
    } finally {
      if (mounted) {
        setState(() {
          isLoading = false; // Hide loading indicator
        });
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    final reservationRepository =
        Provider.of<ReservationRepository>(context, listen: false);
    final carRepository = Provider.of<CarRepository>(context, listen: false);

    final car = carRepository.getCarById(widget.reservation.carId);

    return Scaffold(
      appBar: AppBar(
        title: const Text('Edit Rental'),
        centerTitle: true,
      ),
      body: Stack(
        children: [
          Padding(
            padding: const EdgeInsets.all(16.0),
            child: Center(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Text(
                    'Your car is waiting for you',
                    style: Theme.of(context).textTheme.bodyLarge?.copyWith(
                          fontWeight: FontWeight.bold,
                        ),
                  ),
                  const SizedBox(height: 20),
                  Text(
                    'Make',
                    style: Theme.of(context)
                        .textTheme
                        .bodyMedium
                        ?.copyWith(color: Colors.grey),
                  ),
                  Text(
                    car.make,
                    style: Theme.of(context).textTheme.bodyMedium,
                  ),
                  const SizedBox(height: 8),
                  Text(
                    'Model',
                    style: Theme.of(context)
                        .textTheme
                        .bodyMedium
                        ?.copyWith(color: Colors.grey),
                  ),
                  Text(
                    car.model,
                    style: Theme.of(context).textTheme.bodyMedium,
                  ),
                  const SizedBox(height: 8),
                  Text(
                    'Year',
                    style: Theme.of(context)
                        .textTheme
                        .bodyMedium
                        ?.copyWith(color: Colors.grey),
                  ),
                  Text(
                    car.productionYear.toString(),
                    style: Theme.of(context).textTheme.bodyMedium,
                  ),
                  const SizedBox(height: 20),
                  Text(
                    'Start Date',
                    style: Theme.of(context).textTheme.bodyMedium,
                  ),
                  const SizedBox(height: 8),
                  GestureDetector(
                    onTap: () => _selectDate(
                      initialDate: startDate,
                      firstDate: DateTime.now(),
                      onDateSelected: (pickedDate) {
                        setState(() {
                          startDate = pickedDate;
                          if (endDate.isBefore(startDate)) {
                            endDate = startDate.add(const Duration(days: 1));
                          }
                        });
                      },
                    ),
                    child: Container(
                      width: double.infinity,
                      padding: const EdgeInsets.all(12),
                      decoration: BoxDecoration(
                        color: Colors.grey[200],
                        borderRadius: BorderRadius.circular(8),
                      ),
                      child: Text(
                        '${startDate.day}/${startDate.month}/${startDate.year}',
                        textAlign: TextAlign.center,
                        style: Theme.of(context).textTheme.bodyMedium,
                      ),
                    ),
                  ),
                  const SizedBox(height: 16),
                  Text(
                    'End Date',
                    style: Theme.of(context).textTheme.bodyMedium,
                  ),
                  const SizedBox(height: 8),
                  GestureDetector(
                    onTap: () => _selectDate(
                      initialDate: endDate,
                      firstDate: startDate.add(const Duration(days: 1)),
                      onDateSelected: (pickedDate) {
                        setState(() {
                          endDate = pickedDate;
                        });
                      },
                    ),
                    child: Container(
                      width: double.infinity,
                      padding: const EdgeInsets.all(12),
                      decoration: BoxDecoration(
                        color: Colors.grey[200],
                        borderRadius: BorderRadius.circular(8),
                      ),
                      child: Text(
                        '${endDate.day}/${endDate.month}/${endDate.year}',
                        textAlign: TextAlign.center,
                        style: Theme.of(context).textTheme.bodyMedium,
                      ),
                    ),
                  ),
                  const SizedBox(height: 24),
                  Text(
                    'Updated Total Price: \$${calculateTotalPrice(
                      startDate: startDate,
                      endDate: endDate,
                      price: car.pricePerDay,
                    )}',
                    style: Theme.of(context).textTheme.bodyLarge?.copyWith(
                          fontWeight: FontWeight.bold,
                          color: Colors.blue,
                        ),
                  ),
                  const SizedBox(height: 24),
                  ElevatedButton(
                    onPressed: isLoading
                        ? null
                        : () {
                            final updatedTotalPrice = calculateTotalPrice(
                              startDate: startDate,
                              endDate: endDate,
                              price: car.pricePerDay,
                            );

                            final updatedReservation = Reservation(
                              id: widget.reservation.id,
                              carId: widget.reservation.carId,
                              userId: widget.reservation.userId,
                              totalPrice: updatedTotalPrice,
                              startDate: startDate,
                              endDate: endDate,
                            );

                            _updateReservation(
                              updatedReservation,
                              reservationRepository,
                            );
                          },
                    style: ElevatedButton.styleFrom(
                      backgroundColor: Colors.black,
                      padding: const EdgeInsets.symmetric(
                          vertical: 16, horizontal: 24),
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(8),
                      ),
                    ),
                    child: isLoading
                        ? const CircularProgressIndicator(
                            color: Colors.white,
                          )
                        : const Text(
                            'Update Details',
                            style: TextStyle(
                              color: Colors.white,
                              fontSize: 16,
                              fontWeight: FontWeight.bold,
                            ),
                          ),
                  ),
                ],
              ),
            ),
          ),
          if (isLoading)
            const Center(
              child: CircularProgressIndicator(),
            ),
        ],
      ),
    );
  }
}
