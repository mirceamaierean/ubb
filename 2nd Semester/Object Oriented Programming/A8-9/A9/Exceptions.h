#pragma once

#include <string>
#include <vector>
#include <exception>

class FileException : public std::exception {
private:
    std::string message;

public:
    explicit FileException(const std::string &message);

    virtual const char *what();
};

class RepositoryException : public std::exception {
protected:
    std::string message;

public:
    RepositoryException();

    explicit RepositoryException(const std::string &message);

    ~RepositoryException() override {};

    virtual const char *what();
};

class DuplicateMovieException : public RepositoryException {
public:
    const char *what();
};

class InvalidPositionException : public RepositoryException {
public:
    const char *what();
};