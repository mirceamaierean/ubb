#pragma once
#include "../repository/Repository.h"
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

class Service
{
private:
  Repository repository;
  bool adminCredentials;
  std::vector<int> indexesOfMoviesThatTheUserLikes;

public:
  Service();
  ~Service();
  void generateRandomMovies();
  void openTrailerOfMovieInBrowser(int positionOfMovieInTheDynamicArray);
  bool compareStrings(const std::string &firstComparedString, const std::string &secondComparedString) const;
  bool addMovie(Movie movie);
  bool removeMovieByPosition(int positionOfMovie);
  bool updateMovie(int position, Movie movie);
  std::vector<Movie> getMovies() const;
  int getMoviesCount() const;
  Movie getMovieByPosition(int position) const;
  void setAdminCredentials(bool adminCredentials);
  bool getAdminCredentials();
  std::vector<int> getPositionsOfMoviesByGenre(const std::string &genreOfMovie);
  std::vector<int> getIndexesOfMoviesThatTheUserLikes() const;
  void removeIndexOfMovieFromUserList(int indexOfMovieWatchedByTheUser);
  void addIndexOfMovieToUserListByPosition(int positionOfMovieLikedByTheUser);
  void increaseLikesCountOfMovieByPosition(int positionOfMovieLikedByTheUser);
};