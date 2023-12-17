#include "Service.h"
#include "Exceptions.h"
#include "CSVWatchList.h"
#include "FileRepository.h"
#include <string>

Service::Service() {
    this->repository = nullptr;
    this->adminCredentials = false;
    this->watchList = nullptr;
}

Service::~Service() {
    delete this->watchList;
    delete this->repository;
}

Service &Service::operator=(const Service &other) {
    if (this == &other)
        return *this;
    this->repository = other.repository;
    this->adminCredentials = other.adminCredentials;
    this->watchList = other.watchList;
    return *this;
}

bool Service::compareStrings(const std::string &firstComparedString, const std::string &secondComparedString) {
    if (firstComparedString.size() != secondComparedString.size())
        return false;
    for (int index = 0; firstComparedString[index]; ++index)
        if (tolower(firstComparedString[index]) != tolower(secondComparedString[index]))
            return false;
    return true;
}

void Service::setAdminCredentials(bool adminCredentials) {
    this->adminCredentials = adminCredentials;
}

bool Service::getAdminCredentials() {
    return this->adminCredentials;
}

void Service::addMovie(Movie movie) {
    // If the movie is already in the repository, we don't add it
    if (this->repository->validatePosition(this->repository->returnPosition(movie)))
        throw DuplicateMovieException();

    this->repository->addMovie(movie);
}

void Service::removeMovieByPosition(int positionOfMovie) {
    if (!this->repository->validatePosition(positionOfMovie))
        throw InvalidPositionException();
    this->repository->removeMovieByPosition(positionOfMovie);
}

void Service::updateMovie(int position, Movie movie) {
    if (!this->repository->validatePosition(position))
        throw InvalidPositionException();

    if (this->repository->returnPosition(movie) != Positions::INDEX_NOT_FOUND)
        throw DuplicateMovieException();

    this->repository->updateMovie(position, movie);
}

std::vector<Movie> Service::getMovies() const {
    return this->repository->getMovies();
}

int Service::getMoviesCount() const {
    return this->repository->getMoviesCount();
}

Movie Service::getMovieByPosition(int position) const {
    if (!this->repository->validatePosition(position))
        throw InvalidPositionException();
    return this->repository->getMovieByPosition(position);
}

std::vector<Movie> Service::getMoviesByGenre(const std::string &genreOfMovie) {
    this->moviesFilteredByGenre.clear();
    this->currentIndexForMovieToBeDisplayed = 0;
    for (const auto &movie: this->repository->getMovies()) {
        std::string genreOfCurrentMovie = movie.getGenre();
        if (genreOfMovie.empty() || (this->compareStrings(genreOfCurrentMovie, genreOfMovie)))
            this->moviesFilteredByGenre.push_back(movie);
    }
    return this->moviesFilteredByGenre;
}

void Service::incrementIndexOfCurrentMovieToBeDisplayed() {
    this->currentIndexForMovieToBeDisplayed++;
}

Movie Service::getCurrentMovieToBeDisplayed() {
    if (this->currentIndexForMovieToBeDisplayed == this->moviesFilteredByGenre.size())
        this->currentIndexForMovieToBeDisplayed = 0;
    this->openTrailerOfCurrentMovieInBrowser();
    return this->moviesFilteredByGenre[this->currentIndexForMovieToBeDisplayed];
}

std::vector<Movie> Service::getMoviesFromWatchList() const {
    return this->watchList->getMovies();
}

void Service::openTrailerOfMovieInBrowser(int positionOfMovieInTheDynamicArray) const {
    Movie movieWhoseTrailerWillBeDisplayedInTheBrowser = this->getMovieByPosition(positionOfMovieInTheDynamicArray);
    movieWhoseTrailerWillBeDisplayedInTheBrowser.openTrailerInBrowser();
}

void Service::openTrailerOfCurrentMovieInBrowser() const {
    Movie currentMovie = this->moviesFilteredByGenre[this->currentIndexForMovieToBeDisplayed];
    currentMovie.openTrailerInBrowser();
}

void Service::addMovieToWatchList(const Movie &movieToAddToWatchList) {
    this->watchList->checkIfMovieIsAlreadyInThePlaylist(movieToAddToWatchList);
    this->watchList->addMovie(movieToAddToWatchList);
}

void Service::addCurrentMovieToWatchList() {
    this->addMovieToWatchList(this->moviesFilteredByGenre[this->currentIndexForMovieToBeDisplayed]);
}

void Service::increaseLikesCountOfMovie(Movie &movieForWhichTheLikesCountWillBeIncreased) {
    int positionOfMovieThatTheUserHasJustLiked = this->repository->returnPosition(
            movieForWhichTheLikesCountWillBeIncreased);
    this->repository->modifyLikesCountOfMovieByPosition(positionOfMovieThatTheUserHasJustLiked, 1);
}

void Service::setTypeOfWatchList(FileWatchList *fileWatchList) {
    this->watchList = fileWatchList;
}

void Service::removeWatchedMovieFromWatchList(int positionOfMovie, bool likedMovie) {
    Movie currentMovieInWatchList = this->watchList->getMovieByPosition(positionOfMovie);
    if (likedMovie)
        for (auto movie: this->repository->getMovies())
            if (movie == currentMovieInWatchList) {
                this->increaseLikesCountOfMovie(movie);
                break;
            }
    this->watchList->removeMovieFromPlaylist(positionOfMovie, likedMovie);
}

void Service::displayPlaylist() {
    this->watchList->openInApp();
}

void Service::checkIfMovieIsAlreadyInThePlaylist(const Movie &movie) {
    this->watchList->checkIfMovieIsAlreadyInThePlaylist(movie);
}

void Service::setTypeOfRepository(Repository *repository) {
    this->repository = repository;
    this->repository->loadMoviesIntoRepository();
}

void Service::clearFile(const std::string &fileName) {
    std::ofstream file(fileName);
    file.close();
}

std::map<std::string, int> Service::getMapOfMoviesByGenre() {
    std::map<std::string, int> mapOfMoviesByGenre;
    for (const auto &movie: this->repository->getMovies()) {
        std::string genreOfCurrentMovie = movie.getGenre();
        if (mapOfMoviesByGenre.find(genreOfCurrentMovie) == mapOfMoviesByGenre.end())
            mapOfMoviesByGenre[genreOfCurrentMovie] = 1;
        else
            ++mapOfMoviesByGenre[genreOfCurrentMovie];
    }
    return mapOfMoviesByGenre;
}
