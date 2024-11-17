//
//  RepositoryController.swift
//  Rental
//
//  Created by Mircea Maierean on 09.11.2024.
//
import Foundation

class ReservationController {
    static func createReservation(
        carId: Int,
        userId: UUID,
        startDate: Date,
        endDate: Date,
        pricePerDay: Int,
        repository: InMemoryReservationRepository
    )
    {
        let totalPrice = pricePerDay * totalDays(startDate: startDate, endDate: endDate)
        let reservation = Reservation(
            carId: carId,
            userId: userId,
            totalPrice: totalPrice,
            startDate: startDate,
            endDate: endDate
        )
        repository.addReservation(reservation)
    }
    
    static func totalDays(startDate: Date, endDate: Date) -> Int {
        let days = Calendar.current.dateComponents([.day], from: startDate, to: endDate).day ?? 0
        return days
    }
    
    static func getReservations(repository: InMemoryReservationRepository) -> [Reservation] { 
        return repository.getAllReservations()
    }
    
    static func deleteReservation(id: UUID, repository: InMemoryReservationRepository) {
        repository.deleteReservation(id: id)
    }
    
    static func getReservation(id: UUID, repository: InMemoryReservationRepository) -> Reservation? {
        return repository.getReservation(id: id)
    }
    
   static func updateReservation(reservation: Reservation, repository: InMemoryReservationRepository) {
       if let index = repository.reservations.firstIndex(where: { $0.id == reservation.id }) {
           repository.reservations[index] = reservation
       }
   }
}
