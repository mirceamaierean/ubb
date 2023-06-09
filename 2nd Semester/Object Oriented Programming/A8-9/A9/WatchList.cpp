#include "WatchList.h"
#include "Exceptions.h"

void WatchList::addMovie(const Movie &movie) {
    this->movies.push_back(movie);
}

bool WatchList::isEmpty() {
    return this->movies.size() == 0;
}

void WatchList::checkIfMovieIsAlreadyInThePlaylist(const Movie &movie) {
    for (auto movieFromPlaylist: this->movies)
        if (movieFromPlaylist.getTitle() == movie.getTitle())
            throw DuplicateMovieException();
}

void WatchList::removeMovieFromPlaylist(int positionOfMovie, bool likedMovie) {
    if (positionOfMovie < 0 || positionOfMovie >= this->movies.size())
        throw InvalidPositionException();
    if (likedMovie)
        this->movies[positionOfMovie].setLikesCount(this->movies[positionOfMovie].getLikesCount() + 1);
    std::vector<Movie>::iterator iteratorPointingToMovieThatWillBeErased = this->movies.begin();
    std::advance(iteratorPointingToMovieThatWillBeErased, positionOfMovie);

    this->movies.erase(iteratorPointingToMovieThatWillBeErased);
}

Movie WatchList::getMovieByPosition(int positionOfMovie) {
    return this->movies[positionOfMovie];
}
