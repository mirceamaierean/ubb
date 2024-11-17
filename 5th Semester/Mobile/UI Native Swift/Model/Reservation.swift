//
//  Reservation.swift
//  Rental
//
//  Created by Mircea Maierean on 05.11.2024.
//

import Foundation
import SwiftData

class Reservation {
    var id: UUID
    var carId: Int
    var userId: UUID
    var totalPrice: Int
    var startDate: Date
    var endDate: Date
    
    init(
        id: UUID = UUID(),
        carId: Int,
        userId: UUID,
        totalPrice: Int = 0,
        startDate: Date = Date(),
        endDate: Date = Date()
    ) {
        self.id = id
        self.carId = carId
        self.userId = userId
        self.totalPrice = totalPrice
        self.startDate = startDate
        self.endDate = endDate
    }
}
