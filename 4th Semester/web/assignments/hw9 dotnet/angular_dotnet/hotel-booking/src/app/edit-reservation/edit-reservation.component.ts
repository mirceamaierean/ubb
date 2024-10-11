// src/app/edit-reservation/edit-reservation.component.ts
import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { ReservationService } from '../reservation.service';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-edit-reservation',
  templateUrl: './edit-reservation.component.html',
  styleUrls: ['../../styles.css'],
})
export class EditReservationComponent implements OnInit {
  id: number = 0;
  startDate: string = '';
  endDate: string = '';

  constructor(
    private reservationService: ReservationService,
    private route: ActivatedRoute,
    private router: Router,
    private service: AuthService
  ) {}

  ngOnInit(): void {
    this.service.currentUserName;
    this.route.queryParams.subscribe((params) => {
      this.id = +params['id'];
      if (!this.id) {
        alert('Invalid ID!');
        this.router.navigate(['/dashboard']);
      }
      this.loadReservationDetails();
    });
  }

  loadReservationDetails(): void {
    this.reservationService
      .getReservationById(this.id)
      .subscribe((reservation) => {
        this.startDate = reservation.start_date;
        this.endDate = reservation.end_date;
      });
  }

  editReservation(): void {
    if (this.startDate < this.endDate) {
      this.reservationService
        .editReservation(this.id, this.startDate, this.endDate)
        .subscribe({
          next: (result) => {
            if (result === 0) {
              alert('Reservation could not be edited!');
            } else {
              alert('Reservation edited successfully!');
              this.router.navigate(['/list-reservations']);
            }
          },
          error: () => {
            alert('Error updating reservation!');
          },
        });
    } else {
      alert(
        'Please enter valid dates where the start date is before the end date.'
      );
    }
  }

  viewAllReservations(): void {
    this.router.navigate(['/reservations']);
  }

  returnToMainPage(): void {
    this.router.navigate(['/']);
  }
}
