#include "../../include/service/testService.h"
#include "../../../include/domain/Movie.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>
#include <ctime>

void TestsService::testService()
{
  std::cout << "Testing Service class..." << std::endl;

  Service service = Service();
  std::string firstStringForCompareThatWillSucceed = "abc";
  std::string secondStringForCompareThatWillSucceed = "abc";
  assert(service.compareStrings(firstStringForCompareThatWillSucceed, secondStringForCompareThatWillSucceed) == true);

  std::string firstStringForCompareThatWillSuccedIncaseSensitive = "THIS IS A SUPER NICE STRING";
  std::string secondStringForCompareThatWillSucceedIncaseSensitive = "this is a super nice string";
  assert(service.compareStrings(firstStringForCompareThatWillSuccedIncaseSensitive, secondStringForCompareThatWillSucceedIncaseSensitive) == true);

  std::string firstStringForCompareThatWillFailBecauseOfTheLength = "abc";
  std::string secondStringForCompareThatWillFailBecauseOfTheLength = "abcd";
  assert(service.compareStrings(firstStringForCompareThatWillFailBecauseOfTheLength, secondStringForCompareThatWillFailBecauseOfTheLength) == false);

  std::string firstStringForCompareThatWillFailBecauseOfTheCharacters = "abc";
  std::string secondStringForCompareThatWillFailBecauseOfTheCharacters = "abd";
  assert(service.compareStrings(firstStringForCompareThatWillFailBecauseOfTheCharacters, secondStringForCompareThatWillFailBecauseOfTheCharacters) == false);

  srand(time(NULL));

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

  Movie movieToBeAdded = Movie("Harry Potter", "Fantasy", "https://www.youtube.com/watch?v=VyHV0BRtdxo", 2001, rand() % 100 + 1);
  assert(service.removeMovieByPosition(312) == false);

  service.addMovie(movieToBeAdded);
  int likesCountForTheLastMovieThatWasAdded = service.getMovieByPosition(15).getLikesCount();
  assert(service.getMoviesCount() == 16);

  service.increaseLikesCountOfMovieByPosition(15);

  assert(service.getMovieByPosition(15).getLikesCount() == likesCountForTheLastMovieThatWasAdded + 1);

  service.removeMovieByPosition(0);
  assert(service.getMoviesCount() == 15);

  Movie updatedMovie = Movie("Harry Potter and the Chamber of Secrets", "Fantasy", "https://www.youtube.com/watch?v=VyHV0BRtdxo", 2002, rand() % 100 + 1);
  std::vector<Movie> currentMoviesInTheList = service.getMovies();
  int positionOfMovieToUpdate = std::distance(currentMoviesInTheList.begin(), std::find(currentMoviesInTheList.begin(), currentMoviesInTheList.end(), movieToBeAdded));
  assert(positionOfMovieToUpdate == 14);
  assert(service.updateMovie(19, updatedMovie) == false);
  assert(service.updateMovie(14, updatedMovie) == true);

  assert(service.getMoviesCount() == 15);
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getTitle() == "Harry Potter and the Chamber of Secrets");
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getGenre() == "Fantasy");
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getTrailer() == "https://www.youtube.com/watch?v=VyHV0BRtdxo");
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getYearOfRelease() == 2002);
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getLikesCount() <= 100);

  assert(service.addMovie(updatedMovie) == false);

  std::vector<Movie> movies = service.getMovies();
  assert(movies.size() == 15);

  service.openTrailerOfMovieInBrowser(12);

  std::vector<int> positionsOfMoviesThatHaveTheGenreAction = service.getPositionsOfMoviesByGenre("Action");
  assert(positionsOfMoviesThatHaveTheGenreAction.size() == 4);
  for (auto moviePosition : positionsOfMoviesThatHaveTheGenreAction)
    service.addIndexOfMovieToUserListByPosition(moviePosition);
  assert(service.getIndexesOfMoviesThatTheUserLikes().size() == 4);
  while (service.getIndexesOfMoviesThatTheUserLikes().size() > 0)
    service.removeIndexOfMovieFromUserList(0);
  assert(service.getIndexesOfMoviesThatTheUserLikes().size() == 0);
}
