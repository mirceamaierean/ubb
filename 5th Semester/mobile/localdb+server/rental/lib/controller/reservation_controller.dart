import 'package:logger/logger.dart';
import 'package:rental/repository/reservation_repository.dart';
import '../models/reservation.dart';

class ReservationController {
  static final logger = Logger();
  static void createReservation({
    required int carId,
    required String userId,
    required DateTime startDate,
    required DateTime endDate,
    required int pricePerDay,
    required ReservationRepository repository,
  }) async {
    final int totalPrice =
        pricePerDay * totalDays(startDate: startDate, endDate: endDate);
    final reservation = Reservation(
      carId: carId,
      userId: userId,
      totalPrice: totalPrice,
      startDate: startDate,
      endDate: endDate,
    );

    await repository.addReservation(reservation);
  }

  static int totalDays(
      {required DateTime startDate, required DateTime endDate}) {
    return endDate.difference(startDate).inDays;
  }

  static List<Reservation> getReservations(
      {required ReservationRepository repository}) {
    return repository.getAllReservations();
  }

  static Future<void> deleteReservation({
    required String id,
    required ReservationRepository repository,
  }) async {
    try {
      await repository.deleteReservation(id);
    } catch (e) {
      logger.e('Error deleting reservation: $e');
      rethrow;
    }
  }

  static Reservation? getReservation({
    required String id,
    required ReservationRepository repository,
  }) {
    try {
      return repository.getReservation(id);
    } catch (e) {
      logger.e('Error getting reservation: $e');
      rethrow;
    }
  }

  static Future<void> updateReservation({
    required Reservation reservation,
    required ReservationRepository repository,
  }) async {
    try {
      await repository.updateReservation(reservation);
    } catch (e) {
      logger.e('Error updating reservation: $e');
      rethrow;
    }
  }
}
