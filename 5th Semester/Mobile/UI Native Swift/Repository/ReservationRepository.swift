//
//  ReservationRepository.swift
//  Rental
//
//  Created by Mircea Maierean on 09.11.2024.
//

import Foundation

protocol ReservationRepository {
    func getAllReservations() -> [Reservation]
    func getReservation(id: UUID) -> Reservation?
    func addReservation(_ reservation: Reservation)
    func updateReservation(reservation: Reservation)
    func deleteReservation(id: UUID)
}

