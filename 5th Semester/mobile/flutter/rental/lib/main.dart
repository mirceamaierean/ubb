import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:rental/repository/car_repository.dart';
import 'package:rental/repository/reservation_repository.dart';
import 'models/user.dart';
import 'views/content_view.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  final carRepository = await CarRepository.create();

  runApp(RentalApp(carRepository: carRepository));
}

class RentalApp extends StatelessWidget {
  final CarRepository carRepository;

  const RentalApp({required this.carRepository, super.key});

  @override
  Widget build(BuildContext context) {
    return MultiProvider(
      providers: [
        Provider<CarRepository>(
          create: (_) => carRepository,
        ),
        ChangeNotifierProvider<ReservationRepository>(
          create: (_) => ReservationRepository(),
        ),
        Provider<User>(
          create: (_) => User(
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
