#include "Repository.h"
#include "Exceptions.h"

using namespace Positions;

Repository::Repository() {
    this->movies = std::vector<Movie>();
}

Repository::~Repository() {
}

void Repository::addMovie(const Movie &movieToBeAdded) {
    this->movies.push_back(movieToBeAdded);
}

void Repository::removeMovie(Movie &movieToBeRemoved) {
    std::vector<Movie>::iterator iteratorPointingToelementThatWillBeErased = std::find(this->movies.begin(),
                                                                                       this->movies.end(),
                                                                                       movieToBeRemoved);
    this->movies.erase(iteratorPointingToelementThatWillBeErased);
}

void Repository::removeMovieByPosition(int positionOfMovieToBeRemoved) {
    this->movies.erase(this->movies.begin() + positionOfMovieToBeRemoved);
}

void Repository::updateMovie(int positionOfMovieToBeUpdated, const Movie &movieWithUpdatedData) {
    this->movies[positionOfMovieToBeUpdated] = movieWithUpdatedData;
}

std::vector<Movie> Repository::getMovies() const {
    return this->movies;
}

size_t Repository::getMoviesCount() const {
    return this->movies.size();
}

Movie Repository::getMovieByPosition(int position) const {
    if (position < 0 || position >= this->movies.size())
        throw InvalidPositionException();
    return this->movies[position];
}

bool Repository::validatePosition(int position) const {
    return position >= 0 && position < this->movies.size();
}

int Repository::returnPosition(Movie &movieForWhichWeWantToGetPosition) {
    auto iteratorForPosition = std::find(this->movies.begin(), this->movies.end(), movieForWhichWeWantToGetPosition);
    if (iteratorForPosition == this->movies.end())
        return INDEX_NOT_FOUND;
    return std::distance(this->movies.begin(), iteratorForPosition);
}

void Repository::modifyLikesCountOfMovieByPosition(int positionOfMovieToBeUpdated, int incrementeLikesCount) {
    Movie movieToBeUpdated = this->getMovieByPosition(positionOfMovieToBeUpdated);
    movieToBeUpdated.setLikesCount(movieToBeUpdated.getLikesCount() + incrementeLikesCount);
    this->updateMovie(positionOfMovieToBeUpdated, movieToBeUpdated);
}

void Repository::clearDataFromRepository() {
    this->movies.clear();
}