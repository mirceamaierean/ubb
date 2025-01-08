// src/app/hotels/hotels.component.ts
import { Component, OnInit } from '@angular/core';
import { HotelService } from '../hotel.service';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-hotels',
  templateUrl: './hotels.component.html',
  styleUrls: ['../../styles.css'],
})
export class HotelsComponent implements OnInit {
  hotels: any[] = [];
  currentPage = 0;
  pageSize = 4;
  nameFilter: string = '';
  addressFilter: string = '';

  constructor(
    private hotelService: HotelService,
    private authService: AuthService
  ) {}

  ngOnInit(): void {
    this.authService.currentUserName;
    this.loadHotels();
  }

  loadHotels(): void {
    this.hotelService.getAllHotels().subscribe((data) => {
      this.hotels = data;
      this.currentPage = 0;
    });
  }

  filterByName(name: string): void {
    this.hotelService.getHotelByName(name).subscribe((data) => {
      this.hotels = data;
      this.currentPage = 0;
    });
  }

  filterByAddress(address: string): void {
    this.hotelService.getHotelByAddress(address).subscribe((data) => {
      this.hotels = data;
      this.currentPage = 0;
    });
  }

  addRoom(hotelId: number): void {
    window.location.href = `add-room?hotel_id=${hotelId}`;
  }

  goToPreviousPage(): void {
    if (this.currentPage > 0) {
      this.currentPage--;
    }
  }

  goToNextPage(): void {
    if (this.currentPage < this.getPageCount() - 1) {
      this.currentPage++;
    }
  }

  getPageCount(): number {
    return Math.ceil(this.hotels.length / this.pageSize);
  }

  getCurrentPageItems(): any[] {
    const start = this.currentPage * this.pageSize;
    const end = start + this.pageSize;
    return this.hotels.slice(start, end);
  }
}
