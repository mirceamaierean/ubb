#include "UserWidget.h"
#include "QtWidgets/qlabel.h"
#include "Exceptions.h"

using namespace CONSTANTS;

QHBoxLayout *UserWidget::createComboBoxLayout() {
    auto *comboBoxLayout = new QHBoxLayout;
    auto *label = new QLabel("Format of Watchlist Export", this);
    watchFileType = new QComboBox(this);
    watchFileType->addItem("Select Format");
    watchFileType->addItem("CSV");
    watchFileType->addItem("HTML");
    comboBoxLayout->addWidget(label);
    comboBoxLayout->addWidget(watchFileType);

    return comboBoxLayout;
}

QHBoxLayout *UserWidget::createGenreGroupFilter() {
    auto *movieGenreGroupFilter = new QHBoxLayout;
    auto *movieGenreFilter = new QLabel("Find Movies By Genre", this);
    movieGenreInputFilter = new QLineEdit(this);
    this->filterMoviesByGenre = new QPushButton("Fetch Data", this);
    movieGenreGroupFilter->addWidget(movieGenreFilter);
    movieGenreGroupFilter->addWidget(movieGenreInputFilter);
    movieGenreGroupFilter->addWidget(filterMoviesByGenre);

    return movieGenreGroupFilter;
}

QVBoxLayout *UserWidget::createDeleteMovieFromWatchListLayout() {
    auto *deleteMovieFromWatchlistLayout = new QVBoxLayout;
    auto *deleteMovieFromWatchlist = new QLabel("Enter the index from the watchlist of the movie you want to delete",
                                                this);
    this->indexOfMovieInPlaylist = new QLineEdit(this);

    this->deleteMovieFromWatchlistButton = new QPushButton("Remove from watchlist", this);
    this->giveLikeAndDeleteMovie = new QPushButton("Give Like and Delete Movie From Watchlist", this);

    deleteMovieFromWatchlistLayout->addWidget(deleteMovieFromWatchlist);
    deleteMovieFromWatchlistLayout->addWidget(this->indexOfMovieInPlaylist);

    auto *layoutButtons = new QHBoxLayout;
    layoutButtons->addWidget(giveLikeAndDeleteMovie);
    layoutButtons->addWidget(deleteMovieFromWatchlistButton);

    deleteMovieFromWatchlistLayout->addLayout(layoutButtons);

    return deleteMovieFromWatchlistLayout;
}

QHBoxLayout *UserWidget::createMovieTitleLayout() {
    auto *movieTitle = new QLabel("Title of Movie", this);
    movieTitleInput = new QLineEdit(this);
    auto *movieTitleGroup = new QHBoxLayout;
    movieTitleGroup->addWidget(movieTitle);
    movieTitleGroup->addWidget(movieTitleInput);

    return movieTitleGroup;
}

QHBoxLayout *UserWidget::createMovieGenreLayout() {
    auto *movieGenre = new QLabel("Genre of Movie", this);
    movieGenreInput = new QLineEdit(this);
    auto *movieGenreGroup = new QHBoxLayout;
    movieGenreGroup->addWidget(movieGenre);
    movieGenreGroup->addWidget(movieGenreInput);

    return movieGenreGroup;
}

QHBoxLayout *UserWidget::createMovieYearLayout() {
    auto *movieYear = new QLabel("Year of Release", this);
    movieYearInput = new QLineEdit(this);
    auto *movieYearGroup = new QHBoxLayout;
    movieYearGroup->addWidget(movieYear);
    movieYearGroup->addWidget(movieYearInput);

    return movieYearGroup;
}

QHBoxLayout *UserWidget::createButtonsLayout() {
    auto *buttons = new QHBoxLayout;
    this->addMovieToWatchList = new QPushButton("Add movie to your watchlist", this);
    this->nextMovie = new QPushButton("Show next movie", this);
    this->exportWatchlist = new QPushButton("Export your watchlist", this);
    buttons->addWidget(addMovieToWatchList);
    buttons->addWidget(nextMovie);
    buttons->addWidget(exportWatchlist);

    return buttons;
}

QVBoxLayout *UserWidget::createWatchListInformation(QHBoxLayout *movieGenreGroupFilter,
                                                    QVBoxLayout *deleteMovieFromWatchlistLayout) {
    auto *movieInformation = new QVBoxLayout;
    auto *buttons = createButtonsLayout();
    auto *movieTitleGroup = createMovieTitleLayout();
    auto *movieGenreGroup = createMovieGenreLayout();
    auto *movieYearGroup = createMovieYearLayout();

    movieInformation->setSpacing(DEFAULT_SPACING);
    movieInformation->addLayout(movieGenreGroupFilter);
    movieInformation->addLayout(movieTitleGroup);
    movieInformation->addLayout(movieGenreGroup);
    movieInformation->addLayout(movieYearGroup);
    movieInformation->addLayout(buttons);
    movieInformation->addLayout(deleteMovieFromWatchlistLayout);

    return movieInformation;
}

UserWidget::UserWidget(Service &service, QWidget *parent) : QWidget(parent), service{service} {
    auto *secondLayout = new QHBoxLayout();
    auto *secondLayoutFirstHalf = new QVBoxLayout;
    auto *comboBoxLayout = createComboBoxLayout();
    auto *movieGenreGroupFilter = createGenreGroupFilter();
    auto *deleteMovieFromWatchlistLayout = createDeleteMovieFromWatchListLayout();

    QVBoxLayout *watchlistInformation = createWatchListInformation(movieGenreGroupFilter,
                                                                   deleteMovieFromWatchlistLayout);

    secondLayoutFirstHalf->addLayout(comboBoxLayout);

    secondLayout->addLayout(secondLayoutFirstHalf);
    secondLayout->addLayout(watchlistInformation);

    this->setLayout(secondLayout);

    this->connectSignalsAndSlots();
}

