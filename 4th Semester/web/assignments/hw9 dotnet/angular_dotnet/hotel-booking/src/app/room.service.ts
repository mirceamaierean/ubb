// src/app/room.service.ts
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';
import { Router } from '@angular/router';

@Injectable({
  providedIn: 'root',
})
export class RoomService {
  private baseUrl = 'http://localhost:5169';

  constructor(private http: HttpClient, private router: Router) {}

  getAllRooms(): Observable<any> {
    return this.http.get(`${this.baseUrl}/api/Rooms`);
  }

  getRoomsByCategory(category: string): Observable<any> {
    return this.http.get(`${this.baseUrl}/api/Rooms/category/${category}`);
  }

  getRoomsByPrice(price: string): Observable<any> {
    return this.http.get(`${this.baseUrl}/api/Rooms/price/${price}`);
  }

  goToMainPage(): void {
    this.router.navigate(['/dashboard']);
  }

  insertRoom(
    hotelId: number,
    roomNumber: number,
    category: string,
    price: number
  ): Observable<any> {
    const params = new URLSearchParams({
      action: 'insertRoom',
      hotel_id: hotelId.toString(),
      room_number: roomNumber.toString(),
      category,
      price: price.toString(),
    });
    return this.http.get(`${this.baseUrl}?${params.toString()}`);
  }
}
