//
//  ContentView.swift
//  Rental
//
//  Created by Mircea Maierean on 05.11.2024.
//
import SwiftUI

struct ContentView: View {
    @EnvironmentObject var currentUser: User
    @EnvironmentObject var reservationRepository: InMemoryReservationRepository

    var body: some View {
        NavigationView {
            VStack(spacing: 24) {
                HStack {
                    Image(systemName: "person.circle.fill")
                        .resizable()
                        .scaledToFit()
                        .frame(width: 50, height: 50)
                        .foregroundColor(.blue)

                    Text(currentUser.name)
                        .font(.headline)
                        .padding(.leading, 8)

                    Spacer()
                }
                .padding([.leading, .trailing], 16)
                
                Text("Welcome to the Rental App!")
                    .font(.title)
                    .fontWeight(.bold)
                    .padding(.top, 8)

                VStack(spacing: 16) {
                    NavigationLink(destination: CarListView()) {
                        Text("View Available Cars")
                            .font(.headline)
                            .padding()
                            .frame(maxWidth: .infinity)
                            .background(Color.blue)
                            .foregroundColor(.white)
                            .cornerRadius(10)
                            .shadow(radius: 5)
                    }

                    NavigationLink(destination: RentalsListView()) {
                        Text("View My Rentals")
                            .font(.headline)
                            .padding()
                            .frame(maxWidth: .infinity)
                            .background(Color.green)
                            .foregroundColor(.white)
                            .cornerRadius(10)
                            .shadow(radius: 5)
                    }
                }
                .padding([.leading, .trailing], 16)

                Spacer()
            }
            .navigationTitle("Profile")
            .navigationBarTitleDisplayMode(.inline) 
        }
    }
}
