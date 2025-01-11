import 'package:rental/models/car.dart';
import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';
import 'package:logger/logger.dart';
import '../models/reservation.dart';
import '../models/sync_action.dart';

class DatabaseHelper {
  static final DatabaseHelper instance = DatabaseHelper._privateConstructor();
  static Database? _database;
  final Logger logger = Logger();

  DatabaseHelper._privateConstructor();

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDatabase();
    return _database!;
  }

  Future<Database> _initDatabase() async {
    String path = join(await getDatabasesPath(), 'local.db');
    logger.i('Database path: $path');
    return await openDatabase(
      path,
      version: 1,
      onCreate: _onCreate,
    );
  }

  Future<void> createCarsTable(Database db) async {
    logger.i('Creating cars table');

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
  }

  Future<void> createReservationsTable(Database db) async {
    logger.i('Creating reservations table');
    await db.execute('''
      CREATE TABLE reservations(
        id TEXT PRIMARY KEY,
        userId TEXT NOT NULL,
        carId INTEGER NOT NULL,
        startDate TEXT NOT NULL,
        endDate TEXT NOT NULL,
        totalPrice INTEGER NOT NULL,
        FOREIGN KEY (carId) REFERENCES cars(id)
      )
    ''');
  }

  Future<void> createActionsTable(Database db) async {
    logger.i('Creating actions table');
    await db.execute('''
      CREATE TABLE actions(
        id TEXT PRIMARY KEY,
        actionType TEXT NOT NULL,
        createdAt TEXT DEFAULT CURRENT_TIMESTAMP,
        reservationId TEXT NOT NULL,
        userId TEXT NOT NULL,
        carId INTEGER NOT NULL,
        startDate TEXT NOT NULL,
        endDate TEXT NOT NULL,
        totalPrice INTEGER NOT NULL,
        FOREIGN KEY (carId) REFERENCES cars(id)
      )
    ''');
  }

  Future<int> getActionsCount() async {
    logger.i('Getting actions count');
    Database db = await database;
    final queryAnswer = await db.rawQuery('SELECT COUNT(*) FROM actions');
    return Sqflite.firstIntValue(queryAnswer)!;
  }

  Future<void> _onCreate(Database db, int version) async {
    logger.i('Creating tables');

    await createCarsTable(db);
    await createReservationsTable(db);
    await createActionsTable(db);
  }

  Future<List<Reservation>> getAllReservationsForUser(String userId) async {
    logger.i("Getting all reservations from the database");
    Database db = await database;
    final queryAnswer = await db
        .query('reservations', where: 'userId = ?', whereArgs: [userId]);
    return queryAnswer.map((e) => Reservation.fromMap(e)).toList();
  }

  Future<List<Car>> getAllCars() async {
    logger.i("Getting all cars from the database");
    Database db = await database;
    final quertAnswer = await db.query('cars');
    return quertAnswer.map((e) => Car.fromMap(e)).toList();
  }

  Future<List<SyncAction>> getAllActions() async {
    logger.i("Getting all actions from the database");
    Database db = await database;
    final queryAnswer = await db.query('actions', orderBy: 'createdAt');
    return queryAnswer.map((e) => SyncAction.fromMap(e)).toList();
  }

  Future<void> syncCars(List<Car> cars) async {
    logger.i("Syncing cars with external source on local db");
    Database db = await database;
    await clearCars();
    await db.transaction((txn) async {
      final batch = txn.batch();
      for (final car in cars) {
        batch.insert('cars', car.toMap());
      }
      await batch.commit(noResult: true);
    });
  }

  Future<void> syncReservations(List<Reservation> reservations) async {
    logger.i("Syncing reservations with external source on local db");

    Database db = await database;

    await clearReservations();

    await db.transaction((txn) async {
      final batch = txn.batch();
      for (final reservation in reservations) {
        batch.insert('reservations', reservation.toMap());
      }
      await batch.commit(noResult: true);
    });
  }

  Future<void> clearCars() async {
    logger.i("Clearing cars table");
    Database db = await database;
    await db.delete('cars');
  }

  Future<void> clearReservations() async {
    logger.i("Clearing reservations table");
    Database db = await database;
    await db.delete('reservations');
  }

  Future<void> clearActions() async {
    logger.i("Clearing actions table");
    Database db = await database;
    await db.delete('actions');
  }

  Future<void> insertReservation(Reservation reservation) async {
    logger.i('Inserting reservation into the database: ${reservation.toMap()}');
    // await Future.delayed(Duration(seconds: 2));
    Database db = await database;
    await db.insert('reservations', reservation.toMap());
  }

  Future<void> insertAction(SyncAction action) async {
    logger.i("Inserting action into the database");
    Database db = await database;
    await db.insert('actions', action.toMap());
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
