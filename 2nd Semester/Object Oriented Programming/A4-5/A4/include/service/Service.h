#pragma once
#include "../repository/Repository.h"
#include <iostream>
#include <string>
#include <initializer_list>

class Service
{
private:
  Repository repository;
  bool adminCredentials;
  DynamicVector<int> indexesOfUserMovies;

public:
  Service();
  ~Service();
  void generateRandomMovies();
  bool addMovie(Movie movie);
  bool removeMovieByPosition(int positionOfMovie);
  bool updateMovie(int position, Movie movie);
  DynamicVector<Movie> getMovies() const;
  int getMoviesCount() const;
  Movie getMovieByPosition(int position) const;
  void setAdminCredentials(bool adminCredentials);
  bool getAdminCredentials();
  DynamicVector<int> getPositionsOfMoviesByGenre(const std::string &genreOfMovie) const;
  void addIndexOfMovieToUserList(int indexOfMovieLikedByTheUser);
  void removeIndexOfMovieFromUserList(int indexOfMovieWatchedByTheUser);
};