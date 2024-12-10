#pragma once
#include "../domain/Movie.h"
#include <iostream>
#include <string>
#include <vector>

class Repository
{
private:
  std::vector<Movie> movies;

public:
  Repository();
  ~Repository();
  void addMovie(const Movie &movie);
  void removeMovie(Movie &movie);
  void removeMovieByPosition(int positionOfMovieToBeRemoved);
  void updateMovie(int positionOfMovieToBeUpdated, const Movie &movie);
  bool validatePosition(int position) const;
  std::vector<Movie> getMovies() const;
  size_t getMoviesCount() const;
  Movie getMovieByPosition(int position) const;
  int returnPosition(Movie &movie);
  void modifyLikesCountOfMovieByPosition(int positionOfMovieToBeUpdated, int newLikesCount);
};