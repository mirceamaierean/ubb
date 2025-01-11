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

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'make': make,
      'model': model,
      'color': color,
      'productionYear': productionYear,
      'carburantType': carburantType,
      'bodyType': bodyType,
      'pricePerDay': pricePerDay,
      'photoPath': photoPath,
    };
  }

  factory Car.fromMap(Map<String, dynamic> map) {
    return Car(
      id: map['id'],
      make: map['make'],
      model: map['model'],
      color: map['color'],
      productionYear: map['productionYear'],
      carburantType: map['carburantType'],
      bodyType: map['bodyType'],
      pricePerDay: map['pricePerDay'],
      photoPath: map['photoPath'],
    );
  }
}
