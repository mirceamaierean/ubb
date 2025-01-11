import 'package:logger/logger.dart';
import 'package:rental/helpers/db_helper.dart';
import 'package:rental/helpers/server_helper.dart';
import 'package:rental/repository/car_interface.dart';
import '../models/car.dart';
import '../exceptions/car_not_found.dart';

class CarRepository implements ICarRepository {
  List<Car> cars = [];
  final logger = Logger();
  final DatabaseHelper dbHelper = DatabaseHelper.instance;
  final ServerHelper serverHelper = ServerHelper.instance;

  @override
  Car getCarById(int id) {
    return cars.firstWhere(
      (car) => car.id == id,
      orElse: () => throw CarNotFoundException('Car with ID $id not found'),
    );
  }

  Future<void> loadCars() async {
    try {
      cars = await serverHelper.loadCars();
      await dbHelper.syncCars(cars);
    } catch (e) {
      logger.e('Error loading cars from server: $e. Falling back to local DB.');
      try {
        cars = await dbHelper.getAllCars();
      } catch (e) {
        logger.e('Error loading cars: $e');
        rethrow;
      }
    }
  }
}
