#pragma once
#include <sqlite3.h>
#include "Repository.h"

class DBRepository : public Repository
{
private:
  sqlite3 *databaseWithMovies;
  std::string dataBaseName;

public:
  DBRepository(const std::string &dataBaseName);
  virtual ~DBRepository();
  void loadMoviesIntoRepository();
  void addMovie(const Movie &);
  void removeMovie(Movie &);
  void removeMovieByPosition(int);
  void updateMovie(int, const Movie &);
};