#pragma once

#include "Repository.h"

class FileRepository : public Repository {
private:
    std::string filePath;

public:
    FileRepository(const std::string &filePath) : filePath{"../../../../" + filePath} {};

    ~FileRepository() override;

    void loadMoviesIntoRepository() override;

    void saveMovies() override;

    void addMovie(const Movie &) override;

    void removeMovie(Movie &) override;

    void removeMovieByPosition(int) override;

    void updateMovie(int, const Movie &) override;
};