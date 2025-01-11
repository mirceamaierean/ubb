import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:rental/repository/car_repository.dart';
import 'package:rental/repository/reservation_repository.dart';
import 'package:rental/views/error_view.dart';
import 'models/user.dart';
import 'views/content_view.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  final carRepository = CarRepository();
  final reservationRepository = ReservationRepository();
  try {
    await carRepository.loadCars();

    runApp(RentalApp(
        carRepository: carRepository,
        reservationRepository: reservationRepository));
  } catch (e) {
    runApp(MaterialApp(
      home: ErrorScreen(
          errorMessage: "We can't load the cars right now. Try again later"),
    ));
  }
}

class RentalApp extends StatelessWidget {
  final CarRepository carRepository;
  final ReservationRepository reservationRepository;

  const RentalApp(
      {required this.carRepository,
      required this.reservationRepository,
      super.key});

  @override
  Widget build(BuildContext context) {
    return MultiProvider(
      providers: [
        Provider<CarRepository>(
          create: (_) => carRepository,
        ),
        ChangeNotifierProvider<ReservationRepository>(
          create: (_) => reservationRepository,
        ),
        Provider<User>(
          create: (_) => User(
            id: "7ac-2nssds-23fsdhsdsa",
            name: "John Doe",
            dateOfBirth: DateTime(2005, 12, 12),
          ),
        ),
      ],
      child: MaterialApp(
        title: 'Rental App',
        theme: ThemeData(
          primarySwatch: Colors.green,
        ),
        home: const ContentView(),
      ),
    );
  }
}
