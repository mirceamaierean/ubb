#pragma once
#include "Service.h"
#include "FileWatchList.h"
#include <iostream>
#include <string>

namespace OPTIONS
{
  namespace STORAGE_TYPE
  {
    const std::string FILE = "1";
    const std::string STORAGE_FILE_NAME = "movies.txt";
    const std::string DATABASE = "2";
    const std::string STORAGE_DATABASE_NAME = "movies.db";
  }
  namespace FILE_TYPE
  {
    const std::string CSV = "1";
    const std::string HTML = "2";
  }
  namespace INTERFACE
  {
    const std::string ADMIN = "1";
    const std::string USER = "2";
  }
  namespace ADMIN
  {
    const std::string ADD_MOVIE = "1";
    const std::string REMOVE_MOVIE = "2";
    const std::string UPDATE_MOVIE = "3";
    const std::string PRINT_ALL_MOVIES = "4";
    const std::string SWITCH_TO_USER_INTERFACE = "5";
    const std::string EXIT = "6";
  }
  namespace USER
  {
    const std::string GET_MOVIES_BY_GENRE = "1";
    const std::string DISPLAY_WATCHLIST = "2";
    const std::string DELETE_MOVIE_FROM_WATCHLIST = "3";
    const std::string SWITCH_TO_ADMIN_INTERFACE = "4";
    const std::string EXIT = "5";
  }
  const std::string EXIT_APPLICATION = "3";
}

class UI
{
private:
  Service service;

public:
  UI();
  ~UI(){};
  void chooseStorageType();
  void choseFileTypeWatchList();
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