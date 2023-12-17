#pragma once
#include "../repository/Repository.h"
#include <iostream>
#include <string>
#include <initializer_list>

class Service
{
private:
  Repository repository;
  bool adminCredentials;
  DynamicVector<int> indexesOfMoviesThatTheUserLikes;

public:
  Service();
  ~Service();
  void generateRandomMovies();
  void openTrailerOfMovieInBrowser(int positionOfMovieInTheDynamicArray);
  bool compareStrings(const std::string &firstComparedString, const std::string &secondComparedString) const;
  bool addMovie(Movie movie);
  bool removeMovieByPosition(int positionOfMovie);
  bool updateMovie(int position, Movie movie);
  bool checkIfUserLikesMovie(int positionOfMovieInTheDynamicArray);
  DynamicVector<Movie> getMovies() const;
  int getMoviesCount() const;
  Movie getMovieByPosition(int position) const;
  void setAdminCredentials(bool adminCredentials);
  bool getAdminCredentials();
  DynamicVector<int> getPositionsOfMoviesByGenre(const std::string &genreOfMovie);
  DynamicVector<int> getIndexesOfMoviesThatTheUserLikes() const;
  void removeIndexOfMovieFromUserList(int indexOfMovieWatchedByTheUser);
  void addIndexOfMovieToUserListByPosition(int positionOfMovieLikedByTheUser);
  void increaseLikesCountOfMovieByPosition(int positionOfMovieLikedByTheUser);
};