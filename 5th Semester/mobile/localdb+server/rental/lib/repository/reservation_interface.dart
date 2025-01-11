import 'package:rental/models/reservation.dart';

abstract class IReservationRepository {
  List<Reservation> getAllReservations();
  Reservation? getReservation(String id);
  void addReservation(Reservation reservation);
  void updateReservation(Reservation reservation);
  void deleteReservation(String id);
}
