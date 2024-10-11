#ifndef MOVIELIST_H
#define MOVIELIST_H

#include <QtWidgets>
#include "Service.h"
#include <vector>

class MovieList : public QTableWidget
{
Q_OBJECT
private:
    std::function<std::vector<Movie>()> getMoviesFunction;
public:
    MovieList(std::function<std::vector<Movie>()> getMoviesFunction, QWidget* parent = Q_NULLPTR){};
    void setMoviesFunction(std::function<std::vector<Movie>()> getMoviesFunction){};
   public slots:
    void reload(){};
};

#endif // MOVIELIST_H
