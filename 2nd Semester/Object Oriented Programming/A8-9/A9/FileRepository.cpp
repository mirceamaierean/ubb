#include "FileRepository.h"
#include "Exceptions.h"
#include <fstream>

FileRepository::~FileRepository() {
    this->saveMovies();
}

void FileRepository::loadMoviesIntoRepository() {

    std::ifstream fileInput(this->filePath);

    if (!fileInput.is_open())
        throw FileException("The file could not be opened!");

    Movie readMovieFromTextFile;
    while (true) {
        try {
            fileInput >> readMovieFromTextFile;
            this->addMovie(readMovieFromTextFile);
        }
        catch (MovieExceptions &errorsCaught) {
            break;
        }
    }
}

void FileRepository::saveMovies() {
    std::ofstream fileOutput(this->filePath);

    if (!fileOutput.is_open())
        throw FileException("The file could not be opened!\n");

    for (const auto &movie: this->movies)
        fileOutput << movie << "\n";
    fileOutput.close();
}

void FileRepository::addMovie(const Movie &movieToBeAdded) {
    Repository::addMovie(movieToBeAdded);
    this->saveMovies();
}

void FileRepository::removeMovie(Movie &movieToBeRemoved) {
    Repository::removeMovie(movieToBeRemoved);
    this->saveMovies();
}

void FileRepository::removeMovieByPosition(int positionOfMovieToBeRemoved) {
    Repository::removeMovieByPosition(positionOfMovieToBeRemoved);
    this->saveMovies();
}

void FileRepository::updateMovie(int positionOfMovieToBeUpdated, const Movie &movieWithUpdatedData) {
    Repository::updateMovie(positionOfMovieToBeUpdated, movieWithUpdatedData);
    this->saveMovies();
}
