import 'package:flutter/material.dart';
import 'package:logger/web.dart';
import 'package:rental/exceptions/reservation_not_found.dart';
import 'package:rental/helpers/db_helper.dart';
import 'package:rental/models/user.dart';
import 'package:rental/repository/reservation_interface.dart';
import '../models/reservation.dart';

class ReservationRepository extends ChangeNotifier
    implements IReservationRepository {
  List<Reservation> reservations = [];
  User? user;

  final DatabaseHelper dbHelper = DatabaseHelper.instance;
  final logger = Logger();

  Future<void> loadReservations(User crtUser) async {
    if (user == null) {
      
      user = crtUser;
      logger.i('Loading reservations for user with ID ${user!.id}');
      final data = await dbHelper.getAllReservationsForUser(user!.id);
      reservations = data.map((map) => Reservation.fromMap(map)).toList();
      logger.i('Reservations loaded');
      notifyListeners();
    }
  }

  @override
  List<Reservation> getAllReservations() {
    return reservations;
  }

  @override
  Reservation? getReservation(String id) {
    try {
      return reservations.firstWhere((reservation) => reservation.id == id);
    } on StateError {
      throw ReservationNotFound('Reservation with ID $id not found');
    }
  }

  @override
  Future<void> addReservation(Reservation reservation) async {
    try {
      await dbHelper.insertReservation(reservation);
      reservations.add(reservation);
      logger.i('Reservation with ID ${reservation.id} succesfully added');
      notifyListeners();
    } catch (e) {
      logger.e('Error adding reservation: $e');
      rethrow;
    }
  }

  @override
  Future<void> updateReservation(Reservation reservation) async {
    final index = reservations.indexWhere((r) => r.id == reservation.id);
    if (index == -1) {
      throw ReservationNotFound(
          'Reservation with ID ${reservation.id} not found');
    }
    await dbHelper.updateReservation(reservation);
    reservations[index] = reservation;
    notifyListeners();
  }

  @override
  Future<void> deleteReservation(String id) async {
    await dbHelper.deleteReservation(id);
    logger.i('Deleting reservation with ID from local storage $id');
    reservations.removeWhere((reservation) => reservation.id == id);
    logger.i('Reservation with ID $id succesfully deleted');
    notifyListeners();
  }
}
