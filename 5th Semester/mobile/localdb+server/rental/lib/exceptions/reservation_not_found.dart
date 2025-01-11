class ReservationNotFound implements Exception {
  final String message;

  ReservationNotFound(this.message);

  @override
  String toString() => 'ReservationNotFound: $message';
}
