//
//  EditRentalView.swift
//  Rental
//
//  Created by Mircea Maierean on 10.11.2024.
//

import SwiftUI

struct EditRentalView: View {
    @EnvironmentObject var reservationRepository: InMemoryReservationRepository
    @EnvironmentObject var carRepository: CarRepository
    @EnvironmentObject var currentUser: User
    
    @State private var startDate: Date
    @State private var endDate: Date
    
    let reservation: Reservation
    
    init(reservation: Reservation) {
        self.reservation = reservation
        _startDate = State(initialValue: reservation.startDate)
        _endDate = State(initialValue: reservation.endDate)
    }
    
    var body: some View {
        VStack(spacing: 16) {
            if let car = carRepository.getCar(byId: reservation.carId) {
                VStack(alignment: .leading, spacing: 8) {
                    Text("Car Details")
                        .font(.title2)
                        .fontWeight(.bold)
                        .padding(.bottom, 8)
                    
                    Text("Make: \(car.make)")
                        .font(.headline)
                    
                    Text("Model: \(car.model)")
                        .font(.subheadline)
                    
                    Text("Color: \(car.color)")
                        .font(.subheadline)
                    
                    Text("Price per Day: $\(car.pricePerDay)")
                        .font(.subheadline)
                    
                    Text("Total Price: $\(calculateTotalPrice(startDate: startDate, endDate: endDate, price: car.pricePerDay))")
                        .font(.subheadline)
                        .foregroundColor(.blue)
                        .fontWeight(.semibold)
                    
                    HStack {
                        Spacer()
                    }               
                }
                .padding()
                .background(Color(UIColor.secondarySystemBackground))
                .cornerRadius(10)
                .frame(
                    minWidth: 0,
                    maxWidth: .infinity,
                    minHeight: 0,
                    maxHeight: .infinity,
                    alignment: .topLeading
                )
                .padding(.horizontal)
            } else {
                Text("Car details not found.")
                    .font(.headline)
                    .foregroundColor(.red)
            }
            
            VStack(alignment: .leading, spacing: 8) {
                Text("Start Date")
                    .font(.headline)
                
                DatePicker(
                    "Select Start Date",
                    selection: $startDate,
                    in: Date()...,
                    displayedComponents: [.date]
                )
                .onChange(of: startDate) { _ in
                    if endDate <= startDate {
                        if let nextDay = Calendar.current.date(byAdding: .day, value: 1, to: startDate) {
                            endDate = nextDay;
                        }
                    }
                }
                .padding(.horizontal)
            }
            
            VStack(alignment: .leading, spacing: 8) {
                Text("End Date")
                    .font(.headline)
                
                DatePicker(
                    "Select End Date",
                    selection: $endDate,
                    in: startDate...,
                    displayedComponents: [.date]
                )
                .padding(.horizontal)
            }
            
            Button(action: {
                if let car = carRepository.getCar(byId: reservation.carId) {
                    let updatedTotalPrice = calculateTotalPrice(
                        startDate: startDate,
                        endDate: endDate,
                        price: car.pricePerDay
                    )
                    
                    let updatedReservation = Reservation(
                        id: reservation.id,
                        carId: reservation.carId,
                        userId: reservation.userId,
                        totalPrice: updatedTotalPrice,
                        startDate: startDate,
                        endDate: endDate
                    )
                    
                    ReservationController.updateReservation(reservation: updatedReservation, repository: reservationRepository)
                }
            }) {
                Text("Save Changes")
                    .font(.headline)
                    .padding()
                    .frame(maxWidth: .infinity)
                    .background(Color.blue)
                    .foregroundColor(.white)
                    .cornerRadius(8)
            }
            .padding(.horizontal)
            .padding(.top)
            
            Spacer()
        }
        .padding()
        .navigationTitle("Edit Rental")
    }
    
    private func calculateTotalPrice(startDate: Date, endDate: Date, price: Int) -> Int {
        return price * ReservationController.totalDays(startDate: startDate, endDate: endDate)
    }
}
