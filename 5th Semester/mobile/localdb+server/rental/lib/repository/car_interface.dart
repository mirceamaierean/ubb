import '../models/car.dart';

abstract class ICarRepository {
  Car getCarById(int id);
}
