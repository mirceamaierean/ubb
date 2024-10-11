// src/app/hotel.service.ts
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root',
})
export class HotelService {
  private baseUrl = 'http://localhost:5169';

  constructor(private http: HttpClient) {}

  getAllHotels(): Observable<any> {
    return this.http.get(`${this.baseUrl}/api/Hotels`);
  }

  getHotelByName(name: string): Observable<any> {
    return this.http.get(`${this.baseUrl}/api/Hotels/${name}`);
  }

  getHotelByAddress(address: string): Observable<any> {
    return this.http.get(`${this.baseUrl}/api/Hotels/address/${address}`);
  }

  insertHotel(name: string, address: string): Observable<any> {
    const params = new URLSearchParams({
      action: 'insertHotel',
      name,
      address,
    });
    return this.http.get(`${this.baseUrl}?${params.toString()}`);
  }
}
