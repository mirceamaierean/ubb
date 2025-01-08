use serde::{Deserialize, Serialize};

#[derive(Serialize, Debug)]
pub struct Car {
    pub id: i32,
    pub make: String,
    pub model: String,
    pub color: String,
    pub productionYear: i32,
    pub carburantType: String,
    pub bodyType: String,
    pub pricePerDay: i32,
    pub photoPath: String,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Reservation {
    pub id: String,
    pub carId: i32,
    pub userId: String,
    pub startDate: String,
    pub endDate: String,
    pub totalPrice: i32,
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Action {
    pub id: String,
    pub actionType: String,
    pub createdAt: String,
    pub reservation: Reservation,
}

#[derive(Deserialize)]
pub struct ReservationsQuery {
    pub id: String,
}
