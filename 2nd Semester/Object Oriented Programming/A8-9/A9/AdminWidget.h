#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qtablewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <vector>
#include <QMessageBox>
#include "Movie.h"
#include "Service.h"
#include "Exceptions.h"

namespace CONSTANT {
    const int TABLE_COLUMN_COUNT = 5;
    const int DEFAULT_SPACING = 20;
    const int TITLE_COLUMN = 0;
    const int GENRE_COLUMN = 1;
    const int YEAR_COLUMN = 2;
    const int LIKES_COLUMN = 3;
    const int TRAILER_COLUMN = 4;
    const int TITLE_COLUMN_WIDTH = 300;
}

class AdminWidget : public QWidget {
Q_OBJECT
private:
    Service &service;
public:
    AdminWidget(Service &service, QWidget *parent = nullptr);

    void createTableWidget();

    ~AdminWidget() {};
    QTableWidget *movieTable;
    QPushButton *addMovieButton, *deleteMovieButton, *updateMovieButton, *displayPlotButton;
    QLineEdit *movieTitleInput, *movieGenreInput, *movieYearOfReleaseInput, *movieLikesCountInput, *movieTrailerInput;

    QHBoxLayout *createButtonsForManagingMovies();

    QHBoxLayout *createMovieTitle();

    QHBoxLayout *createMovieGenreLayout();

    QHBoxLayout *createMovieYearOfReleaseLayout();

    QHBoxLayout *createLikesCountLayout();

    QHBoxLayout *createMovieTrailerLayout();

public slots:

    void addMovie();

    void addMovieToTable(const Movie &movie) const;

    void deleteMovie();

    void updateMovie();

    void displayCurrentSelectedMovie();

    void displayPlot();
};

#endif // ADMINWIDGET_H
