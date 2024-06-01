// src/app/add-room/add-room.component.ts
import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { RoomService } from '../room.service';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-add-room',
  templateUrl: './add-room.component.html',
  styleUrls: ['../../styles.css'],
})
export class AddRoomComponent {
  roomNumber: string = '';
  category: string = '';
  price: string = '';
  hotelId: number;

  constructor(
    private roomService: RoomService,
    private router: Router,
    private route: ActivatedRoute,
    private service: AuthService
  ) {
    this.hotelId = Number(this.route.snapshot.queryParamMap.get('hotel_id'));
  }

  ngOnInit() {
    this.service.currentUserName;
    if (!this.hotelId || isNaN(this.hotelId)) {
      alert('Hotel id is not valid!');
      this.router.navigate(['/']);
    }
  }

  addRoom(): void {
    const roomNumberParsed = parseInt(this.roomNumber, 10);
    const priceParsed = parseFloat(this.price);

    if (
      isNaN(roomNumberParsed) ||
      this.category.trim().length === 0 ||
      isNaN(priceParsed)
    ) {
      alert('Please enter valid data in all fields!');
      return;
    }

    this.roomService
      .insertRoom(this.hotelId, roomNumberParsed, this.category, priceParsed)
      .subscribe({
        next: (res) => {
          if (res === 0) {
            alert('Room could not be added!');
          } else {
            this.roomNumber = '';
            this.category = '';
            this.price = '';
            alert('Room added successfully!');
          }
        },
        error: () => alert('Error adding room'),
      });
  }

  viewAllRooms(): void {
    this.router.navigate(['/list-rooms']);
  }

  returnToMainPage(): void {
    this.router.navigate(['/dashboard']);
  }
}
