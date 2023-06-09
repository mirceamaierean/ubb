#include "testService.h"
#include "FileWatchList.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"
#include "Repository.h"
#include "FileRepository.h"
#include "Movie.h"
#include "Exceptions.h"
#include <cassert>
#include <iostream>
#include <ctime>

void TestsService::testService(Repository *typeOfRepository, FileWatchList *typeOfWatchList)
{
  std::cout << "Testing Service class..." << std::endl;

  Service service = Service();

  std::string firstStringForCompareThatWillSucceed = "abc";
  std::string secondStringForCompareThatWillSucceed = "abc";
  assert(service.compareStrings(firstStringForCompareThatWillSucceed, secondStringForCompareThatWillSucceed) == true);

  std::string firstStringForCompareThatWillSuccedInCaseSensitive = "THIS IS A SUPER NICE STRING";
  std::string secondStringForCompareThatWillSucceedInCaseSensitive = "this is a super nice string";
  assert(service.compareStrings(firstStringForCompareThatWillSuccedInCaseSensitive, secondStringForCompareThatWillSucceedInCaseSensitive) == true);

  std::string firstStringForCompareThatWillFailBecauseOfTheLength = "abc";
  std::string secondStringForCompareThatWillFailBecauseOfTheLength = "abcd";
  assert(service.compareStrings(firstStringForCompareThatWillFailBecauseOfTheLength, secondStringForCompareThatWillFailBecauseOfTheLength) == false);

  std::string firstStringForCompareThatWillFailBecauseOfTheCharacters = "abc";
  std::string secondStringForCompareThatWillFailBecauseOfTheCharacters = "abd";
  assert(service.compareStrings(firstStringForCompareThatWillFailBecauseOfTheCharacters, secondStringForCompareThatWillFailBecauseOfTheCharacters) == false);

  srand(time(NULL));

  service.setTypeOfRepository(typeOfRepository);
  service.setTypeOfWatchList(typeOfWatchList);

  try
  {
    service.getMovieByPosition(-1);
    assert(false);
  }
  catch (const std::exception &caughtException)
  {
    assert(true);
  }

  int moviesCount = service.getMoviesCount();
  assert(moviesCount >= 0);

  service.setAdminCredentials(true);
  assert(service.getAdminCredentials() == true);

  service.setAdminCredentials(false);
  assert(service.getAdminCredentials() == false);

  Movie movieToBeAdded = Movie("Harry Potter", "Fantasy", "https://www.youtube.com/watch?v=VyHV0BRtdxo", 2001, rand() % 100 + 1);
  try
  {
    service.removeMovieByPosition(312);
    assert(false);
  }
  catch (InvalidPositionException &caughtException)
  {
    assert(true);
  }

  service.addMovie(movieToBeAdded);
  movieToBeAdded = Movie("Harry Potter 2", "Fantasy", "https://www.youtube.com/watch?v=VyHV0BRtdxo", 2001, rand() % 100 + 1);
  service.addMovie(movieToBeAdded);
  movieToBeAdded = Movie("Harry Potter 3", "Fantasy", "https://www.youtube.com/watch?v=VyHV0BRtdxo", 2001, rand() % 100 + 1);
  service.addMovie(movieToBeAdded);

  int likesCountForTheLastMovieThatWasAdded = service.getMovieByPosition(service.getMoviesCount() - 1).getLikesCount();
  moviesCount += 3;

  assert(service.getMoviesCount() == moviesCount);

  service.increaseLikesCountOfMovie(movieToBeAdded);

  assert(service.getMovieByPosition(moviesCount - 1).getLikesCount() == likesCountForTheLastMovieThatWasAdded + 1);

  service.removeMovieByPosition(2);
  assert(service.getMoviesCount() == moviesCount - 1);

  --moviesCount;

  Movie updatedMovie = Movie("Harry Potter and the Chamber of Secrets", "Fantasy", "https://www.youtube.com/watch?v=VyHV0BRtdxo", 2002, rand() % 100 + 1);
  std::vector<Movie> currentMoviesInTheList = service.getMovies();
  int positionOfMovieToUpdate = 0;

  try
  {
    service.updateMovie(193223, updatedMovie);
    assert(false);
  }
  catch (InvalidPositionException &caughtException)
  {
    assert(true);
  }

  try
  {
    service.updateMovie(positionOfMovieToUpdate, updatedMovie);
    assert(true);
  }
  catch (const std::exception &e)
  {
    assert(false);
  }

  assert(service.getMoviesCount() == moviesCount);
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getTitle() == "Harry Potter and the Chamber of Secrets");
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getGenre() == "Fantasy");
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getTrailer() == "https://www.youtube.com/watch?v=VyHV0BRtdxo");
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getYearOfRelease() == 2002);
  assert(service.getMovieByPosition(positionOfMovieToUpdate).getLikesCount() <= 100);

  try
  {
    service.addMovie(updatedMovie);
    assert(false);
  }
  catch (DuplicateMovieException &caughtException)
  {
    assert(true);
  }

  std::vector<Movie> movies = service.getMovies();

  service.openTrailerOfMovieInBrowser(0);

  Movie entryMovie1 = Movie("The Godfather", "Crime", "https://www.youtube.com/watch?v=sY1S34973zA", 1972, rand() % 100 + 1);
  Movie entryMovie2 = Movie("Schindlers List", "Biography", "https://www.youtube.com/watch?v=gG22XNhtnoY", 1993, rand() % 100 + 1);
  Movie entryMovie3 = Movie("2012", "Action", "https://www.youtube.com/watch?v=sFXGrTng0gQ", 2009, rand() % 100 + 1);
  Movie entryMovie4 = Movie("The Shawshank Redemption", "Drama", "https://www.youtube.com/watch?v=6hB3S9bIaco", 1994, rand() % 100 + 1);
  Movie entryMovie5 = Movie("The Dark Knight", "Action", "https://www.youtube.com/watch?v=EXeTwQWrcwY", 2008, rand() % 100 + 1);
  Movie entryMovie6 = Movie("The Lord of the Rings: The Return of the King", "Adventure", "https://www.youtube.com/watch?v=r5X-hFf6Bwo", 2003, rand() % 100 + 1);
  Movie entryMovie7 = Movie("The Godfather: Part II", "Crime", "https://www.youtube.com/watch?v=9O1Iy9od7-A", 1974, rand() % 100 + 1);
  Movie entryMovie8 = Movie("The Lord of the Rings: The Fellowship of the Ring", "Adventure", "https://www.youtube.com/watch?v=V75dMMIW2B4", 2001, rand() % 100 + 1);
  Movie entryMovie9 = Movie("Pulp Fiction", "Crime", "https://www.youtube.com/watch?v=s7EdQ4FqbhY", 1994, rand() % 100 + 1);
  Movie entryMovie10 = Movie("The Good the Bad and the Ugly", "Western", "https://www.youtube.com/watch?v=WCN5JJY_wiA", 1966, rand() % 100 + 1);
  Movie entryMovie11 = Movie("The Lord of the Rings: The Two Towers", "Adventure", "https://www.youtube.com/watch?v=LbfMDwc4azU", 2002, rand() % 100 + 1);
  Movie entryMovie12 = Movie("Inception", "Action", "https://www.youtube.com/watch?v=YoHD9XEInc0", 2010, rand() % 100 + 1);
  Movie entryMovie13 = Movie("Fight Club", "Drama", "https://www.youtube.com/watch?v=SUXWAEX2jlg", 1999, rand() % 100 + 1);
  Movie entryMovie14 = Movie("Forrest Gump", "Drama", "https://www.youtube.com/watch?v=bLvqoHBptjg", 1994, rand() % 100 + 1);
  Movie entryMovie15 = Movie("Star Wars: Episode V - The Empire Strikes Back", "Action", "https://www.youtube.com/watch?v=JNwNXF9Y6kY", 1980, rand() % 100 + 1);
  service.addMovie(entryMovie1);
  service.addMovie(entryMovie2);
  service.addMovie(entryMovie3);
  service.addMovie(entryMovie4);
  service.addMovie(entryMovie5);
  service.addMovie(entryMovie6);
  service.addMovie(entryMovie7);
  service.addMovie(entryMovie8);
  service.addMovie(entryMovie9);
  service.addMovie(entryMovie10);
  service.addMovie(entryMovie11);
  service.addMovie(entryMovie12);
  service.addMovie(entryMovie13);
  service.addMovie(entryMovie14);
  service.addMovie(entryMovie15);

  service.addMovieToWatchList(entryMovie1);
  service.addMovieToWatchList(entryMovie3);
  service.addMovieToWatchList(entryMovie6);
  service.addMovieToWatchList(entryMovie10);
  service.addMovieToWatchList(entryMovie15);

  std::vector<Movie> moviesThatHaveTheGenreAction = service.getMoviesByGenre("Action");
  assert(moviesThatHaveTheGenreAction.size() == 4);

  std::vector<Movie> allMovies = service.getMoviesByGenre("");
  assert(allMovies.size() == 17);

  typeOfWatchList->writeToFile();
  typeOfWatchList->openInApp();
}

void TestsService::testService()
{
  Service serviceForClearingFiles = Service();
  serviceForClearingFiles.clearFile("../../../../testFile+CSV.txt");
  serviceForClearingFiles.clearFile("../../../../WatchListFile+CSV.csv");
  testService(new FileRepository{"testFile+CSV.txt"}, new CSVWatchList{"WatchListFile+CSV.csv"});
  serviceForClearingFiles.clearFile("../../../../testFile+HTML.txt");
  serviceForClearingFiles.clearFile("../../../../WatchListFile+HTML.html");
  testService(new FileRepository{"testFile+HTML.txt"}, new HTMLWatchList{"WatchListFile+HTML.html"});
}