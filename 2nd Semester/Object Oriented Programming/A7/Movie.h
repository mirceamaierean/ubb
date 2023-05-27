#pragma once
#include <string>
#include <iostream>
#include <regex>
#include <Utils.h>
#include "MovieValidator.h"

namespace indexes
{
  const int TITLE = 0;
  const int GENRE = 1;
  const int YEAR_OF_RELEASE = 2;
  const int TRAILER = 3;
  const int NUMBER_OF_LIKES = 4;
}

class Movie
{
private:
  std::string title, genre, trailer;
  int yearOfRelease, likesCount;

public:
  // Constructors
  Movie(const std::string &title = "",
        const std::string &genre = "",
        const std::string &trailer = "",
        int yearOfRelease = 0,
        int likesCount = 0) : title{title},
                              genre{genre},
                              trailer{trailer},
                              yearOfRelease{yearOfRelease},
                              likesCount{likesCount} {};
  Movie(const Movie &movie);

  // Destructor
  ~Movie() {}

  // Operators
  Movie &operator=(const Movie &);
  bool operator==(const Movie &) const;
  friend std::ostream &operator<<(std::ostream &, const Movie &);
  friend std::istream &operator>>(std::istream &, Movie &);

  // Getters
  std::string getTitle() const;
  std::string getGenre() const;
  std::string getTrailer() const;
  int getYearOfRelease() const;
  int getLikesCount() const;

  // Setters
  void setTitle(const std::string &);
  void setGenre(const std::string &);
  void setTrailer(const std::string &);
  void setYearOfRelease(int);
  void setLikesCount(int);

  void openTrailerInBrowser();
};