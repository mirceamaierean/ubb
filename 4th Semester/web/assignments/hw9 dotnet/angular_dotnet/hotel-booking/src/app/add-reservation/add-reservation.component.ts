// src/app/add-reservation/add-reservation.component.ts
import { Component } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { ReservationService } from '../reservation.service';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-add-reservation',
  templateUrl: './add-reservation.component.html',
  styleUrls: ['../../styles.css'],
})
export class AddReservationComponent {
  startDate: string = '';
  endDate: string = '';
  roomId: number;

  constructor(
    private reservationService: ReservationService,
    private route: ActivatedRoute,
    private router: Router,
    private authService: AuthService
  ) {
    this.roomId = Number(this.route.snapshot.queryParamMap.get('id'));
  }

  ngOnInit() {
    this.authService.currentUserName;
    if (!this.roomId || isNaN(this.roomId)) {
      alert('Room ID is not valid!');
      this.router.navigate(['/dashboard']);
    }
  }

  addReservation(): void {
    if (this.startDate < this.endDate) {
      const user_name = this.authService.currentUserName;
      if (!user_name) {
        alert('User not logged in!');
        return;
      }
      this.reservationService
        .insertReservation(this.roomId, user_name, this.startDate, this.endDate)
        .subscribe({
          next: (res) => {
            if (res === 0) {
              alert('Reservation could not be added!');
            } else {
              this.startDate = '';
              this.endDate = '';
              alert('Reservation added successfully!');
              this.router.navigate(['/reservations']);
            }
          },
          error: () => alert('Error adding reservation'),
        });
    } else {
      alert('End date must be after start date!');
    }
  }

  viewAllReservations(): void {
    this.router.navigate(['/list-reservations']);
  }

  returnToMainPage(): void {
    this.router.navigate(['/dashboard']);
  }
}
