#include "FileRepository.h"
#include "Exceptions.h"
#include <fstream>
#include <sqlite3.h>
#include "DBRepository.h"

DBRepository::DBRepository(const std::string &dataBaseName)
{
  this->dataBaseName = dataBaseName;
  int errorCode = sqlite3_open(this->dataBaseName.c_str(), &this->databaseWithMovies);

  if (errorCode != SQLITE_OK)
    throw RepositoryException("Could not open database");

  std::string createTableStatement = "CREATE TABLE IF NOT EXISTS Movies (Title TEXT PRIMARY KEY, Genre TEXT, YearOfRelease INTEGER, LikesCount INTEGER, Trailer TEXT);";
  char *errorMessage;
  errorCode = sqlite3_exec(this->databaseWithMovies, createTableStatement.c_str(), NULL, 0, &errorMessage);
  free(errorMessage);
  if (errorCode != SQLITE_OK)
    throw RepositoryException("Could not create table");
}

DBRepository::~DBRepository()
{
  sqlite3_close(this->databaseWithMovies);
}

void DBRepository::addMovie(const Movie &movieToBeAdded)
{
  Repository::addMovie(movieToBeAdded);
  std::string insertStatement = "INSERT INTO Movies VALUES ('" + movieToBeAdded.getTitle() + "', '" + movieToBeAdded.getGenre() + "', " + std::to_string(movieToBeAdded.getYearOfRelease()) + ", " + std::to_string(movieToBeAdded.getLikesCount()) + ", '" + movieToBeAdded.getTrailer() + "');";
  char *errorMessage;
  int errorCode = sqlite3_exec(this->databaseWithMovies, insertStatement.c_str(), NULL, 0, &errorMessage);
  free(errorMessage);
  if (errorCode != SQLITE_OK)
    throw RepositoryException("Could not add movie");
}

void DBRepository::removeMovie(Movie &movieToBeRemoved)
{
  std::string deleteStatement = "DELETE FROM Movies WHERE Title = '" + movieToBeRemoved.getTitle() + "' AND Genre = '" + movieToBeRemoved.getGenre() + "' AND YearOfRelease = " + std::to_string(movieToBeRemoved.getYearOfRelease()) + ";";
  char *errorMessage;
  int errorCode = sqlite3_exec(this->databaseWithMovies, deleteStatement.c_str(), NULL, 0, &errorMessage);
  free(errorMessage);
  if (errorCode != SQLITE_OK)
    throw RepositoryException("Could not remove movie");
  Repository::removeMovie(movieToBeRemoved);
}

void DBRepository::updateMovie(int positionOfMovieToBeUpdated, const Movie &updatedMovie)
{
  std::string updateStatement = "UPDATE Movies SET Title = '" + updatedMovie.getTitle() + "', Genre = '" + updatedMovie.getGenre() + "', YearOfRelease = " + std::to_string(updatedMovie.getYearOfRelease()) + ", LikesCount = " + std::to_string(updatedMovie.getLikesCount()) + ", Trailer = '" + updatedMovie.getTrailer() + "' WHERE Title = '" + this->movies[positionOfMovieToBeUpdated].getTitle() + "' AND Genre = '" + this->movies[positionOfMovieToBeUpdated].getGenre() + "' AND YearOfRelease = " + std::to_string(this->movies[positionOfMovieToBeUpdated].getYearOfRelease()) + ";";
  Repository::updateMovie(positionOfMovieToBeUpdated, updatedMovie);
  char *errorMessage;
  int errorCode = sqlite3_exec(this->databaseWithMovies, updateStatement.c_str(), NULL, 0, &errorMessage);
  free(errorMessage);
  if (errorCode != SQLITE_OK)
    throw RepositoryException("Could not update movie");
}

void DBRepository::removeMovieByPosition(int positionOfMovieToBeRemoved)
{
  this->removeMovie(this->movies[positionOfMovieToBeRemoved]);
}

void DBRepository::loadMoviesIntoRepository()
{
  std::string selectStatement = "SELECT * FROM Movies;";
  sqlite3_stmt *statement;
  int errorCode = sqlite3_prepare_v2(this->databaseWithMovies, selectStatement.c_str(), -1, &statement, NULL);
  if (errorCode != SQLITE_OK)
  {
    free(statement);
    throw RepositoryException("Could not load movies into repository");
  }
  while (sqlite3_step(statement) == SQLITE_ROW)
  {
    std::string title = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 0)));
    std::string genre = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 1)));
    int yearOfRelease = sqlite3_column_int(statement, 2);
    int likesCount = sqlite3_column_int(statement, 3);
    std::string trailer = std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 4)));

    Movie movie(title, genre, trailer, yearOfRelease, likesCount);
    try
    {
      this->addMovie(movie);
    }
    catch (const std::exception &e)
    {
    }
  }
  sqlite3_finalize(statement);
}