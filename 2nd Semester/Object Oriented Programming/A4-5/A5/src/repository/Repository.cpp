#include "../../include/repository/Repository.h"

Repository::Repository()
{
  this->movies = DynamicVector<Movie>();
}

Repository::~Repository()
{
  // nothing to do here, the destructor of the dynamic vector will be called automatically
}

void Repository::addMovie(const Movie &movieToBeAdded)
{
  this->movies.addElementInDynamicVector(movieToBeAdded);
}

void Repository::removeMovie(Movie &movieToBeRemoved)
{
  int positionOfMovieToBeRemoved = this->movies.returnPosition(movieToBeRemoved);
  this->movies.removeElementFromDynamicVector(positionOfMovieToBeRemoved);
}

void Repository::removeMovieByPosition(int positionOfMovieToBeRemoved)
{
  this->movies.removeElementFromDynamicVector(positionOfMovieToBeRemoved);
}

void Repository::updateMovie(int positionOfMovieToBeUpdated, const Movie &movieWithUpdatedData)
{
  this->movies.updateElementInDynamicVector(positionOfMovieToBeUpdated, movieWithUpdatedData);
}

DynamicVector<Movie> Repository::getMovies() const
{
  return this->movies;
}

int Repository::getMoviesCount() const
{
  return this->movies.getSizeOfDynamicVector();
}

Movie Repository::getMovieByPosition(int position) const
{
  return this->movies.getElement(position);
}

bool Repository::validatePosition(int position) const
{
  return position >= 0 && position < this->movies.getSizeOfDynamicVector();
}

int Repository::returnPosition(Movie &movie) const
{
  int position = this->movies.returnPosition(movie);
  return position;
}

void Repository::modifyLikesCountOfMovieByPosition(int positionOfMovieToBeUpdated, int incrementeLikesCount)
{
  Movie movieToBeUpdated = this->movies.getElement(positionOfMovieToBeUpdated);
  movieToBeUpdated.setLikesCount(movieToBeUpdated.getLikesCount() + incrementeLikesCount);
  this->movies.updateElementInDynamicVector(positionOfMovieToBeUpdated, movieToBeUpdated);
}