void UserWidget::connectSignalsAndSlots() {
    QObject::connect(this->addMovieToWatchList, &QPushButton::clicked, this, &UserWidget::addMovieToWatchListHandler);
    QObject::connect(this->nextMovie, &QPushButton::clicked, this, &UserWidget::nextMovieHandler);
    QObject::connect(this->exportWatchlist, &QPushButton::clicked, this, &UserWidget::exportWatchlistHandler);
    QObject::connect(this->filterMoviesByGenre, &QPushButton::clicked, this, &UserWidget::filterMoviesByGenreHandler);
    QObject::connect(this->deleteMovieFromWatchlistButton, &QPushButton::clicked, this,
                     &UserWidget::deleteMovieFromWatchlistByTitleHandler);
    QObject::connect(this->watchFileType, &QComboBox::currentTextChanged, this, &UserWidget::watchlistFileTypeHandler);
    QObject::connect(this->giveLikeAndDeleteMovie, &QPushButton::clicked, this, &UserWidget::likeMovieAndDeleteIt);
}

void UserWidget::filterMoviesByGenreHandler() {
    this->movieTitleInput->setText("");
    this->movieGenreInput->setText("");
    this->movieYearInput->setText("");

    auto v = this->service.getMoviesByGenre(this->movieGenreInputFilter->text().toStdString());
    if (!v.empty()) {
        Movie movieToBeDisplayed = this->service.getCurrentMovieToBeDisplayed();
        this->movieTitleInput->setText(QString::fromStdString(movieToBeDisplayed.getTitle()));
        this->movieGenreInput->setText(QString::fromStdString(movieToBeDisplayed.getGenre()));
        this->movieYearInput->setText(QString::fromStdString(std::to_string(movieToBeDisplayed.getYearOfRelease())));
    } else
        QMessageBox::information(this, "Info", "There are no movies with the given genre!");
}

void UserWidget::addMovieToWatchListHandler() {
    if (this->movieTitleInput->text().isEmpty()) {
        QMessageBox::information(this, "Info", "You must introduce a genre first!");
        return;
    }

    try {
        this->service.addCurrentMovieToWatchList();
        QMessageBox::information(this, "Info", "Movie added to watchlist!");
    }
    catch (DuplicateMovieException &e) {
        QMessageBox::information(this, "Info", e.what());
        return;
    }
}

void UserWidget::deleteMovieFromWatchlistByTitleHandler() {

    int indexOfMovieToBeDeleted = this->indexOfMovieInPlaylist->text().toInt();

    if (indexOfMovieToBeDeleted == 0 && this->indexOfMovieInPlaylist->text().toStdString() != "0") {
        QMessageBox::information(this, "Info", "Introduce a valid position!");
        return;
    }

    try {
        this->service.removeWatchedMovieFromWatchList(indexOfMovieToBeDeleted, false);
        QMessageBox::information(this, "Info", "Movie deleted from watchlist!");
    }
    catch (InvalidPositionException &e) {
        QMessageBox::information(this, "Info", "Invalid position");
        return;
    }
}

void UserWidget::nextMovieHandler() {
    if (this->movieTitleInput->text().isEmpty()) {
        QMessageBox::information(this, "Info", "You must introduce a genre first!");
        return;
    }

    this->service.incrementIndexOfCurrentMovieToBeDisplayed();

    Movie movieToBeDisplayed = this->service.getCurrentMovieToBeDisplayed();
    this->movieTitleInput->setText(QString::fromStdString(movieToBeDisplayed.getTitle()));
    this->movieGenreInput->setText(QString::fromStdString(movieToBeDisplayed.getGenre()));
    this->movieYearInput->setText(QString::fromStdString(std::to_string(movieToBeDisplayed.getYearOfRelease())));
}

void UserWidget::exportWatchlistHandler() {
    try {
        this->service.displayPlaylist();
    }
    catch (FileException &caughtException) {
        QMessageBox::information(this, "Info", caughtException.what());
        return;
    }
}

void UserWidget::watchlistFileTypeHandler() {
    if (this->watchFileType->currentText() == "CSV")
        this->service.setTypeOfWatchList(new CSVWatchList{"watchlist.csv"});
    else
        this->service.setTypeOfWatchList(new HTMLWatchList{"watchlist.html"});
}

void UserWidget::likeMovieAndDeleteIt() {
    std::cout << "aici boss\n";
    int indexOfMovieToBeDeleted = this->indexOfMovieInPlaylist->text().toInt();

    if (indexOfMovieToBeDeleted == 0 && this->indexOfMovieInPlaylist->text().toStdString() != "0") {
        QMessageBox::information(this, "Info", "Introduce a valid position!");
        return;
    }

    try {
        this->service.removeWatchedMovieFromWatchList(indexOfMovieToBeDeleted, true);
        QMessageBox::information(this, "Info", "Movie deleted from watchlist!");
    }
    catch (InvalidPositionException &e) {
        QMessageBox::information(this, "Info", "Invalid position");
        return;
    }
}
