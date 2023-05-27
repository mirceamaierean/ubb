#pragma once
#include "../domain/DynamicVector.h"
#include "../domain/Movie.h"
#include <iostream>
#include <string>

class Repository
{
private:
  DynamicVector<Movie> movies;

public:
  Repository();
  ~Repository();
  void addMovie(const Movie &movie);
  void removeMovie(Movie &movie);
  void removeMovieByPosition(int positionOfMovieToBeRemoved);
  void updateMovie(int positionOfMovieToBeUpdated, const Movie &movie);
  bool validatePosition(int position) const;
  DynamicVector<Movie> getMovies() const;
  int getMoviesCount() const;
  Movie getMovieByPosition(int position) const;
  int returnPosition(Movie &movie) const;
};