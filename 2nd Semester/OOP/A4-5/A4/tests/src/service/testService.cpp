#include "../../include/service/testService.h"
#include "../../../include/domain/Movie.h"
#include "../../../include/domain/DynamicVector.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestsService::testService()
{
  std::cout << "Testing Service class..." << std::endl;
  Service service = Service();
  try
  {
    service.getMovieByPosition(-1);
    assert(false);
  }
  catch (const std::exception &caughtException)
  {
    assert(true);
  }

  assert(service.getMoviesCount() == 0);

  service.setAdminCredentials(true);
  assert(service.getAdminCredentials() == true);

  service.setAdminCredentials(false);
  assert(service.getAdminCredentials() == false);

  service.generateRandomMovies();
  assert(service.getMoviesCount() == 15);

  Movie movieToBeAdded = Movie("Harry Potter", "Fantasy", "https://www.youtube.com/watch?v=VyHV0BRtdxo", 2001, 1000000);
  assert(service.removeMovieByPosition(312) == false);

  service.addMovie(movieToBeAdded);
  assert(service.getMoviesCount() == 16);

  service.removeMovieByPosition(0);
  assert(service.getMoviesCount() == 15);

  Movie updatedMovie = Movie("Harry Potter and the Chamber of Secrets", "Fantasy", "https://www.youtube.com/watch?v=VyHV0BRtdxo", 2002, 1000000);
  int positionOfMovieToUpdate = service.getMovies().returnPosition(movieToBeAdded);
  assert(positionOfMovieToUpdate == 14);
  assert(service.updateMovie(19, updatedMovie) == false);
  assert(service.updateMovie(14, updatedMovie) == true);

  assert(service.getMoviesCount() == 15);
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getTitle() == "Harry Potter and the Chamber of Secrets");
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getGenre() == "Fantasy");
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getTrailer() == "https://www.youtube.com/watch?v=VyHV0BRtdxo");
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getYearOfRelease() == 2002);
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getLikesCount() == 1000000);

  assert(service.addMovie(updatedMovie) == false);

  DynamicVector<Movie> movies = service.getMovies();
  assert(movies.getSizeOfDynamicVector() == 15);
}
