#include "../../include/service/Service.h"
#include <iostream>
#include <string>
#include <ctime>

Service::Service()
{
  this->repository = Repository();
  this->adminCredentials = false;
}

Service::~Service()
{
}

void Service::setAdminCredentials(bool adminCredentials)
{
  this->adminCredentials = adminCredentials;
}

bool Service::getAdminCredentials()
{
  return this->adminCredentials;
}

void Service::generateRandomMovies()
{
  srand(time(NULL));
  Movie entryMovie1 = Movie("The Godfather", "Crime", "https://www.youtube.com/watch?v=sY1S34973zA", 1972, rand() % 100 + 1);
  Movie entryMovie2 = Movie("Schindler's List", "Biography", "https://www.youtube.com/watch?v=gG22XNhtnoY", 1993, rand() % 100 + 1);
  Movie entryMovie3 = Movie("2012", "Action", "https://www.youtube.com/watch?v=2eLXZQXzsX4", 2009, rand() % 100 + 1);
  Movie entryMovie4 = Movie("The Shawshank Redemption", "Drama", "https://www.youtube.com/watch?v=6hB3S9bIaco", 1994, rand() % 100 + 1);
  Movie entryMovie5 = Movie("The Dark Knight", "Action", "https://www.youtube.com/watch?v=EXeTwQWrcwY", 2008, rand() % 100 + 1);
  Movie entryMovie6 = Movie("The Lord of the Rings: The Return of the King", "Adventure", "https://www.youtube.com/watch?v=r5X-hFf6Bwo", 2003, rand() % 100 + 1);
  Movie entryMovie7 = Movie("The Godfather: Part II", "Crime", "https://www.youtube.com/watch?v=qJr4k7WQiIg", 1974, rand() % 100 + 1);
  Movie entryMovie8 = Movie("The Lord of the Rings: The Fellowship of the Ring", "Adventure", "https://www.youtube.com/watch?v=V75dMMIW2B4", 2001, rand() % 100 + 1);
  Movie entryMovie9 = Movie("Pulp Fiction", "Crime", "https://www.youtube.com/watch?v=s7EdQ4FqbhY", 1994, rand() % 100 + 1);
  Movie entryMovie10 = Movie("The Good, the Bad and the Ugly", "Western", "https://www.youtube.com/watch?v=WCN5JJY_wiA", 1966, rand() % 100 + 1);
  Movie entryMovie11 = Movie("The Lord of the Rings: The Two Towers", "Adventure", "https://www.youtube.com/watch?v=LbfMDwc4azU", 2002, rand() % 100 + 1);
  Movie entryMovie12 = Movie("Inception", "Action", "https://www.youtube.com/watch?v=YoHD9XEInc0", 2010, rand() % 100 + 1);
  Movie entryMovie13 = Movie("Fight Club", "Drama", "https://www.youtube.com/watch?v=SUXWAEX2jlg", 1999, rand() % 100 + 1);
  Movie entryMovie14 = Movie("Forrest Gump", "Drama", "https://www.youtube.com/watch?v=bLvqoHBptjg", 1994, rand() % 100 + 1);
  Movie entryMovie15 = Movie("Star Wars: Episode V - The Empire Strikes Back", "Action", "https://www.youtube.com/watch?v=JNwNXF9Y6kY", 1980, rand() % 100 + 1);
  this->addMovie(entryMovie1);
  this->addMovie(entryMovie2);
  this->addMovie(entryMovie3);
  this->addMovie(entryMovie4);
  this->addMovie(entryMovie5);
  this->addMovie(entryMovie6);
  this->addMovie(entryMovie7);
  this->addMovie(entryMovie8);
  this->addMovie(entryMovie9);
  this->addMovie(entryMovie10);
  this->addMovie(entryMovie11);
  this->addMovie(entryMovie12);
  this->addMovie(entryMovie13);
  this->addMovie(entryMovie14);
  this->addMovie(entryMovie15);
}

bool Service::addMovie(Movie movie)
{
  // If the movie is already in the repository, we don't add it
  if (this->repository.validatePosition(this->repository.returnPosition(movie)))
    return false;

  this->repository.addMovie(movie);
  return true;
}

bool Service::removeMovieByPosition(int positionOfMovie)
{
  if (!this->repository.validatePosition(positionOfMovie))
    return false;
  this->repository.removeMovieByPosition(positionOfMovie);
  return true;
}

bool Service::updateMovie(int position, Movie movie)
{
  if (!this->repository.validatePosition(position))
    return false;
  this->repository.updateMovie(position, movie);
  return true;
}

DynamicVector<Movie> Service::getMovies() const
{
  return this->repository.getMovies();
}

int Service::getMoviesCount() const
{
  return this->repository.getMoviesCount();
}

Movie Service::getMovieByPosition(int position) const
{
  if (!this->repository.validatePosition(position))
    throw std::invalid_argument("Position is not valid");
  return this->repository.getMovieByPosition(position);
}

DynamicVector<int> Service::getPositionsOfMoviesByGenre(const std::string &genreOfMovie) const
{
  DynamicVector<int> positionsOfMoviesByGenre;
  for (int index = 0; index < this->repository.getMoviesCount(); ++index)
  {
    if (this->repository.getMovieByPosition(index).getGenre() == genreOfMovie)
      positionsOfMoviesByGenre.addElementInDynamicVector(index);
  }
  return positionsOfMoviesByGenre;
}
