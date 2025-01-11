class CarNotFoundException implements Exception {
  final String message;

  CarNotFoundException(this.message);

  @override
  String toString() => 'CarNotFoundException: $message';
}
