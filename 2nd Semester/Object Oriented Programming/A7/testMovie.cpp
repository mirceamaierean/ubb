#include "testMovie.h"
#include "Movie.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestsMovie::testMovie()
{
  std::cout << "Testing Movie class..." << std::endl;
  // Test all constructors
  Movie movieWithDefaultConstructor;
  assert(movieWithDefaultConstructor.getTitle() == "");
  assert(movieWithDefaultConstructor.getGenre() == "");
  assert(movieWithDefaultConstructor.getTrailer() == "");
  assert(movieWithDefaultConstructor.getYearOfRelease() == 0);
  assert(movieWithDefaultConstructor.getLikesCount() == 0);
  movieWithDefaultConstructor = movieWithDefaultConstructor;
  Movie movieWithConstructorBasedOnParameters{"The Shawshank Redemption", "Drama", "https://www.youtube.com/watch?v=6hB3S9bIaco", 1994, 1000000};
  assert(movieWithConstructorBasedOnParameters.getTitle() == "The Shawshank Redemption");
  assert(movieWithConstructorBasedOnParameters.getGenre() == "Drama");
  assert(movieWithConstructorBasedOnParameters.getTrailer() == "https://www.youtube.com/watch?v=6hB3S9bIaco");
  assert(movieWithConstructorBasedOnParameters.getYearOfRelease() == 1994);
  assert(movieWithConstructorBasedOnParameters.getLikesCount() == 1000000);
  try
  {
    MovieValidator::validateMovieIdentifiers(movieWithConstructorBasedOnParameters.getTitle(), movieWithConstructorBasedOnParameters.getGenre(), std::to_string(movieWithConstructorBasedOnParameters.getYearOfRelease()), movieWithConstructorBasedOnParameters.getTrailer(), std::to_string(movieWithConstructorBasedOnParameters.getLikesCount()));
    assert(true);
  }
  catch (const std::exception &caughtException)
  {
    assert(false);
  }
  try
  {
    MovieValidator::validateMovieTrailer("this links is not a link");
    assert(false);
  }
  catch (const std::exception &caughtException)
  {
    assert(true);
  }
  try
  {
    MovieValidator::validateMovieYearOfRelease("-21");
    assert(false);
  }
  catch (const std::exception &caughtException)
  {
    assert(true);
  }

  try
  {
    MovieValidator::validateMovieYearOfRelease("this is a string");
    assert(false);
  }
  catch (const std::exception &caughtException)
  {
    assert(true);
  }

  try
  {
    MovieValidator::validateMovieYearOfRelease("2023");
    assert(true);
  }
  catch (const std::exception &caughtException)
  {
    assert(false);
  }

  Movie movieWithCopyConstructor{movieWithConstructorBasedOnParameters};
  assert(movieWithCopyConstructor.getTitle() == "The Shawshank Redemption");
  assert(movieWithCopyConstructor.getGenre() == "Drama");
  assert(movieWithCopyConstructor.getTrailer() == "https://www.youtube.com/watch?v=6hB3S9bIaco");
  assert(movieWithCopyConstructor.getYearOfRelease() == 1994);
  assert(movieWithCopyConstructor.getLikesCount() == 1000000);
  // Test setters
  movieWithDefaultConstructor.setTitle("Titanic");
  assert(movieWithDefaultConstructor.getTitle() == "Titanic");
  movieWithDefaultConstructor.setGenre("Romance");
  assert(movieWithDefaultConstructor.getGenre() == "Romance");
  movieWithDefaultConstructor.setTrailer("https://www.youtube.com/watch?v=kVrqfYjkTdQ");
  assert(movieWithDefaultConstructor.getTrailer() == "https://www.youtube.com/watch?v=kVrqfYjkTdQ");
  movieWithDefaultConstructor.setYearOfRelease(1997);
  assert(movieWithDefaultConstructor.getYearOfRelease() == 1997);
  movieWithDefaultConstructor.setLikesCount(312);
  assert(movieWithDefaultConstructor.getLikesCount() == 312);
  // Test operator=
  movieWithDefaultConstructor = movieWithConstructorBasedOnParameters;
  assert(movieWithDefaultConstructor.getTitle() == "The Shawshank Redemption");
  assert(movieWithDefaultConstructor.getGenre() == "Drama");
  assert(movieWithDefaultConstructor.getTrailer() == "https://www.youtube.com/watch?v=6hB3S9bIaco");
  assert(movieWithDefaultConstructor.getYearOfRelease() == 1994);
  assert(movieWithDefaultConstructor.getLikesCount() == 1000000);
  // Test validateTrailer
  try
  {
    MovieValidator::validateMovieTrailer("https://www.youtube.com/watch?v=6hB3S9bIaco");
    assert(true);
  }
  catch (const std::exception &caughtException)
  {
    assert(false);
  }
}