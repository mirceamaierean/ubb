use rusqlite::Result;

use crate::models::{Car, Reservation};
use r2d2::Pool;
use r2d2_sqlite::SqliteConnectionManager;
use std::sync::Arc;
use tracing::info;

#[derive(Debug)]
pub struct DBHelper {
    pool: Arc<Pool<SqliteConnectionManager>>,
}

impl DBHelper {
    pub fn new(db_path: &str) -> Self {
        let manager = SqliteConnectionManager::file(db_path);
        let pool = Pool::new(manager).expect("Failed to create connection pool");
        Self {
            pool: Arc::new(pool),
        }
    }

    pub fn get_all_cars(&self) -> Result<Vec<Car>> {
        let conn = self.pool.get().unwrap();
        let mut statement = conn.prepare("SELECT * FROM cars").unwrap();
        info!("Query for getting all cars exectued\n");
        let cars = statement
            .query_map([], |row| {
                Ok(Car {
                    id: row.get("id")?,
                    make: row.get("make")?,
                    model: row.get("model")?,
                    color: row.get("color")?,
                    productionYear: row.get("productionYear")?,
                    carburantType: row.get("carburantType")?,
                    bodyType: row.get("bodyType")?,
                    pricePerDay: row.get("pricePerDay")?,
                    photoPath: row.get("photoPath")?,
                })
            })?
            .collect::<Result<Vec<Car>>>()?;

        Ok(cars)
    }

    pub fn get_reservations_for_user(&self, user_id: &str) -> Result<Vec<Reservation>> {
        let conn = self.pool.get().unwrap();
        let mut statement = conn.prepare("SELECT * FROM reservations WHERE userId = ?")?;
        info!("Query for getting reservations exectued\n");
        let reservations = statement
            .query_map([user_id], |row| {
                Ok(Reservation {
                    id: row.get("id")?,
                    carId: row.get("carId")?,
                    userId: row.get("userId")?,
                    startDate: row.get("startDate")?,
                    endDate: row.get("endDate")?,
                    totalPrice: row.get("totalPrice")?,
                })
            })?
            .collect::<Result<Vec<Reservation>>>()?;

        info!("Reservations: {:?}\n", reservations);

        Ok(reservations)
    }

    pub fn insert_reservation(&self, reservation: &Reservation) -> Result<()> {
        let conn = self.pool.get().unwrap();
        let mut statement = conn.prepare("INSERT INTO reservations (id, carId, userId, startDate, endDate, totalPrice) VALUES (?, ?, ?, ?, ?, ?)")?;
        statement.execute([
            reservation.id.clone(),
            reservation.carId.to_string(),
            reservation.userId.clone(),
            reservation.startDate.clone(),
            reservation.endDate.clone(),
            reservation.totalPrice.to_string(),
        ])?;

        info!("Query for inserting reservation executed\n");
        Ok(())
    }

    pub fn update_reservation(&self, reservation: &Reservation) -> Result<()> {
        let conn = self.pool.get().unwrap();
        let mut statement = conn.prepare(
            "UPDATE reservations SET startDate = ?, endDate = ?, totalPrice = ? WHERE id = ?",
        )?;

        statement.execute([
            reservation.startDate.clone(),
            reservation.endDate.clone(),
            reservation.totalPrice.to_string(),
            reservation.id.clone(),
        ])?;

        info!("Query for updating reservation exectued\n");

        Ok(())
    }

    pub fn delete_reservation(&self, reservation_id: &str) -> Result<()> {
        let conn = self.pool.get().unwrap();
        let mut statement = conn.prepare("DELETE FROM reservations WHERE id = ?")?;
        statement.execute([reservation_id])?;

        info!("Query for deleting reservation exectued\n");

        Ok(())
    }
}
