#include "AdminWidget.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qtablewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QTableWidgetItem>

using namespace CONSTANT;

QHBoxLayout *AdminWidget::createButtonsForManagingMovies()
{
    QHBoxLayout *buttons = new QHBoxLayout();
    QPushButton *addMovie = new QPushButton("Add Movie", this);
    QPushButton *deleteMovie = new QPushButton("Delete Movie", this);
    QPushButton *updateMovie = new QPushButton("Update Movie", this);

    buttons->addWidget(addMovie);
    buttons->addWidget(deleteMovie);
    buttons->addWidget(updateMovie);

    return buttons;
}

QHBoxLayout *AdminWidget::createMovieTitle()
{
    QLabel *movieTitle = new QLabel("Title of Movie", this);
    QLineEdit *movieTitleInput = new QLineEdit(this);
    QHBoxLayout *movieTitleGroup = new QHBoxLayout();
    movieTitleGroup->addWidget(movieTitle);
    movieTitleGroup->addWidget(movieTitleInput);

    return movieTitleGroup;
}

QHBoxLayout *AdminWidget::createMovieGenreLayout()
{
    QLabel *movieGenre = new QLabel("Genre of Movie", this);
    QLineEdit *movieGenreInput = new QLineEdit(this);
    QHBoxLayout *movieGenreGroup = new QHBoxLayout();
    movieGenreGroup->addWidget(movieGenre);
    movieGenreGroup->addWidget(movieGenreInput);

    return movieGenreGroup;
}

QHBoxLayout *AdminWidget::createMovieYearOfReleaseLayout()
{
    QLabel *movieYear = new QLabel("Year of Release", this);
    QLineEdit *movieYearInput = new QLineEdit(this);
    QHBoxLayout *movieYearGroup = new QHBoxLayout();
    movieYearGroup->addWidget(movieYear);
    movieYearGroup->addWidget(movieYearInput);

    return movieYearGroup;
}

QHBoxLayout *AdminWidget::createLikesCountLayout()
{
    QLabel *movieLikes = new QLabel("Likes", this);
    QLineEdit *movieLikesInput = new QLineEdit(this);
    QHBoxLayout *movieLikesGroup = new QHBoxLayout();
    movieLikesGroup->addWidget(movieLikes);
    movieLikesGroup->addWidget(movieLikesInput);

    return movieLikesGroup;
}

QHBoxLayout *AdminWidget::createMovieTrailerLayout()
{
    QLabel *movieTrailer = new QLabel("Trailer", this);
    QLineEdit *movieTrailerInput = new QLineEdit(this);
    QHBoxLayout *movieTrailerGroup = new QHBoxLayout();
    movieTrailerGroup->addWidget(movieTrailer);
    movieTrailerGroup->addWidget(movieTrailerInput);

    return movieTrailerGroup;
}

AdminWidget::AdminWidget(QWidget *parent, std::vector<Movie> movies) : QWidget(parent), movies(movies)
{
    QHBoxLayout *adminLayout = new QHBoxLayout;
    QVBoxLayout *movieInformation = new QVBoxLayout;

    QHBoxLayout *movieTitleGroup = createMovieTitle();
    QHBoxLayout *movieGenreGroup = createMovieGenreLayout();
    QHBoxLayout *movieYearGroup = createMovieYearOfReleaseLayout();
    QHBoxLayout *movieLikesGroup = createLikesCountLayout();
    QHBoxLayout *movieTrailerGroup = createMovieTrailerLayout();
    QHBoxLayout *buttons = createButtonsForManagingMovies();

    movieInformation->setSpacing(DEFAULT_SPACING);
    movieInformation->addLayout(movieTitleGroup);
    movieInformation->addLayout(movieGenreGroup);
    movieInformation->addLayout(movieYearGroup);
    movieInformation->addLayout(movieLikesGroup);
    movieInformation->addLayout(movieTrailerGroup);

    movieInformation->addLayout(buttons);
    adminLayout->addLayout(movieInformation);

    QTableWidget *tableWidget = this->createTableWidget();

    adminLayout->addWidget(tableWidget);
    this->setLayout(adminLayout);
}

QTableWidget *AdminWidget::createTableWidget()
{
    QTableWidget *tableWidget = new QTableWidget();
    QStringList header = {"Title", "Genre", "Year of Release", "Number of Likes", "Trailer"};
    tableWidget->setColumnCount(TABLE_COLUMN_COUNT);
    tableWidget->setColumnWidth(TITLE_COLUMN, TITLE_COLUMN_WIDTH);
    tableWidget->setHorizontalHeaderLabels(header);
    for (auto movie : this->movies)
    {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount);
        tableWidget->setItem(rowCount, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
        tableWidget->setItem(rowCount, GENRE_COLUMN, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
        tableWidget->setItem(rowCount, YEAR_COLUMN, new QTableWidgetItem(QString::number(movie.getYearOfRelease())));
        tableWidget->setItem(rowCount, LIKES_COLUMN, new QTableWidgetItem(QString::number(movie.getLikesCount())));
        tableWidget->setItem(rowCount, TRAILER_COLUMN, new QTableWidgetItem(QString::fromStdString(movie.getTrailer())));
    }
    return tableWidget;
}
