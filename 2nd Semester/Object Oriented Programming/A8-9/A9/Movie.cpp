#include "Movie.h"
#include <sstream>

using namespace indexes;

Movie::Movie(const Movie &movie)
{
  this->title = movie.title;
  this->genre = movie.genre;
  this->trailer = movie.trailer;
  this->yearOfRelease = movie.yearOfRelease;
  this->likesCount = movie.likesCount;
}

// Assignment operator
Movie &Movie::operator=(const Movie &movie)
{
  if (this == &movie)
    return *this;

  this->title = movie.title;
  this->genre = movie.genre;
  this->trailer = movie.trailer;
  this->yearOfRelease = movie.yearOfRelease;
  this->likesCount = movie.likesCount;

  return *this;
}

bool Movie::operator==(const Movie &movie) const
{
  return this->title == movie.title && this->genre == movie.genre && this->yearOfRelease == movie.yearOfRelease;
}

// Getters
std::string Movie::getTitle() const
{
  return this->title;
}

std::string Movie::getGenre() const
{
  return this->genre;
}

std::string Movie::getTrailer() const
{
  return this->trailer;
}

// Setters
int Movie::getYearOfRelease() const
{
  return this->yearOfRelease;
}

int Movie::getLikesCount() const
{
  return this->likesCount;
}

void Movie::setTitle(const std::string &title)
{

  this->title = title;
}

void Movie::setGenre(const std::string &genre)
{
  this->genre = genre;
}

void Movie::setTrailer(const std::string &trailer)
{
  this->trailer = trailer;
}

void Movie::setYearOfRelease(int yearOfRelease)
{
  this->yearOfRelease = yearOfRelease;
}

void Movie::setLikesCount(int likesCount)
{
  this->likesCount = likesCount;
}

void Movie::openTrailerInBrowser()
{
  std::string commandToOpenTheLinkInBrowser = "open " + this->trailer;
  system(commandToOpenTheLinkInBrowser.c_str());
}

std::ostream &operator<<(std::ostream &output, const Movie &movie)
{
  output << movie.getTitle() << " | " << movie.getGenre() << " | " << movie.getYearOfRelease() << " | " << movie.getTrailer() << " | " << movie.getLikesCount();
  return output;
}

std::istream &operator>>(std::istream &input, Movie &movie)
{
  Utils utilFunctionsToWorkWithStrings;

  std::string lineWithContentOfMovie;
  std::getline(input, lineWithContentOfMovie);

  std::vector<std::string> vectorWithTokens = utilFunctionsToWorkWithStrings.tokenizeString(lineWithContentOfMovie, '|');

  int numberOfArguments = vectorWithTokens.size();
  if (numberOfArguments != 5)
    throw MovieExceptions("The provided number of arguments is not ok! Expected 5 arguments, received " +
                          std::to_string(numberOfArguments) +
                          " arguments.");

  const std::string &title = vectorWithTokens[TITLE],
                    &genre = vectorWithTokens[GENRE],
                    &yearOfRelease = vectorWithTokens[YEAR_OF_RELEASE],
                    &trailer = vectorWithTokens[TRAILER],
                    &likesCount = vectorWithTokens[NUMBER_OF_LIKES];

    MovieValidator::validateMovieIdentifiers(title, genre, yearOfRelease, trailer, likesCount);

  movie.setTitle(title);
  movie.setGenre(genre);
  movie.setYearOfRelease(std::stoi(yearOfRelease));
  movie.setTrailer(trailer);
  movie.setLikesCount(std::stoi(likesCount));

  return input;
}
