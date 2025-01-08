// src/app/dashboard/dashboard.component.ts
import { Component, OnInit } from '@angular/core';
import { AuthService } from '../auth.service';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['../../styles.css'],
})
export class DashboardComponent implements OnInit {
  username: string = '';
  router: any;

  constructor(private authService: AuthService) {}

  ngOnInit(): void {
    this.username = this.authService.currentUserName;
  }

  logout(): void {
    this.authService.logout();
  }
}
