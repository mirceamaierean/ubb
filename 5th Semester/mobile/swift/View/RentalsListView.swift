//
//  RentalsListView.swift
//  Rental
//
//  Created by Mircea Maierean on 10.11.2024.
//

import SwiftUI

struct RentalsListView: View {
    @EnvironmentObject var reservationRepository: InMemoryReservationRepository
    @EnvironmentObject var carRepository: CarRepository
    @EnvironmentObject var currentUser: User
    
    @State private var showingAlert = false
    @State private var reservationToDelete: Reservation?

    private var dateFormatter: DateFormatter {
        let formatter = DateFormatter()
        formatter.dateStyle = .short
        return formatter
    }

    var body: some View {
        List {
            ForEach(reservationRepository.reservations, id: \.id) { reservation in
                VStack(alignment: .leading) {
                    if let car = carRepository.getCar(byId: reservation.carId) {
                        Text("\(car.make) \(car.model)")
                            .font(.headline)
                    } else {
                        Text("Car details not available")
                            .font(.headline)
                            .foregroundColor(.red)
                    }
                    
                    Text("Total Price: $\(reservation.totalPrice)")
                        .font(.subheadline)
                    Text("Start: \(reservation.startDate, formatter: dateFormatter)")
                        .font(.subheadline)
                    Text("End: \(reservation.endDate, formatter: dateFormatter)")
                        .font(.subheadline)
                }
                .padding([.top, .bottom], 8)
                .swipeActions {
                    Button(role: .destructive) {
                        reservationToDelete = reservation
                        showingAlert = true
                    } label: {
                        Label("Delete", systemImage: "trash")
                    }
                }
                .background(
                    NavigationLink(destination: EditRentalView(reservation: reservation)) {
                        EmptyView()
                    }
                    .opacity(0)
                )
            }
        }
        .navigationTitle("All Rentals")
        .alert(isPresented: $showingAlert) {
            Alert(
                title: Text("Confirm Deletion"),
                message: Text("Are you sure you want to delete this reservation?"),
                primaryButton: .destructive(Text("Delete")) {
                    if let reservation = reservationToDelete {
                        ReservationController.deleteReservation(id: reservation.id, repository: reservationRepository)
                    }
                },
                secondaryButton: .cancel()
            )
        }
    }
}
