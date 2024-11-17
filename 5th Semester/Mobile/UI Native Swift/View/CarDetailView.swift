//
//  CarDetailView.swift
//  Rental
//
//  Created by Mircea Maierean on 07.11.2024.
//
import SwiftUI

struct CarDetailView: View {
    @EnvironmentObject var reservationRepository: InMemoryReservationRepository
    @EnvironmentObject var user: User

    let car: Car
    @State private var startDate = Date()
    @State private var endDate = Date().addingTimeInterval(86400)
    @State private var showingSuccessAlert = false

    private var totalPrice: Int {
        let days = Calendar.current.dateComponents([.day], from: startDate, to: endDate).day ?? 0
        return days * car.pricePerDay
    }

    var body: some View {
        ScrollView {
            VStack(spacing: 20) {
                if let imageName = car.photo {
                    Image(imageName)
                        .resizable()
                        .scaledToFill()
                        .frame(height: 250)
                        .clipped()
                        .cornerRadius(12)
                        .padding([.leading, .trailing], 16)
                } else {
                    Rectangle()
                        .fill(Color.gray)
                        .frame(height: 250)
                        .cornerRadius(12)
                        .padding([.leading, .trailing], 16)
                }

                VStack(alignment: .leading, spacing: 12) {
                    Text("\(car.make) \(car.model)")
                        .font(.title2)
                        .fontWeight(.bold)

                    Text("Price per day: $\(car.pricePerDay)")
                        .font(.subheadline)
                        .foregroundColor(.gray)

                    Text("Total price: $\(totalPrice)")
                        .font(.subheadline)
                        .foregroundColor(.gray)

                    Text("Color: \(car.color)")
                        .font(.subheadline)

                    Text("Body type: \(car.bodyType)")
                        .font(.subheadline)

                    Text("Fuel type: \(car.carburantType)")
                        .font(.subheadline)

                    Text("Year: \(String(format: "%d", car.productionYear))")
                        .font(.subheadline)
                }
                .padding([.leading, .trailing], 16)

                VStack(spacing: 16) {
                    VStack(alignment: .leading, spacing: 8) {
                        Text("Start Date")
                            .font(.headline)

                        DatePicker(
                            "Select Start Date",
                            selection: $startDate,
                            in: Date()...,
                            displayedComponents: [.date]
                        )
                        .padding(.horizontal)
                        .onChange(of: startDate) { newStartDate in
                            if endDate <= newStartDate {
                                endDate = Calendar.current.date(byAdding: .day, value: 1, to: newStartDate) ?? newStartDate
                            }
                        }
                    }

                    VStack(alignment: .leading, spacing: 8) {
                        Text("End Date")
                            .font(.headline)

                        DatePicker(
                            "Select End Date",
                            selection: $endDate,
                            in: startDate.addingTimeInterval(86400)...,
                            displayedComponents: [.date]
                        )
                        .padding(.horizontal)
                    }
                }

                Button(action: {
                    ReservationController.createReservation(
                        carId: car.id,
                        userId: user.id,
                        startDate: startDate,
                        endDate: endDate,
                        pricePerDay: car.pricePerDay,
                        repository: reservationRepository
                    )
                    showingSuccessAlert = true
                }) {
                    Text("Reserve Car")
                        .font(.headline)
                        .padding()
                        .frame(maxWidth: .infinity)
                        .background(Color.blue)
                        .foregroundColor(.white)
                        .cornerRadius(10)
                        .shadow(radius: 5)
                        .padding([.leading, .trailing], 16)
                }
                .alert(isPresented: $showingSuccessAlert) {
                    Alert(
                        title: Text("Reservation Successful"),
                        message: Text("Your reservation has been successfully created."),
                        dismissButton: .default(Text("OK"))
                    )
                }

                Spacer()
            }
            .navigationTitle("\(car.make) \(car.model)")
            .navigationBarTitleDisplayMode(.inline)
        }
    }
}
