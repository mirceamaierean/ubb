//
//  CarListView.swift
//  Rental
//
//  Created by Mircea Maierean on 07.11.2024.
//

import SwiftUI

struct CarListView: View {
    @EnvironmentObject var carRepository: CarRepository
    @EnvironmentObject var reservationRepository: InMemoryReservationRepository

    var body: some View {
        NavigationStack {
            List(carRepository.cars) { car in  
                NavigationLink(destination: CarDetailView(car: car)) {
                    CarCard(car: car)
                        .padding(.bottom, 8)
                }
            }
            .background(Color(UIColor.systemGroupedBackground))
            .navigationTitle("Available Cars")
        }
    }
}
