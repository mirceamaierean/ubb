// src/app/reservations/reservations.component.ts
import { Component, OnInit } from '@angular/core';
import { ReservationService } from '../reservation.service';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-reservations',
  templateUrl: './reservations.component.html',
  styleUrls: ['../../styles.css'],
})
export class ReservationsComponent implements OnInit {
  reservations: any[] = [];
  currentPage = 0;
  pageSize = 4;

  constructor(
    private reservationService: ReservationService,
    private authService: AuthService
  ) {}

  ngOnInit(): void {
    this.authService.currentUserName;
    this.loadReservations(this.authService.currentUserName);
  }

  loadReservations(userName: string): void {
    this.reservationService
      .getReservationsByUserName(userName)
      .subscribe((data) => {
        this.reservations = data;
      });
  }

  deleteReservation(id: number): void {
    if (confirm('Are you sure you want to delete this reservation?')) {
      this.reservationService.deleteReservation(id).subscribe(
        () => {
          this.reservations = this.reservations.filter(
            (reservation) => reservation.id !== id
          );
        },
        (error) => {
          alert('Could not delete the reservation!');
        }
      );
    }
  }

  editReservation(id: number): void {
    window.location.href = `edit-reservation?id=${id}`;
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
    return Math.ceil(this.reservations.length / this.pageSize);
  }

  getCurrentPageItems(): any[] {
    const start = this.currentPage * this.pageSize;
    const end = start + this.pageSize;
    return this.reservations.slice(start, end);
  }

  goToMainPage(): void {
    this.reservationService.goToMainPage();
  }
}
