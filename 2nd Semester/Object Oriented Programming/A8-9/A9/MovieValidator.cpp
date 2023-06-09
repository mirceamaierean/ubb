#include "MovieValidator.h"

MovieExceptions::MovieExceptions(std::vector<std::invalid_argument> errors) {
    this->errors = errors;
}

MovieExceptions::MovieExceptions(const std::string &error) {
    this->errors.emplace_back(error);
}

void MovieValidator::validateMovieTitle(const std::string &titleOfMovieToBeValidated) {
    if (titleOfMovieToBeValidated.empty())
        throw std::invalid_argument("The title of the movie cannot be empty!");
}

void MovieValidator::validateMovieGenre(const std::string &genreOfMovieToBeValidated) {
    if (genreOfMovieToBeValidated.empty())
        throw std::invalid_argument("The genre of the movie cannot be empty!");
}

void MovieValidator::validateMovieYearOfRelease(const std::string &yearOfReleaseOfMovieToBeValidated) {
    int yearOfReleaseOfMovieToBeValidatedAsInteger;

    try {
        yearOfReleaseOfMovieToBeValidatedAsInteger = std::stoi(yearOfReleaseOfMovieToBeValidated);
    }
    catch (const std::exception &e) {
        throw std::invalid_argument("The year of release of the movie must be an integer!");
    }

    if (yearOfReleaseOfMovieToBeValidatedAsInteger < 0)
        throw std::invalid_argument("The year of release of the movie must be a positive integer!");
}

void MovieValidator::validateMovieNumberOfLikes(const std::string &numberOfLikesOfMovieToBeValidated) {
    int numberOfLikesOfMovieToBeValidatedAsInteger;
    try {
        numberOfLikesOfMovieToBeValidatedAsInteger = std::stoi(numberOfLikesOfMovieToBeValidated);
    }
    catch (const std::exception &e) {
        throw std::invalid_argument("The number of likes of the movie must be an integer!");
    }
}

void MovieValidator::validateMovieTrailer(const std::string &trailerOfMovieToBeValidated) {
    const std::regex pattern(
            "((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");

    if (!std::regex_match(trailerOfMovieToBeValidated, pattern))
        throw std::invalid_argument("Invalid trailer link");
}

void MovieValidator::validateMovieIdentifiers(const std::string &titleOfMovieToBeValidated,
                                              const std::string &genreOfMovieToBeValidated,
                                              const std::string &yearOfReleaseOfMovieToBeValidated,
                                              const std::string &trailerOfMovieToBeValidated,
                                              const std::string &numberOfLikesOfMovieToBeValidated) {
    std::vector<std::invalid_argument> errors;
    try {
        validateMovieTitle(titleOfMovieToBeValidated);
    }
    catch (const std::invalid_argument &error) {
        errors.push_back(error);
    }

    try {
        validateMovieGenre(genreOfMovieToBeValidated);
    }
    catch (const std::invalid_argument &error) {
        errors.push_back(error);
    }

    try {
        validateMovieYearOfRelease(yearOfReleaseOfMovieToBeValidated);
    }
    catch (const std::invalid_argument &error) {
        errors.push_back(error);
    }

    try {
        validateMovieNumberOfLikes(numberOfLikesOfMovieToBeValidated);
    }
    catch (const std::invalid_argument &error) {
        errors.push_back(error);
    }

    try {
        validateMovieTrailer(trailerOfMovieToBeValidated);
    }
    catch (const std::invalid_argument &error) {
        errors.push_back(error);
    }

    if (errors.size() > 0)
        throw MovieExceptions(errors);
}

std::vector<std::invalid_argument> MovieExceptions::returnErrors() {
    return this->errors;
}

const char *MovieExceptions::what() {
    std::string errors = "";
    for (const auto &error: this->errors) {
        errors += error.what();
        errors += "\n";
    }

    return errors.c_str();
}
