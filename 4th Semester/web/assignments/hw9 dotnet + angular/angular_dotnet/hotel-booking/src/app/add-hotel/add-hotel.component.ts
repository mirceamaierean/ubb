// src/app/add-hotel/add-hotel.component.ts
import { Component } from '@angular/core';
import { HotelService } from '../hotel.service';
import { Router } from '@angular/router';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-add-hotel',
  templateUrl: './add-hotel.component.html',
  styleUrls: ['../../styles.css'],
})
export class AddHotelComponent {
  name: string = '';
  address: string = '';

  constructor(
    private hotelService: HotelService,
    private router: Router,
    private auth: AuthService
  ) {
    this.auth.currentUserName;
  }

  addHotel(): void {
    if (this.name.trim() && this.address.trim()) {
      this.hotelService.insertHotel(this.name, this.address).subscribe({
        next: (res) => {
          if (res === 0) {
            alert('Hotel could not be added!');
          } else {
            this.name = '';
            this.address = '';
            alert('Hotel added successfully!');
          }
        },
        error: () => alert('Error adding hotel'),
      });
    } else {
      alert('Please enter valid data in all fields!');
    }
  }

  viewAllHotels(): void {
    this.router.navigate(['/list-hotels']);
  }

  returnToMainPage(): void {
    this.router.navigate(['/dashboard']);
  }
}
