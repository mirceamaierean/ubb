import 'package:uuid/uuid.dart';

class Reservation {
  final String id;
  final int carId;
  final String userId;
  final int totalPrice;
  final DateTime startDate;
  final DateTime endDate;

  Reservation({
    String? id,
    required this.carId,
    required this.userId,
    this.totalPrice = 0,
    DateTime? startDate,
    DateTime? endDate,
  })  : id = id ?? Uuid().v4(),
        startDate = startDate ?? DateTime.now(),
        endDate = endDate ?? DateTime.now();
}
