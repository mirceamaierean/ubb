// src/app/hotel.service.ts
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root',
})
export class HotelService {
  private baseUrl = 'http://localhost/hw/DBUtils.php';

  constructor(private http: HttpClient) {}

  getAllHotels(): Observable<any> {
    return this.http.get(`${this.baseUrl}?action=getAllHotels`);
  }

  getHotelByName(name: string): Observable<any> {
    const params = new URLSearchParams({
      action: 'getHotelByName',
      hotel: name,
    });
    return this.http.get(`${this.baseUrl}?${params.toString()}`);
  }

  getHotelByAddress(address: string): Observable<any> {
    const params = new URLSearchParams({
      action: 'getHotelByAddr',
      address,
    });
    return this.http.get(`${this.baseUrl}?${params.toString()}`);
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
