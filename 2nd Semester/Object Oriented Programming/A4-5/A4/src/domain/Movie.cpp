#include "../../include/domain/Movie.h"
#include <sstream>
// Constructor
Movie::Movie(const std::string &title, const std::string &genre, const std::string &trailer, int yearOfRelease, int likesCount) : title{title}, genre{genre}, trailer{trailer}, yearOfRelease{yearOfRelease}, likesCount{likesCount} {};

// Destructor
Movie::~Movie() {}

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

// Validate trailer
void Movie::validateTrailer(const std::string &trailer)
{
  const std::regex pattern("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
  if (!std::regex_match(trailer, pattern))
    throw std::invalid_argument("Invalid trailer link");
}

void Movie::validateYearOfRelease(int yearOfRelease)
{
  std::time_t result = std::time(nullptr);
  std::istringstream iss(ctime(&result));

  iss.ignore(20);
  int currentYear;
  iss >> currentYear;
  if (yearOfRelease < 0 || yearOfRelease > currentYear)
    throw std::invalid_argument("Year of release must be a positive integer");
}

void Movie::validateLikesCount(int likesCount)
{
  if (likesCount < 0)
    throw std::invalid_argument("Likes count must be a positive integer");
}

void Movie::validateMovie()
{
  validateTrailer(this->trailer);
  validateYearOfRelease(this->yearOfRelease);
  validateLikesCount(this->likesCount);
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
  // Defensive programming
  this->validateYearOfRelease(yearOfRelease);
  this->yearOfRelease = yearOfRelease;
}

void Movie::setLikesCount(int likesCount)
{
  // Defensive programming
  this->validateLikesCount(likesCount);
  this->likesCount = likesCount;
}
