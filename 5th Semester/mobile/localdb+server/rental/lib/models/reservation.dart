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

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'carId': carId,
      'userId': userId,
      'totalPrice': totalPrice,
      'startDate': startDate.toIso8601String(),
      'endDate': endDate.toIso8601String(),
    };
  }

  factory Reservation.fromMap(Map<String, dynamic> map) {
    return Reservation(
      id: map['id'],
      carId: map['carId'],
      userId: map['userId'],
      totalPrice: map['totalPrice'],
      startDate: DateTime.parse(map['startDate']),
      endDate: DateTime.parse(map['endDate']),
    );
  }
}
