import 'package:uuid/uuid.dart';

class User {
  final String id;
  final String name;
  final DateTime dateOfBirth;

  User({
    String? id,
    required this.name,
    required this.dateOfBirth,
  }) : id = id ?? Uuid().v4();
}
