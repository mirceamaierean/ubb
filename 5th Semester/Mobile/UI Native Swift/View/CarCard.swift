//
//  CarCard.swift
//  Rental
//
//  Created by Mircea Maierean on 07.11.2024.
//

import SwiftUI

struct CarCard: View {
    var car: Car

    var body: some View {
        VStack(alignment: .leading) {
            if let imageName = car.photo {
                Image(imageName)
                    .resizable()
                    .scaledToFill()
                    .frame(height: 150)
                    .clipped()
                    .cornerRadius(8)
            } else {
                Rectangle()
                    .fill(Color.gray)
                    .frame(height: 150)
                    .cornerRadius(8)
            }

            VStack(alignment: .leading, spacing: 8) {
                Text("\(car.make) \(car.model)")
                    .font(.title3)
                    .fontWeight(.semibold)

                Text("Price per day: $\(car.pricePerDay)")
                    .font(.subheadline)
                    .foregroundColor(.gray)

                Text("Color: \(car.color)")
                    .font(.subheadline)

                Text("Body type: \(car.bodyType)")
                    .font(.subheadline)

                Text("Year: \(String(format: "%d", car.productionYear))")
                    .font(.subheadline)
            }
            .padding(.top, 8)
            .padding([.leading, .trailing], 4)
            .frame(maxWidth: .infinity, alignment: .leading)
        }
        .padding()
        .background(Color.white)
        .cornerRadius(12)
        .shadow(radius: 5)
    }
}
