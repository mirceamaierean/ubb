import 'package:rental/repository/reservation_repository.dart';
import '../models/reservation.dart';

class ReservationController {
  static void createReservation({
    required int carId,
    required String userId,
    required DateTime startDate,
    required DateTime endDate,
    required int pricePerDay,
    required ReservationRepository repository,
  }) {
    final int totalPrice =
        pricePerDay * totalDays(startDate: startDate, endDate: endDate);
    final reservation = Reservation(
      carId: carId,
      userId: userId,
      totalPrice: totalPrice,
      startDate: startDate,
      endDate: endDate,
    );

    repository.addReservation(reservation);
  }

  static int totalDays(
      {required DateTime startDate, required DateTime endDate}) {
    return endDate.difference(startDate).inDays;
  }

  static List<Reservation> getReservations(
      {required ReservationRepository repository}) {
    return repository.getAllReservations();
  }

  static void deleteReservation({
    required String id,
    required ReservationRepository repository,
  }) {
    repository.deleteReservation(id);
  }

  static Reservation? getReservation({
    required String id,
    required ReservationRepository repository,
  }) {
    return repository.getReservation(id);
  }

  static void updateReservation({
    required Reservation reservation,
    required ReservationRepository repository,
  }) {
    repository.updateReservation(reservation);
  }
}
