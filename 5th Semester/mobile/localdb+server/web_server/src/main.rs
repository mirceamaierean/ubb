mod db;
mod models;

use actix_web::{
    web::{delete, get, patch, post, Data, Json, Query},
    App, HttpResponse, HttpServer, Responder,
};
use db::DBHelper;
use dotenv::dotenv;
use models::{Action, Reservation, ReservationsQuery};
use std::{env, io::Result, sync::Arc, thread};
use tracing::{error, info};

// Handler function
async fn get_cars_handler(db_helper: Data<Arc<db::DBHelper>>) -> impl Responder {
    let cars = db_helper.get_all_cars();
    info!("Handling GET /cars on thread {:?}", thread::current().id());

    match cars {
        Ok(cars) => HttpResponse::Ok().json(cars),
        Err(_) => HttpResponse::InternalServerError().finish(),
    }
}

async fn get_reservations_for_user_handler(
    db_helper: Data<Arc<db::DBHelper>>,
    query: Query<ReservationsQuery>,
) -> impl Responder {
    let user_id = &query.id;
    info!("User ID: {:?}\n", user_id);

    let reservations = db_helper.get_reservations_for_user(user_id);

    info!(
        "Handling GET /reservations on thread {:?}",
        thread::current().id()
    );

    match reservations {
        Ok(reservations) => HttpResponse::Ok().json(reservations),
        Err(_) => HttpResponse::InternalServerError().finish(),
    }
}

async fn insert_reservation_handler(
    db_helper: Data<Arc<db::DBHelper>>,
    query: Json<Reservation>,
) -> impl Responder {
    let reservation = query.into_inner();
    info!(
        "Handling POST /reservation/insert on thread {:?} for reservation: {:?}",
        thread::current().id(),
        reservation
    );
    let result = db_helper.insert_reservation(&reservation);

    match result {
        Ok(_) => HttpResponse::Ok().finish(),
        Err(_) => HttpResponse::InternalServerError().finish(),
    }
}

async fn update_reservation_handler(
    db_helper: Data<Arc<db::DBHelper>>,
    query: Json<Reservation>,
) -> impl Responder {
    let reservation = query.into_inner();

    info!(
        "Handling PATCH /reservations/update on thread {:?} Query: {:?}",
        thread::current().id(),
        reservation
    );

    let result = db_helper.update_reservation(&reservation);

    match result {
        Ok(_) => HttpResponse::Ok().finish(),
        Err(_) => HttpResponse::InternalServerError().finish(),
    }
}

async fn delete_reservation_handler(
    db_helper: Data<Arc<db::DBHelper>>,
    query: Query<ReservationsQuery>,
) -> impl Responder {
    let reservation_id = &query.id;
    info!(
        "Handling DELETE of /reservations with Reservation ID {:?} on thread {:?}",
        reservation_id,
        thread::current().id()
    );

    let result = db_helper.delete_reservation(reservation_id);

    match result {
        Ok(_) => HttpResponse::Ok().finish(),
        Err(_) => HttpResponse::InternalServerError().finish(),
    }
}

async fn sync_server(
    db_helper: Data<Arc<db::DBHelper>>,
    query: Json<Vec<Action>>,
) -> impl Responder {
    info!("Handling POST /sync on thread {:?}", thread::current().id());
    let actions = query.into_inner();
    info!("Actions: {:?}", actions);

    for action in actions {
        match action.actionType.as_str() {
            "INSERT" => {
                if let Err(e) = db_helper.insert_reservation(&action.reservation) {
                    error!("Error inserting reservation: {:?}", e);
                    return HttpResponse::InternalServerError().finish();
                }
            }
            "UPDATE" => {
                if let Err(e) = db_helper.update_reservation(&action.reservation) {
                    error!("Error updating reservation: {:?}", e);
                    return HttpResponse::InternalServerError().finish();
                }
            }
            "DELETE" => {
                if let Err(e) = db_helper.delete_reservation(&action.reservation.id) {
                    error!("Error deleting reservation: {:?}", e);
                    return HttpResponse::InternalServerError().finish();
                }
            }
            _ => {}
        }
    }

    HttpResponse::Ok().finish()
}
#[actix_web::main]
async fn main() -> Result<()> {
    dotenv().ok();

    // Load the database path from the environment
    let db_path = env::var("DB_PATH").expect("DB_PATH environment variable not set");

    // Create the DBHelper instance and wrap it in Arc
    let db_helper = Arc::new(DBHelper::new(&db_path));

    // Start the HTTP server
    HttpServer::new(move || {
        App::new()
            // Share the Arc<DBHelper> instance with the application
            .app_data(Data::new(db_helper.clone()))
            .route("/cars", get().to(get_cars_handler))
            .route("/reservations", get().to(get_reservations_for_user_handler))
            .route(
                "/reservations/insert",
                post().to(insert_reservation_handler),
            )
            .route(
                "/reservations/update",
                patch().to(update_reservation_handler),
            )
            .route("/reservations", delete().to(delete_reservation_handler))
            .route("/sync", post().to(sync_server))
    })
    .bind("127.0.0.1:8080")?
    .run()
    .await
}
