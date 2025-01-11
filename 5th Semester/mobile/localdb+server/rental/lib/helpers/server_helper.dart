import 'package:http/http.dart' as http;
import 'package:logger/web.dart';
import 'dart:convert';

import 'package:rental/models/car.dart';
import 'package:rental/models/sync_action.dart';
import 'package:rental/models/reservation.dart';

class ServerHelper {
  static final ServerHelper instance = ServerHelper._privateConstructor();
  final Logger logger = Logger();
  final String _baseUrl = 'http://127.0.0.1:8080';

  ServerHelper._privateConstructor();

  Future<List<Car>> loadCars() async {
    final response = await http.get(Uri.parse('$_baseUrl/cars'));

    if (response.statusCode != 200) {
      throw Exception('Failed to load cars: ${response.statusCode}');
    }

    List<dynamic> carsJson = json.decode(response.body);
    logger.i(carsJson);
    List<Car> cars = carsJson.map((carJson) => Car.fromMap(carJson)).toList();

    return cars;
  }

  Future<void> syncActionsWithServer(List<SyncAction> actions) async {
    final jsonEncoding =
        jsonEncode(actions.map((action) => action.toQueryMap()).toList());
    logger.i('Syncing actions with server $jsonEncoding');
    final response = await http.post(
      Uri.parse('$_baseUrl/sync'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncoding,
    );

    if (response.statusCode != 200) {
      throw Exception('Failed to sync actions: ${response.statusCode}');
    }
  }

  Future<List<Reservation>> getReservationForUser(String userid) async {
    final response =
        await http.get(Uri.parse('$_baseUrl/reservations?id=$userid'));

    if (response.statusCode != 200) {
      throw Exception('Failed to load reservations: ${response.statusCode}');
    }

    List<dynamic> reservationsJson = json.decode(response.body);
    logger.i(reservationsJson);
    List<Reservation> reservations = reservationsJson
        .map((reservationJson) => Reservation.fromMap(reservationJson))
        .toList();

    return reservations;
  }

  Future<void> insertReservation(Reservation reservation) async {
    await http.post(
      Uri.parse('$_baseUrl/reservations/insert'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(reservation.toMap()),
    );
  }

  Future<void> deleteReservation(String reservationId) async {
    await http.delete(Uri.parse('$_baseUrl/reservations?id=$reservationId'));
  }

  Future<void> updateReservation(Reservation reservation) async {
    await http.patch(
      Uri.parse('$_baseUrl/reservations/update'),
      headers: <String, String>{
        'Content-Type': 'application/json; charset=UTF-8',
      },
      body: jsonEncode(reservation.toMap()),
    );
  }
}
