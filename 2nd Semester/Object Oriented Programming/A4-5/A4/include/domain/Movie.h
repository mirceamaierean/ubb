#pragma once
#include <string>
#include <iostream>
#include <regex>

class Movie
{
private:
  std::string title, genre, trailer;
  int yearOfRelease, likesCount;

public:
  Movie(const std::string &title = "", const std::string &genre = "", const std::string &trailer = "", int yearOfRelease = 0, int likesCount = 0);
  Movie(const Movie &movie);
  ~Movie();
  Movie &operator=(const Movie &movie);
  bool operator==(const Movie &movie) const;
  std::string getTitle() const;
  std::string getGenre() const;
  std::string getTrailer() const;
  int getYearOfRelease() const;
  int getLikesCount() const;
  void setTitle(const std::string &title);
  void setGenre(const std::string &genre);
  void setTrailer(const std::string &trailer);
  void setYearOfRelease(int yearOfRelease);
  void setLikesCount(int likeCount);
  void validateTrailer(const std::string &trailer);
  void validateYearOfRelease(int yearOfRelease);
  void validateLikesCount(int likesCount);
  void validateMovie();
};