#pragma once

#include "Movie.h"

class WatchList {
protected:
    std::vector<Movie> movies;

public:
    WatchList() {};

    virtual ~WatchList() {}

    void addMovie(const Movie &);

    Movie getMovieByPosition(int);

    void removeMovieFromPlaylist(int, bool);

    bool isEmpty();

    void checkIfMovieIsAlreadyInThePlaylist(const Movie &);

    std::vector<Movie> getMovies() const { return this->movies; }
};