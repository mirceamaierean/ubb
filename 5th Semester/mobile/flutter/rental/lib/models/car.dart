class Car {
  final int id;
  final String make;
  final String model;
  final String color;
  final int productionYear;
  final String carburantType;
  final String bodyType;
  final int pricePerDay;
  final String? photoPath;

  Car({
    required this.id,
    required this.make,
    required this.model,
    required this.color,
    required this.productionYear,
    required this.carburantType,
    required this.bodyType,
    required this.pricePerDay,
    this.photoPath,
  });

  factory Car.fromJson(Map<String, dynamic> json) {
    return Car(
      id: json['id'],
      make: json['make'],
      model: json['model'],
      color: json['color'],
      productionYear: json['productionYear'],
      carburantType: json['carburantType'],
      bodyType: json['bodyType'],
      pricePerDay: json['pricePerDay'],
      photoPath: json['photoPath'],
    );
  }
}
