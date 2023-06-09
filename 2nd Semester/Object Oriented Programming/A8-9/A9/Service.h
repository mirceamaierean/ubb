#pragma once

#include "Repository.h"
#include "MovieValidator.h"
#include "WatchList.h"
#include "FileWatchList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <initializer_list>

class Service {
private:
    Repository *repository;
    bool adminCredentials;
    FileWatchList *watchList;
    int currentIndexForMovieToBeDisplayed;
    std::vector<int> indexesOfMoviesThatTheUserLikes;
    std::vector<Movie> moviesFilteredByGenre;

public:
    Service();

    ~Service();

    Service &operator=(const Service &other);

    void openTrailerOfMovieInBrowser(int) const;

    void openTrailerOfCurrentMovieInBrowser() const;

    static bool compareStrings(const std::string &, const std::string &);

    void addMovie(Movie);

    void removeMovieByPosition(int);

    void updateMovie(int, Movie);

    FileWatchList *getWatchList() const { return this->watchList; };

    std::vector<Movie> getMovies() const;

    int getMoviesCount() const;

    Movie getMovieByPosition(int) const;

    void setAdminCredentials(bool);

    bool getAdminCredentials();

    void incrementIndexOfCurrentMovieToBeDisplayed();

    std::vector<Movie> getMoviesByGenre(const std::string &);

    std::vector<Movie> getMoviesFromWatchList() const;

    void removeWatchedMovieFromWatchList(int, bool);

    void addMovieToWatchList(const Movie &);

    void addCurrentMovieToWatchList();

    void increaseLikesCountOfMovie(Movie &);

    void setTypeOfWatchList(FileWatchList *);

    void setTypeOfRepository(Repository *);

    void displayPlaylist();

    void checkIfMovieIsAlreadyInThePlaylist(const Movie &);

    void clearFile(const std::string &);

    Movie getCurrentMovieToBeDisplayed();

    std::map<std::string, int> getMapOfMoviesByGenre();
};