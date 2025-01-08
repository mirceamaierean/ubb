// src/app/reservation.service.ts
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Router } from '@angular/router';

@Injectable({
  providedIn: 'root',
})
export class ReservationService {
  private baseUrl = 'http://localhost:80/hw/DBUtils.php';

  constructor(private http: HttpClient, private router: Router) {}

  getReservationById(reservationId: number): Observable<any> {
    const params = new URLSearchParams({
      action: 'getReservationById',
      id: reservationId.toString(),
    });

    return this.http.get(`${this.baseUrl}?${params.toString()}`);
  }

  getReservationsByUserName(userName: string): Observable<any> {
    const params = new URLSearchParams({
      action: 'getReservationByUserName',
      user_name: userName,
    });

    return this.http.get(`${this.baseUrl}?${params.toString()}`);
  }

  deleteReservation(reservationId: number): Observable<any> {
    const params = new URLSearchParams({
      action: 'deleteReservation',
      id: reservationId.toString(),
    });
    return this.http.get(`${this.baseUrl}?${params.toString()}`);
  }

  insertReservation(
    roomId: number,
    userName: string,
    startDate: string,
    endDate: string
  ): Observable<any> {
    const params = new URLSearchParams({
      action: 'insertReservation',
      room_id: roomId.toString(),
      user_name: userName,
      start_date: startDate,
      end_date: endDate,
    });
    return this.http.get(`${this.baseUrl}?${params.toString()}`);
  }

  editReservation(
    id: number,
    startDate: string,
    endDate: string
  ): Observable<any> {
    const params = new URLSearchParams({
      action: 'editReservation',
      id: id.toString(),
      start_date: startDate,
      end_date: endDate,
    });
    return this.http.get(`${this.baseUrl}?${params.toString()}`);
  }

  goToMainPage(): void {
    this.router.navigate(['/dashboard']);
  }
}
