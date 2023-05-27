#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "Movie.h"

class MovieExceptions : public std::exception
{
private:
  std::vector<std::invalid_argument> errors;

public:
  MovieExceptions(std::vector<std::invalid_argument> errors);
  MovieExceptions(std::string error);
  std::vector<std::invalid_argument> returnErrors();
};

class MovieValidator
{
public:
  static void validateMovieTitle(const std::string &);
  static void validateMovieGenre(const std::string &);
  static void validateMovieYearOfRelease(const std::string &);
  static void validateMovieNumberOfLikes(const std::string &);
  static void validateMovieTrailer(const std::string &);
  static void validateMovieIdentifiers(const std::string &, const std::string &, const std::string &, const std::string &, const std::string &);
};