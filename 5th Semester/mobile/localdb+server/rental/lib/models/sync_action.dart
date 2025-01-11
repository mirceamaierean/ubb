import 'package:rental/models/reservation.dart';
import 'package:uuid/uuid.dart';

class SyncAction {
  final String id;
  final String actionType;
  final DateTime createdAt;
  final Reservation reservation;

  SyncAction(
      {String? id,
      required this.actionType,
      DateTime? createdAt,
      required this.reservation})
      : id = id ?? Uuid().v4(),
        createdAt = createdAt ?? DateTime.now();

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'actionType': actionType,
      'createdAt': createdAt.toIso8601String(),
      'reservationId': reservation.id,
      'userId': reservation.userId,
      'carId': reservation.carId,
      'startDate': reservation.startDate.toIso8601String(),
      'endDate': reservation.endDate.toIso8601String(),
      'totalPrice': reservation.totalPrice,
    };
  }

  factory SyncAction.fromMap(Map<String, dynamic> map) {
    // display the type for each value
    return SyncAction(
      id: map['id'],
      actionType: map['actionType'],
      createdAt: DateTime.parse(map['createdAt']),
      reservation: Reservation(
        id: map['reservationId'],
        userId: map['userId'],
        carId: map['carId'],
        startDate: DateTime.parse(map['startDate']),
        endDate: DateTime.parse(map['endDate']),
        totalPrice: map['totalPrice'],
      ),
    );
  }

  Map<String, dynamic> toQueryMap() {
    return {
      'id': id,
      'actionType': actionType,
      'createdAt': createdAt.toIso8601String(),
      'reservation': reservation.toMap()
    };
  }
}
