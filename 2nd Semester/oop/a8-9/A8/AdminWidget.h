#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H
#include <QWidget>
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qtablewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <vector>
#include "Movie.h"

namespace CONSTANT
{
    const int TABLE_COLUMN_COUNT = 5;
    const int DEFAULT_SPACING = 20;
    const int TITLE_COLUMN = 0;
    const int GENRE_COLUMN = 1;
    const int YEAR_COLUMN = 2;
    const int LIKES_COLUMN = 3;
    const int TRAILER_COLUMN = 4;
    const int TITLE_COLUMN_WIDTH = 300;
}

class AdminWidget : public QWidget
{
    Q_OBJECT
private:
    std::vector<Movie> movies;

public:
    AdminWidget(QWidget *parent = nullptr, std::vector<Movie> movies = {});
    QTableWidget *createTableWidget();
    ~AdminWidget(){};
    QHBoxLayout * createButtonsForManagingMovies();
    QHBoxLayout * createMovieTitle();
    QHBoxLayout * createMovieGenreLayout();
    QHBoxLayout * createMovieYearOfReleaseLayout();
    QHBoxLayout * createLikesCountLayout();
    QHBoxLayout * createMovieTrailerLayout();
    void createMovieInformationLayout(QVBoxLayout *movieInformation);
};

#endif // ADMINWIDGET_H
