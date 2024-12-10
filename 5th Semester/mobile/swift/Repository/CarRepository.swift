//
//  CarRepository.swift
//  Rental
//
//  Created by Mircea Maierean on 10.11.2024.
//

import Foundation
import SwiftUI

class CarRepository: ObservableObject {
    @Published var cars: [Car] = []

    init() {
        loadCars()
    }

    private func loadCars() {
        guard let url = Bundle.main.url(forResource: "cars", withExtension: "json") else {
            print("Could not find cars.json in bundle.")
            return
        }

        do {
            let data = try Data(contentsOf: url)
            cars = try JSONDecoder().decode([Car].self, from: data)
            print("Loaded cars:", cars)
        } catch {
            print("Error loading or decoding JSON:", error)
        }
    }

    func getCar(byId id: Int) -> Car? {
        return cars.first { $0.id == id }
    }
}
