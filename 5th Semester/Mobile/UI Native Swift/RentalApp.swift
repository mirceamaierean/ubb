//
//  RentalApp.swift
//  Rental
//
//  Created by Mircea Maierean on 05.11.2024.
//
import SwiftUI

@main
struct RentalApp: App {
    @StateObject private var carRepository = CarRepository()
    @StateObject private var reservationRepository = InMemoryReservationRepository()
    
    var body: some Scene {
        WindowGroup {
            ContentView()
                .environmentObject(carRepository)
                .environmentObject(reservationRepository)
                .environmentObject(User(name: "John Doe", dateOfBirth: Calendar.current.date(from: DateComponents(year: 2000, month: 1, day: 1)) ?? Date()))
        }
    }
}
 
