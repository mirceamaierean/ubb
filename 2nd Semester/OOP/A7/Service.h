#pragma once
#include "Repository.h"
#include "MovieValidator.h"
#include "WatchList.h"
#include "FileWatchList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <initializer_list>

class Service
{
private:
  Repository *repository;
  bool adminCredentials;
  FileWatchList *watchList;
  std::vector<int> indexesOfMoviesThatTheUserLikes;

public:
  Service();
  ~Service();
  void openTrailerOfMovieInBrowser(int);
  bool compareStrings(const std::string &, const std::string &) const;
  void addMovie(Movie);
  void removeMovieByPosition(int);
  void updateMovie(int, Movie);
  std::vector<Movie> getMovies() const;
  int getMoviesCount() const;
  Movie getMovieByPosition(int) const;
  void setAdminCredentials(bool);
  bool getAdminCredentials();
  std::vector<Movie> getMoviesByGenre(const std::string &);
  std::vector<Movie> getMoviesFromWatchList() const;
  void removeWatchedMovieFromWatchList(int);
  void addMovieToWatchList(Movie);
  void increaseLikesCountOfMovie(Movie &);
  void setTypeOfWatchList(FileWatchList *);
  void setTypeOfRepository(Repository *);
  void displayPlaylist();
  void checkIfMovieIsAlreadyInThePlaylist(const Movie &);
  void clearFile(const std::string &);
};