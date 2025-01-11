import 'package:flutter/material.dart';
import 'package:rental/repository/reservation_repository.dart';
import '../models/car.dart';
import '../models/reservation.dart';
import 'package:provider/provider.dart';

class CarDetailView extends StatefulWidget {
  final Car car;

  const CarDetailView({required this.car, super.key});

  @override
  State<CarDetailView> createState() => _CarDetailViewState();
}

class _CarDetailViewState extends State<CarDetailView> {
  late DateTime startDate;
  late DateTime endDate;

  @override
  void initState() {
    super.initState();
    startDate = DateTime.now();
    startDate = DateTime(startDate.year, startDate.month, startDate.day);
    endDate = startDate.add(const Duration(days: 1));
  }

  int calculateTotalPrice() {
    final int days = endDate.difference(startDate).inDays;
    return days * widget.car.pricePerDay;
  }

  Future<void> _selectDate({
    required DateTime initialDate,
    required Function(DateTime) onDateSelected,
    required DateTime firstDate,
  }) async {
    final DateTime? pickedDate = await showDatePicker(
      context: context,
      initialDate: initialDate,
      firstDate: firstDate,
      lastDate: DateTime(2100),
    );
    if (pickedDate != null) {
      onDateSelected(pickedDate);
    }
  }

  void _reserveCar(BuildContext context) {
    final reservationRepository =
        Provider.of<ReservationRepository>(context, listen: false);

    final totalPrice = calculateTotalPrice();

    final reservation = Reservation(
      carId: widget.car.id,
      userId: "current_user_id",
      totalPrice: totalPrice,
      startDate: startDate,
      endDate: endDate,
    );

    reservationRepository.addReservation(reservation);

    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Reservation Successful'),
        content: const Text('Your car has been reserved successfully.'),
        actions: [
          TextButton(
            onPressed: () => Navigator.of(context).pop(),
            child: const Text('OK'),
          ),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('${widget.car.make} ${widget.car.model}'),
      ),
      body: SingleChildScrollView(
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.center,
          children: [
            if (widget.car.photoPath != null)
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 16.0),
                child: ClipRRect(
                  borderRadius: BorderRadius.circular(12),
                  child: Image.asset(
                    widget.car.photoPath!,
                    height: 250,
                    width: double.infinity,
                    fit: BoxFit.cover,
                  ),
                ),
              )
            else
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 16.0),
                child: Container(
                  height: 250,
                  decoration: BoxDecoration(
                    color: Colors.grey,
                    borderRadius: BorderRadius.circular(12),
                  ),
                ),
              ),
            const SizedBox(height: 20),
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 16.0),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Text(
                    '${widget.car.make} ${widget.car.model}',
                    style: Theme.of(context)
                        .textTheme
                        .titleMedium
                        ?.copyWith(fontWeight: FontWeight.bold),
                    textAlign: TextAlign.center,
                  ),
                  const SizedBox(height: 8),
                  Text(
                    'Price per day: \$${widget.car.pricePerDay}',
                    style: Theme.of(context).textTheme.bodyLarge,
                    textAlign: TextAlign.center,
                  ),
                  Text(
                    'Total price: \$${calculateTotalPrice()}',
                    style: Theme.of(context).textTheme.bodyLarge,
                    textAlign: TextAlign.center,
                  ),
                  const SizedBox(height: 8),
                  Text(
                    'Color: ${widget.car.color}',
                    style: Theme.of(context).textTheme.bodyMedium,
                  ),
                  Text(
                    'Body type: ${widget.car.bodyType}',
                    style: Theme.of(context).textTheme.bodyMedium,
                  ),
                  Text(
                    'Fuel type: ${widget.car.carburantType}',
                    style: Theme.of(context).textTheme.bodyMedium,
                  ),
                  Text(
                    'Year: ${widget.car.productionYear}',
                    style: Theme.of(context).textTheme.bodyMedium,
                  ),
                ],
              ),
            ),
            const SizedBox(height: 20),
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 16.0),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Text(
                    'Start Date',
                    style: Theme.of(context).textTheme.bodyLarge,
                  ),
                  const SizedBox(height: 8),
                  GestureDetector(
                    onTap: () => _selectDate(
                      initialDate: startDate,
                      firstDate: DateTime.now(),
                      onDateSelected: (selectedDate) {
                        setState(() {
                          startDate = selectedDate;
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
                        '${startDate.month}/${startDate.day}/${startDate.year}',
                        textAlign: TextAlign.center,
                        style: Theme.of(context).textTheme.bodyLarge,
                      ),
                    ),
                  ),
                  const SizedBox(height: 16),
                  Text(
                    'End Date',
                    style: Theme.of(context).textTheme.bodyLarge,
                  ),
                  const SizedBox(height: 8),
                  GestureDetector(
                    onTap: () => _selectDate(
                      initialDate: endDate,
                      firstDate: startDate.add(const Duration(days: 1)),
                      onDateSelected: (selectedDate) {
                        setState(() {
                          endDate = selectedDate;
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
                        '${endDate.month}/${endDate.day}/${endDate.year}',
                        textAlign: TextAlign.center,
                        style: Theme.of(context).textTheme.bodyLarge,
                      ),
                    ),
                  ),
                ],
              ),
            ),
            const SizedBox(height: 20),
            Padding(
              padding: const EdgeInsets.symmetric(horizontal: 16.0),
              child: ElevatedButton(
                onPressed: () => _reserveCar(context),
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.black,
                  padding: const EdgeInsets.all(16),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(10),
                  ),
                ),
                child: const Text(
                  'Reserve Car',
                  style: TextStyle(
                    color: Colors.white,
                    fontSize: 16,
                    fontWeight: FontWeight.bold,
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
