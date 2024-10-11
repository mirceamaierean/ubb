#include "UserWidget.h"
#include "QtWidgets/qlabel.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

using namespace CONSTANTS;

QHBoxLayout *UserWidget::createComboBoxLayout()
{
    QHBoxLayout *comboBoxLayout = new QHBoxLayout;
    QLabel *label = new QLabel("Format of Watchlist Export", this);
    QComboBox *watchFileType = new QComboBox(this);
    watchFileType->addItem("CSV");
    watchFileType->addItem("HTML");
    comboBoxLayout->addWidget(label);
    comboBoxLayout->addWidget(watchFileType);

    return comboBoxLayout;
}

QHBoxLayout *UserWidget::createGenreGroupFilter()
{
    QHBoxLayout *movieGenreGroupFilter = new QHBoxLayout;
    QLabel *movieGenreFilter = new QLabel("Find Movies By Genre", this);
    QLineEdit *movieGenreInputFilter = new QLineEdit(this);
    QPushButton *filterMoviesByGenre = new QPushButton("Fetch Data", this);
    movieGenreGroupFilter->addWidget(movieGenreFilter);
    movieGenreGroupFilter->addWidget(movieGenreInputFilter);
    movieGenreGroupFilter->addWidget(filterMoviesByGenre);

    return movieGenreGroupFilter;
}

QVBoxLayout *UserWidget::createDeleteMovieFromWatchListLayout()
{
    QVBoxLayout *deleteMovieFromWatchlistLayout = new QVBoxLayout;
    QLabel *deleteMovieFromWatchlist = new QLabel("Enter the title of the movie you have just watched", this);
    QLineEdit *deleteMovieFromWatchList = new QLineEdit(this);
    QPushButton *deleteMovieFromWatchlistByTitle = new QPushButton("Remove from watchlist", this);
    deleteMovieFromWatchlistLayout->addWidget(deleteMovieFromWatchlist);
    deleteMovieFromWatchlistLayout->addWidget(deleteMovieFromWatchList);
    deleteMovieFromWatchlistLayout->addWidget(deleteMovieFromWatchlistByTitle);

    return deleteMovieFromWatchlistLayout;
}

QHBoxLayout *UserWidget::createMovieTitleLayout()
{
    QLabel *movieTitle = new QLabel("Title of Movie", this);
    QLineEdit *movieTitleInput = new QLineEdit(this);
    QHBoxLayout *movieTitleGroup = new QHBoxLayout;
    movieTitleGroup->addWidget(movieTitle);
    movieTitleGroup->addWidget(movieTitleInput);

    return movieTitleGroup;
}

QHBoxLayout *UserWidget::createMovieGenreLayout()
{
    QLabel *movieGenre = new QLabel("Genre of Movie", this);
    QLineEdit *movieGenreInput = new QLineEdit(this);
    QHBoxLayout *movieGenreGroup = new QHBoxLayout;
    movieGenreGroup->addWidget(movieGenre);
    movieGenreGroup->addWidget(movieGenreInput);

    return movieGenreGroup;
}

QHBoxLayout *UserWidget::createMovieYearLayout()
{
    QLabel *movieYear = new QLabel("Year of Release", this);
    QLineEdit *movieYearInput = new QLineEdit(this);
    QHBoxLayout *movieYearGroup = new QHBoxLayout;
    movieYearGroup->addWidget(movieYear);
    movieYearGroup->addWidget(movieYearInput);

    return movieYearGroup;
}

QHBoxLayout *UserWidget::createButtonsLayout()
{
    QHBoxLayout *buttons = new QHBoxLayout;
    QPushButton *addMovieToWatchList = new QPushButton("Add movie to your watchlist", this);
    QPushButton *nextMovie = new QPushButton("Show next movie", this);
    QPushButton *exportWatchlist = new QPushButton("Export your watchlist", this);
    buttons->addWidget(addMovieToWatchList);
    buttons->addWidget(nextMovie);
    buttons->addWidget(exportWatchlist);

    return buttons;
}

QVBoxLayout *UserWidget::createWatchListInformation(QHBoxLayout *movieGenreGroupFilter, QVBoxLayout *deleteMovieFromWatchlistLayout)
{
    QVBoxLayout *movieInformation = new QVBoxLayout;
    QHBoxLayout *buttons = createButtonsLayout();
    QHBoxLayout *movieTitleGroup = createMovieTitleLayout();
    QHBoxLayout *movieGenreGroup = createMovieGenreLayout();
    QHBoxLayout *movieYearGroup = createMovieYearLayout();

    movieInformation->setSpacing(DEFAULT_SPACING);
    movieInformation->addLayout(movieGenreGroupFilter);
    movieInformation->addLayout(movieTitleGroup);
    movieInformation->addLayout(movieGenreGroup);
    movieInformation->addLayout(movieYearGroup);
    movieInformation->addLayout(buttons);
    movieInformation->addLayout(deleteMovieFromWatchlistLayout);

    return movieInformation;
}

UserWidget::UserWidget(QWidget *parent)
{
    QHBoxLayout *secondLayout = new QHBoxLayout();
    QVBoxLayout *secondLayoutFirstHalf = new QVBoxLayout;
    QHBoxLayout *comboBoxLayout = createComboBoxLayout();
    QHBoxLayout *movieGenreGroupFilter = createGenreGroupFilter();
    QVBoxLayout *deleteMovieFromWatchlistLayout = createDeleteMovieFromWatchListLayout();

    QVBoxLayout *watchlistInformation = createWatchListInformation(movieGenreGroupFilter, deleteMovieFromWatchlistLayout);

    secondLayoutFirstHalf->addLayout(comboBoxLayout);

    secondLayout->addLayout(secondLayoutFirstHalf);
    secondLayout->addLayout(watchlistInformation);

    this->setLayout(secondLayout);
}
