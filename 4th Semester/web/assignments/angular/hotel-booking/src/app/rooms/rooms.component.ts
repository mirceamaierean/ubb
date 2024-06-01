import { Component, OnInit } from '@angular/core';
import { RoomService } from '../room.service';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-rooms',
  templateUrl: './rooms.component.html',
  styleUrls: ['../../styles.css'],
})
export class RoomsComponent implements OnInit {
  rooms: any[] = [];
  currentPage = 0;
  pageSize = 4;
  categoryFilter: string = '';
  priceFilter: string = '';

  constructor(
    private roomService: RoomService,
    private authService: AuthService
  ) {}

  ngOnInit(): void {
    this.authService.currentUserName;
    this.loadRooms();
  }

  loadRooms(): void {
    this.roomService.getAllRooms().subscribe((data) => {
      this.rooms = data;
      this.currentPage = 0;
    });
  }

  filterByCategory(category: string): void {
    console.log(category);
    this.roomService.getRoomsByCategory(category).subscribe((data) => {
      this.rooms = data;
      this.currentPage = 0;
    });
  }

  filterByPrice(price: string): void {
    this.roomService.getRoomsByPrice(price).subscribe((data) => {
      this.rooms = data;
      this.currentPage = 0;
    });
  }

  addReservation(roomId: number): void {
    window.location.href = `add-reservation?id=${roomId}`;
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
    return Math.ceil(this.rooms.length / this.pageSize);
  }

  getCurrentPageItems(): any[] {
    const start = this.currentPage * this.pageSize;
    const end = start + this.pageSize;
    return this.rooms.slice(start, end);
  }

  goToMainPage(): void {
    this.roomService.goToMainPage();
  }
}
