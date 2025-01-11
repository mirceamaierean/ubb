import 'dart:async';

import 'package:flutter/material.dart';
import 'package:logger/web.dart';
import 'package:rental/exceptions/reservation_not_found.dart';
import 'package:rental/helpers/db_helper.dart';
import 'package:rental/helpers/server_helper.dart';
import 'package:rental/models/sync_action.dart';
import 'package:rental/models/user.dart';
import 'package:rental/repository/reservation_interface.dart';
import '../models/reservation.dart';

class ReservationRepository extends ChangeNotifier
    implements IReservationRepository {
  List<Reservation> reservations = [];
  User? user;

  final DatabaseHelper dbHelper = DatabaseHelper.instance;
  final ServerHelper serverHelper = ServerHelper.instance;

  final logger = Logger();
  Timer? _syncTimer; // Timer for periodic sync

  // Function to start periodic syncing
  void startPeriodicSync({Duration interval = const Duration(seconds: 10)}) {
    logger.i('Starting periodic sync with interval: $interval');
    _syncTimer?.cancel();
    _syncTimer = Timer.periodic(interval, (Timer timer) async {
      await syncActions();
    });
  }

  // Function to stop periodic syncing
  void stopPeriodicSync() {
    logger.i('Stopping periodic sync');
    _syncTimer?.cancel();
  }

  Future<void> syncActions() async {
    try {
      final actions = await dbHelper.getAllActions();
      await serverHelper.syncActionsWithServer(actions);
      await dbHelper.clearActions();
    } catch (e) {
      logger.e('Error syncing actions: $e');
    }
  }

  Future<void> loadReservations(User crtUser) async {
    if (user == null) {
      user = crtUser;
      logger.i('Loading reservations for user with ID ${user!.id}');
      final actionsCount = await dbHelper.getActionsCount();
      if (actionsCount == 0) {
        // server is synced with local db, load reservations from server
        try {
          reservations = await serverHelper.getReservationForUser(user!.id);
          await dbHelper.syncReservations(reservations);
        } catch (e) {
          logger.e(
              'Error loading reservations from server: $e. Falling back to local DB.');
          try {
            reservations = await dbHelper.getAllReservationsForUser(user!.id);
          } catch (e) {
            logger.e('Error loading reservations: $e');
            rethrow;
          }
        }
      } else {
        // if actions are present, means that the last source of truth was local db
        // load reservations from local db
        try {
          reservations = await dbHelper.getAllReservationsForUser(user!.id);
        } catch (e) {
          logger.e('Error loading reservations: $e');
          rethrow;
        }
      }
      logger.i('Reservations loaded');
      notifyListeners();

      startPeriodicSync();
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
    // workflow
    /*
    - add data to local db
      - if not working, print error
    - add data to server
      -if not working, add action to local db, to sync later
        - if action not working
          - if did not manage to sync with local db, rethrow error
    */
    bool syncedWithLocalDB = false;
    try {
      await dbHelper.insertReservation(reservation);
      syncedWithLocalDB = true;
      logger.i('Reservation added to local storage: $reservation');
    } catch (e) {
      logger.e('Cannot add reservation to local db: $e');
    }
    try {
      await serverHelper.insertReservation(reservation);
    } catch (e) {
      logger.i(
          "Server is down: $e, falling back to local storage for adding reservation: $reservation");
      try {
        SyncAction action =
            SyncAction(actionType: "INSERT", reservation: reservation);
        await dbHelper.insertAction(action);
      } catch (e) {
        logger.e('Cannot add action to local db: $e');
        if (!(syncedWithLocalDB)) {
          rethrow;
        }
      }
    }

    reservations.add(reservation);

    notifyListeners();
  }

  @override
  Future<void> updateReservation(Reservation reservation) async {
    final index = reservations.indexWhere((r) => r.id == reservation.id);
    if (index == -1) {
      throw ReservationNotFound(
          'Reservation with ID ${reservation.id} not found');
    }
    bool syncedWithLocalDB = false;
    try {
      await dbHelper.updateReservation(reservation);
      syncedWithLocalDB = true;
      logger.i('Reservation updated in local storage: $reservation');
    } catch (e) {
      logger.e('Cannot update reservation in local db: $e');
    }
    try {
      await serverHelper.updateReservation(reservation);
    } catch (e) {
      logger.i(
          "Server is down, falling back to local storage for updating reservation: $reservation");
      try {
        SyncAction action =
            SyncAction(actionType: "UPDATE", reservation: reservation);
        await dbHelper.insertAction(action);
      } catch (e) {
        logger.e('Cannot add action to local db: $e');
        if (!(syncedWithLocalDB)) {
          rethrow;
        }
      }
    }
    reservations[index] = reservation;
    logger.i('Reservation updated: $reservation');
    notifyListeners();
  }

  @override
  Future<void> deleteReservation(String id) async {
    final reservation =
        reservations.firstWhere((reservation) => reservation.id == id);
    bool syncedWithLocalDB = false;
    try {
      await dbHelper.deleteReservation(id);
      syncedWithLocalDB = true;
      logger.i('Reservation deleted from local storage: $reservation');
    } catch (e) {
      logger.e('Cannot delete reservation from local db: $e');
    }
    try {
      await serverHelper.deleteReservation(id);
    } catch (e) {
      logger.i(
          "Server is down, falling back to local storage for deleting reservation: $reservation");
      try {
        SyncAction action =
            SyncAction(actionType: "DELETE", reservation: reservation);
        await dbHelper.insertAction(action);
      } catch (e) {
        logger.e('Cannot add action to local db: $e');
        if (!(syncedWithLocalDB)) {
          rethrow;
        }
      }
    }
    reservations.remove(reservation);
    logger.i('Reservation deleted: $reservation');
    notifyListeners();
  }
}
