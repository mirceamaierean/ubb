// src/app/auth.service.ts
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { BehaviorSubject, Observable } from 'rxjs';
import { map } from 'rxjs/operators';
import { Router } from '@angular/router';
import { CookieService } from 'ngx-cookie-service';

@Injectable({
  providedIn: 'root',
})
export class AuthService {
  constructor(
    private http: HttpClient,
    private router: Router,
    private cookieService: CookieService
  ) {}

  public get currentUserName(): string {
    let username = this.cookieService.get('username');
    if (!username) {
      alert('You need to be logged in to view this page!');
      this.router.navigate(['/login']);
    }
    return username;
  }

  login(username: string, password: string): Observable<any> {
    return this.http
      .post<any>('http://localhost/hw/login.php', { username, password })
      .pipe(
        map((response) => {
          if (response.success) {
            this.cookieService.set('username', username);
          }
          return response;
        })
      );
  }

  logout(): void {
    console.log('Logging out...');
    this.http.post('http://localhost/hw/logout.php', {});
    this.cookieService.delete('username');
    this.router.navigate(['/login']);
  }
}
