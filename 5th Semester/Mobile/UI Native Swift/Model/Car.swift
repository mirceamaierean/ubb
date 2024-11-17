//
//  Car.swift
//  Rental
//
//  Created by Mircea Maierean on 05.11.2024.
//

import Foundation
import SwiftData

struct Car: Identifiable, Decodable {
    var id: Int
    var make: String
    var model: String
    var color: String
    var productionYear: Int
    var carburantType: String
    var bodyType: String
    var pricePerDay: Int
    var photo: String?  
}
