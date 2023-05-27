#pragma once
#include "Repository.h"

class FileRepository : public Repository
{
private:
  std::string fileName;

public:
  FileRepository(const std::string &fileName) : fileName{fileName} {};
  virtual ~FileRepository();
  void loadMoviesIntoRepository();
  void saveMovies();
  void addMovie(const Movie &);
  void removeMovie(Movie &);
  void removeMovieByPosition(int);
  void updateMovie(int, const Movie &);
};