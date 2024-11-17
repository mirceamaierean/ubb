//
//  User.swift
//  Rental
//
//  Created by Mircea Maierean on 05.11.2024.
//

import Foundation

class User: ObservableObject {
    let id: UUID
    let name: String
    let dateOfBirth: Date
    
    init(
        id: UUID = UUID(),
        name: String = "",
        dateOfBirth: Date = Date()
    ) {
        self.id = id
        self.name = name
        self.dateOfBirth = dateOfBirth
    }
}
