//
//  DatePickerView.swift
//  Rental
//
//  Created by Mircea Maierean on 10.11.2024.
//

import Foundation
import SwiftUI

struct DatePickerView: View {
    @Binding var selectedDate: Date

    @Environment(\.dismiss) var dismiss
    var body: some View {
        VStack {
            DatePicker(
                "Select Date",
                selection: $selectedDate,
                displayedComponents: [.date]
            )
            .datePickerStyle(GraphicalDatePickerStyle())
            .padding()

            Button("Done") {
                dismiss()
            }
            .padding()
            .background(Color.blue)
            .foregroundColor(.white)
            .cornerRadius(8)
        }
    }
}

let dateFormatter: DateFormatter = {
    let formatter = DateFormatter()
    formatter.dateStyle = .short
    return formatter
}()

