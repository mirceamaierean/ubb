#pragma once

#include "Movie.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace Positions {
    const int INDEX_NOT_FOUND = -1;
}

class Repository {
protected:
    std::vector<Movie> movies;

public:
    Repository();

    virtual ~Repository();

    virtual void loadMoviesIntoRepository() {};

    virtual void saveMovies() {};

    virtual void addMovie(const Movie &);

    virtual void removeMovie(Movie &);

    virtual void removeMovieByPosition(int);

    virtual void updateMovie(int, const Movie &);

    bool validatePosition(int) const;

    std::vector<Movie> getMovies() const;

    size_t getMoviesCount() const;

    Movie getMovieByPosition(int) const;

    int returnPosition(Movie &);

    void clearDataFromRepository();

    void modifyLikesCountOfMovieByPosition(int, int);
};