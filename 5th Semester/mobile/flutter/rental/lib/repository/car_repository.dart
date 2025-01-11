import 'dart:convert';
import 'package:flutter/services.dart';
import '../models/car.dart';
import '../exceptions/car_not_found.dart';

class CarRepository {
  List<Car> cars = [];

  CarRepository._();

  static Future<CarRepository> create() async {
    var repository = CarRepository._();
    await repository.loadCars();
    return repository;
  }

  Future<void> loadCars() async {
    final String response =
        await rootBundle.loadString('assets/data/cars.json');

    final List data = json.decode(response);

    cars = data.map((car) => Car.fromJson(car)).toList();
  }

  Car getCarById(int id) {
    return cars.firstWhere(
      (car) => car.id == id,
      orElse: () => throw CarNotFoundException('Car with ID $id not found'),
    );
  }
}
