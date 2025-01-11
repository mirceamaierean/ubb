import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';
import 'package:logger/logger.dart';
import '../models/reservation.dart';

class DatabaseHelper {
  static final DatabaseHelper instance = DatabaseHelper._privateConstructor();
  static Database? _database;
  final logger = Logger();

  DatabaseHelper._privateConstructor();

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDatabase();
    return _database!;
  }

  Future<Database> _initDatabase() async {
    String path = join(await getDatabasesPath(), 'reservations.db');
    logger.i('Database path: $path');
    return await openDatabase(
      path,
      version: 1,
      onCreate: _onCreate,
    );
  }

  Future<void> _onCreate(Database db, int version) async {
    logger.i('Creating tables');

    await db.execute('''
      CREATE TABLE cars(
        id INTEGER PRIMARY KEY,
        make TEXT NOT NULL,
        model TEXT NOT NULL,
        color TEXT NOT NULL,
        productionYear INTEGER NOT NULL,
        carburantType TEXT NOT NULL,
        bodyType TEXT NOT NULL,
        pricePerDay INTEGER NOT NULL,
        photoPath TEXT
      )
    ''');

    await db.execute('''
      CREATE TABLE reservations(
        id TEXT PRIMARY KEY,
        carId INTEGER NOT NULL,
        userId TEXT NOT NULL,
        startDate TEXT NOT NULL,
        endDate TEXT NOT NULL,
        totalPrice INTEGER NOT NULL,
        FOREIGN KEY (carId) REFERENCES cars(id)
      )
    ''');

    await initializeCars();
  }

  Future<List<Map<String, dynamic>>> getAllReservationsForUser(
      String userId) async {
    logger.i("Getting all reservations from the database");
    Database db = await database;
    return await db
        .query('reservations', where: 'userId = ?', whereArgs: [userId]);
  }

  Future<List<Map<String, dynamic>>> getAllCars() async {
    logger.i("Getting all cars from the database");
    Database db = await database;
    return await db.query('cars');
  }

  Future<void> initializeCars() async {
    logger.i("DB has just been create, inserting values for the cars table");
    Database db = await database;
    await db.execute('''
      INSERT INTO cars (id, make, model, color, productionYear, carburantType, bodyType, pricePerDay, photoPath) VALUES
      (1, 'BMW', 'X3', 'Black', 2018, 'Diesel', 'SUV', 70, 'assets/images/cars/BMW/BMW.png'),
      (2, 'Dacia', '1310', 'Blue', 1982, 'Petrol', 'SUV', 40, 'assets/images/cars/Dacia/Dacia.png'),
      (3, 'Ford', 'Focus', 'Blue', 2017, 'Petrol', 'Hatchback', 50, 'assets/images/cars/Ford/Ford.png'),
      (4, 'Honda', 'Civic', 'Gray', 2016, 'Petrol', 'Sedan', 55, 'assets/images/cars/Honda/Honda.png'),
      (5, 'Mercedes', 'CLA', 'Blue', 2020, 'Diesel', 'Sedan', 85, 'assets/images/cars/Mercedes/Mercedes.png'),
      (6, 'Porsche', '911', 'Red', 2020, 'Petrol', 'Coupe', 150, 'assets/images/cars/Porsche/Porsche.png'),
      (7, 'Renault', 'Clio', 'White', 2015, 'Petrol', 'Hatchback', 45, 'assets/images/cars/Renault/Renault.png'),
      (8, 'Skoda', 'Octavia', 'Black', 2009, 'Diesel', 'Sedan', 60, 'assets/images/cars/Skoda/Skoda.png'),
      (9, 'Volkswagen', 'Passat', 'Black', 2014, 'Diesel', 'Sedan', 55, 'assets/images/cars/Volkswagen/Volkswagen.png');
    ''');
  }

  Future<void> insertReservation(Reservation reservation) async {
    logger.i('Inserting reservation into the database: ${reservation.toMap()}');
    await Future.delayed(Duration(seconds: 2));
    Database db = await database;
    await db.insert('reservations', reservation.toMap());
  }

  Future<void> updateReservation(Reservation reservation) async {
    logger.i('Updating reservation in the database: ${reservation.toMap()}');
    // await Future.delayed(Duration(seconds: 2));
    Database db = await database;
    await db.update(
      'reservations',
      reservation.toMap(),
      where: 'id = ?',
      whereArgs: [reservation.id],
    );
  }

  Future<void> deleteReservation(String id) async {
    logger.i('Deleting reservation with ID from database: $id');
    // await Future.delayed(Duration(seconds: 2));
    Database db = await database;
    await db.delete(
      'reservations',
      where: 'id = ?',
      whereArgs: [id],
    );
  }
}
