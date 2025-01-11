import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:rental/repository/car_repository.dart';
import 'car_detail_view.dart';
import 'car_card.dart';

class CarListView extends StatelessWidget {
  const CarListView({super.key});

  @override
  Widget build(BuildContext context) {
    final carRepository = Provider.of<CarRepository>(context);

    return Scaffold(
      appBar: AppBar(
        title: const Text('Available Cars'),
      ),
      body: Container(
        color: Colors.white,
        child: ListView.builder(
          itemCount: carRepository.cars.length,
          itemBuilder: (context, index) {
            final car = carRepository.cars[index];
            return GestureDetector(
              onTap: () {
                Navigator.of(context).push(
                  MaterialPageRoute(
                    builder: (context) => CarDetailView(car: car),
                  ),
                );
              },
              child: Padding(
                padding:
                    const EdgeInsets.symmetric(vertical: 4.0, horizontal: 8.0),
                child: CarCard(car: car),
              ),
            );
          },
        ),
      ),
    );
  }
}
