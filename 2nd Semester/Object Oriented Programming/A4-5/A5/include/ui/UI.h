#pragma once
#include "../service/Service.h"
#include <iostream>
#include <string>

class UI
{
private:
  const int ADMIN_INTERFACE = 1;
  const int USER_INTERFACE = 2;
  const int EXIT_APPLICATION = 3;
  const int ADMIN_ADD_MOVIE = 1;
  const int ADMIN_REMOVE_MOVIE = 2;
  const int ADMIN_UPDATE_MOVIE = 3;
  const int ADMIN_PRINT_ALL_MOVIES = 4;
  const int ADMIN_EXIT = 5;
  const int USER_GET_MOVIES_BY_GENRE = 1;
  const int USER_DISPLAY_WATCHLIST = 2;
  const int USER_DELETE_MOVIE_FROM_WATCHLIST = 3;
  const int USER_EXIT = 4;
  Service service;

public:
  UI();
  ~UI();
  void printInitialMenu();
  void printAdminMenu();
  void printUserMenu();
  void runApp();
  void printAllMovies();
  void adminAddMovie();
  void adminRemoveMovie();
  void adminUpdateMovie();
  void userGetMoviesByGenre();
  void userDisplayMoviesFromWatchList();
  void userDeleteMovieFromWatchList();
};