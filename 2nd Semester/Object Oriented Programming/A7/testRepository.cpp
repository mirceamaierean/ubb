#include "testRepository.h"
#include "Movie.h"
#include "Repository.h"
#include "Exceptions.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestsRepository::testRepository()
{
  std::cout << "Testing Repository class..." << std::endl;
  // Test creation of a repository
  Repository genericRepository;

  // genericRepository.clearDataFromRepository();
  assert(genericRepository.getMoviesCount() == 0);
  // // Test adding a movie to the repository
  Movie movieToAdd("The Shawshank Redemption", "Drama", "https://www.youtube.com/watch?v=6hB3S9bIaco", 1994, rand() % 100 + 1);
  genericRepository.addMovie(movieToAdd);
  assert(genericRepository.getMoviesCount() == 1);
  int previousLikesCountForTheLastAddedMovie = genericRepository.getMovieByPosition(0).getLikesCount();
  genericRepository.modifyLikesCountOfMovieByPosition(0, 123);
  assert(genericRepository.getMovieByPosition(0).getLikesCount() == previousLikesCountForTheLastAddedMovie + 123);
  // Test removing a movie from the repository
  Movie movieToRemove("The Shawshank Redemption", "Drama", "https://www.youtube.com/watch?v=6hB3S9bIaco", 1994, rand() % 100 + 1);
  genericRepository.removeMovie(movieToRemove);
  assert(genericRepository.getMoviesCount() == 0);
  // Test updating a movie from the repository
  Movie movieToUpdate("The Shawshank Redemption", "Drama", "https://www.youtube.com/watch?v=6hB3S9bIaco", 1994, rand() % 100 + 1);
  genericRepository.addMovie(movieToUpdate);

  Movie updatedMovie("IT", "Horror", "https://www.youtube.com/watch?v=FnCdOQsX5kc", 2017, rand() % 100 + 1);
  int positionOfMovieToUpdate = genericRepository.returnPosition(movieToUpdate);
  assert(positionOfMovieToUpdate == 0);

  genericRepository.updateMovie(0, updatedMovie);

  assert(genericRepository.getMoviesCount() == 1);

  try
  {
    genericRepository.getMovieByPosition(-1);
    assert(false);
  }
  catch (const std::exception &caughtException)
  {
    assert(true);
  }

  try
  {
    genericRepository.getMovieByPosition(238871);
    assert(false);
  }
  catch (const std::exception &caughtException)
  {
    assert(true);
  }

  assert(genericRepository.getMovieByPosition(0).getTitle() == "IT");
  assert(genericRepository.getMovieByPosition(0).getGenre() == "Horror");
  assert(genericRepository.getMovieByPosition(0).getTrailer() == "https://www.youtube.com/watch?v=FnCdOQsX5kc");
  assert(genericRepository.getMovieByPosition(0).getYearOfRelease() == 2017);
  assert(genericRepository.getMovieByPosition(0).getLikesCount() <= 100);

  // Test validation of position
  assert(genericRepository.validatePosition(0) == true);
  assert(genericRepository.validatePosition(1) == false);
  assert(genericRepository.validatePosition(-1) == false);

  // Test getting the movies from the repository
  assert(genericRepository.getMoviesCount() == 1);
  assert(genericRepository.getMovieByPosition(0).getTitle() == "IT");
  assert(genericRepository.getMovieByPosition(0).getGenre() == "Horror");
  assert(genericRepository.getMovieByPosition(0).getTrailer() == "https://www.youtube.com/watch?v=FnCdOQsX5kc");
  assert(genericRepository.getMovieByPosition(0).getYearOfRelease() == 2017);
  assert(genericRepository.getMovieByPosition(0).getLikesCount() <= 100);

  // Test getting the movies count from the repository
  assert(genericRepository.getMoviesCount() == 1);

  // Test getting a movie by position from the repository
  assert(genericRepository.getMovieByPosition(0).getTitle() == "IT");
  assert(genericRepository.getMovieByPosition(0).getGenre() == "Horror");
  assert(genericRepository.getMovieByPosition(0).getTrailer() == "https://www.youtube.com/watch?v=FnCdOQsX5kc");
  assert(genericRepository.getMovieByPosition(0).getYearOfRelease() == 2017);
  assert(genericRepository.getMovieByPosition(0).getLikesCount() <= 100);
}