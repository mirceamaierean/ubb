import 'package:logger/logger.dart';
import 'package:rental/helpers/db_helper.dart';
import 'package:rental/repository/car_interface.dart';
import '../models/car.dart';
import '../exceptions/car_not_found.dart';

class CarRepository implements ICarRepository {
  List<Car> cars = [];
  final logger = Logger();
  final DatabaseHelper dbHelper = DatabaseHelper.instance;

  @override
  Car getCarById(int id) {
    return cars.firstWhere(
      (car) => car.id == id,
      orElse: () => throw CarNotFoundException('Car with ID $id not found'),
    );
  }

  Future<void> loadCars() async {
    try {
      final data = await dbHelper.getAllCars();
      cars = data.map((map) => Car.fromMap(map)).toList();
    } catch (e) {
      logger.e('Error loading cars: $e');
      rethrow;
    }
  }
}
