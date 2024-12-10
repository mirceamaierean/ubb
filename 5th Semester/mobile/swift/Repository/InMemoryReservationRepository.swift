//
//  InMemoryReservationRepository.swift
//  Rental
//
//  Created by Mircea Maierean on 09.11.2024.
//

import Foundation

class InMemoryReservationRepository: ObservableObject {
    @Published var reservations: [Reservation] = []

    func getAllReservations() -> [Reservation] {
        return reservations
    }

    func getReservation(id: UUID) -> Reservation? {
        return reservations.first { $0.id == id }
    }

    func addReservation(_ reservation: Reservation) {
        reservations.append(reservation)
    }

    func updateReservation(reservation: Reservation) {
        if let index = reservations.firstIndex(where: { $0.id == reservation.id }) {
            reservations[index] = reservation
        }
    }

    func deleteReservation(id: UUID) {
        reservations.removeAll { $0.id == id }
    }
}
