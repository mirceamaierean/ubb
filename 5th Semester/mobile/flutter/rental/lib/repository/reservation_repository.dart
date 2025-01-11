import 'package:flutter/material.dart';
import 'package:rental/exceptions/reservation_not_found.dart';
import '../models/reservation.dart';

class ReservationRepository extends ChangeNotifier {
  List<Reservation> reservations = [];

  List<Reservation> getAllReservations() {
    return reservations;
  }

  Reservation? getReservation(String id) {
    return reservations.firstWhere(
      (reservation) => reservation.id == id,
      orElse: () =>
          throw ReservationNotFound('Reservation with ID $id not found'),
    );
  }

  void addReservation(Reservation reservation) {
    reservations.add(reservation);
    notifyListeners();
  }

  void updateReservation(Reservation reservation) {
    final index = reservations.indexWhere((r) => r.id == reservation.id);
    if (index != -1) {
      reservations[index] = reservation;
      notifyListeners();
    }
  }

  void deleteReservation(String id) {
    reservations.removeWhere((reservation) => reservation.id == id);
    notifyListeners();
  }
}
