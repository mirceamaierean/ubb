#include "AdminWidget.h"
#include "QtWidgets/qlabel.h"
#include "QtWidgets/qtablewidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <utility>
#include "qcustomplot.h"

using namespace CONSTANT;

QHBoxLayout *AdminWidget::createButtonsForManagingMovies() {
    auto *buttons = new QHBoxLayout();
    this->addMovieButton = new QPushButton("Add Movie", this);
    this->deleteMovieButton = new QPushButton("Delete Movie", this);
    this->updateMovieButton = new QPushButton("Update Movie", this);
    this->displayPlotButton = new QPushButton("Display Plot", this);

    buttons->addWidget(addMovieButton);
    buttons->addWidget(deleteMovieButton);
    buttons->addWidget(updateMovieButton);
    buttons->addWidget(displayPlotButton);

    return buttons;
}

QHBoxLayout *AdminWidget::createMovieTitle() {
    auto *movieTitle = new QLabel("Title of Movie", this);
    this->movieTitleInput = new QLineEdit(this);
    auto *movieTitleGroup = new QHBoxLayout();
    movieTitleGroup->addWidget(movieTitle);
    movieTitleGroup->addWidget(movieTitleInput);

    return movieTitleGroup;
}

QHBoxLayout *AdminWidget::createMovieGenreLayout() {
    auto *movieGenre = new QLabel("Genre of Movie", this);
    movieGenreInput = new QLineEdit(this);
    auto *movieGenreGroup = new QHBoxLayout();
    movieGenreGroup->addWidget(movieGenre);
    movieGenreGroup->addWidget(movieGenreInput);

    return movieGenreGroup;
}

QHBoxLayout *AdminWidget::createMovieYearOfReleaseLayout() {
    auto *movieYear = new QLabel("Year of Release", this);
    movieYearOfReleaseInput = new QLineEdit(this);
    auto *movieYearGroup = new QHBoxLayout();
    movieYearGroup->addWidget(movieYear);
    movieYearGroup->addWidget(movieYearOfReleaseInput);

    return movieYearGroup;
}

QHBoxLayout *AdminWidget::createLikesCountLayout() {
    auto *movieLikes = new QLabel("Likes", this);
    movieLikesCountInput = new QLineEdit(this);
    auto *movieLikesGroup = new QHBoxLayout();
    movieLikesGroup->addWidget(movieLikes);
    movieLikesGroup->addWidget(movieLikesCountInput);

    return movieLikesGroup;
}

QHBoxLayout *AdminWidget::createMovieTrailerLayout() {
    auto *movieTrailer = new QLabel("Trailer", this);
    movieTrailerInput = new QLineEdit(this);
    auto *movieTrailerGroup = new QHBoxLayout();
    movieTrailerGroup->addWidget(movieTrailer);
    movieTrailerGroup->addWidget(movieTrailerInput);

    return movieTrailerGroup;
}

AdminWidget::AdminWidget(Service &service, QWidget *parent) : service(service), QWidget(parent) {
    auto *adminLayout = new QVBoxLayout;
    auto *movieInformation = new QVBoxLayout;

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
    this->createTableWidget();
    adminLayout->addWidget(movieTable);
    adminLayout->addLayout(movieInformation);
    this->setLayout(adminLayout);

    QObject::connect(this->addMovieButton, &QPushButton::clicked, this, &AdminWidget::addMovie);
    QObject::connect(this->deleteMovieButton, &QPushButton::clicked, this, &AdminWidget::deleteMovie);
    QObject::connect(this->movieTable, &QTableWidget::itemSelectionChanged, this,
                     &AdminWidget::displayCurrentSelectedMovie);
    QObject::connect(this->updateMovieButton, &QPushButton::clicked, this, &AdminWidget::updateMovie);
    QObject::connect(this->displayPlotButton, &QPushButton::clicked, this, &AdminWidget::displayPlot);
}

void AdminWidget::createTableWidget() {
    movieTable = new QTableWidget();
    QStringList header = {"Title", "Genre", "Year of Release", "Number of Likes", "Trailer"};
    movieTable->setColumnCount(TABLE_COLUMN_COUNT);
    movieTable->setColumnWidth(TITLE_COLUMN, TITLE_COLUMN_WIDTH);
    movieTable->setHorizontalHeaderLabels(header);
    for (const auto &movie: this->service.getMovies())
        addMovieToTable(movie);
}

void AdminWidget::addMovieToTable(const Movie &movie) const {
    int rowCount = movieTable->rowCount();
    movieTable->insertRow(rowCount);
    movieTable->setItem(rowCount, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(movie.getTitle())));
    movieTable->setItem(rowCount, GENRE_COLUMN, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
    movieTable->setItem(rowCount, YEAR_COLUMN, new QTableWidgetItem(QString::number(movie.getYearOfRelease())));
    movieTable->setItem(rowCount, LIKES_COLUMN, new QTableWidgetItem(QString::number(movie.getLikesCount())));
    movieTable->setItem(rowCount, TRAILER_COLUMN, new QTableWidgetItem(QString::fromStdString(movie.getTrailer())));
}

void AdminWidget::addMovie() {
    std::string title = this->movieTitleInput->text().toStdString();
    std::string genre = this->movieGenreInput->text().toStdString();
    int yearOfRelease = this->movieYearOfReleaseInput->text().toInt();
    int likesCount = this->movieLikesCountInput->text().toInt();
    std::string trailer = this->movieTrailerInput->text().toStdString();

    try {
        MovieValidator::validateMovieIdentifiers(title, genre, std::to_string(yearOfRelease), trailer,
                                                 std::to_string(likesCount));
        Movie movie = Movie(title, genre, trailer, yearOfRelease, likesCount);
        this->service.addMovie(movie);
        this->addMovieToTable(movie);
        this->movieTitleInput->clear();
        this->movieGenreInput->clear();
        this->movieYearOfReleaseInput->clear();
        this->movieLikesCountInput->clear();
        this->movieTrailerInput->clear();
    }
    catch (MovieExceptions &exception) {
        QMessageBox::critical(this, "Error", "Invalid Fields");
    }
    catch (DuplicateMovieException &exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
}

void AdminWidget::deleteMovie() {
    int selectedRow = this->movieTable->currentRow();
    try {
        this->service.removeMovieByPosition(selectedRow);
    }
    catch (InvalidPositionException &exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
    this->movieTable->removeRow(selectedRow);
}

void AdminWidget::displayCurrentSelectedMovie() {
    int selectedRow = this->movieTable->currentRow();

    if (selectedRow == -1)
        return;

    std::string title = this->movieTable->item(selectedRow, TITLE_COLUMN)->text().toStdString();
    std::string genre = this->movieTable->item(selectedRow, GENRE_COLUMN)->text().toStdString();
    int yearOfRelease = this->movieTable->item(selectedRow, YEAR_COLUMN)->text().toInt();
    int likesCount = this->movieTable->item(selectedRow, LIKES_COLUMN)->text().toInt();
    std::string trailer = this->movieTable->item(selectedRow, TRAILER_COLUMN)->text().toStdString();

    this->movieTitleInput->setText(QString::fromStdString(title));
    this->movieGenreInput->setText(QString::fromStdString(genre));
    this->movieYearOfReleaseInput->setText(QString::number(yearOfRelease));
    this->movieLikesCountInput->setText(QString::number(likesCount));
    this->movieTrailerInput->setText(QString::fromStdString(trailer));
}

void AdminWidget::updateMovie() {
    int selectedRow = this->movieTable->currentRow();
    std::string title = this->movieTitleInput->text().toStdString();
    std::string genre = this->movieGenreInput->text().toStdString();
    int yearOfRelease = this->movieYearOfReleaseInput->text().toInt();
    int likesCount = this->movieLikesCountInput->text().toInt();
    std::string trailer = this->movieTrailerInput->text().toStdString();

    try {
        MovieValidator::validateMovieIdentifiers(title, genre, std::to_string(yearOfRelease), trailer,
                                                 std::to_string(likesCount));
        Movie movie = Movie(title, genre, trailer, yearOfRelease, likesCount);
        this->service.updateMovie(selectedRow, movie);
        this->movieTable->setItem(selectedRow, TITLE_COLUMN, new QTableWidgetItem(QString::fromStdString(title)));
        this->movieTable->setItem(selectedRow, GENRE_COLUMN, new QTableWidgetItem(QString::fromStdString(genre)));
        this->movieTable->setItem(selectedRow, YEAR_COLUMN, new QTableWidgetItem(QString::number(yearOfRelease)));
        this->movieTable->setItem(selectedRow, LIKES_COLUMN, new QTableWidgetItem(QString::number(likesCount)));
        this->movieTable->setItem(selectedRow, TRAILER_COLUMN, new QTableWidgetItem(QString::fromStdString(trailer)));
    }
    catch (MovieExceptions &exception) {
        QMessageBox::critical(this, "Error", "Invalid Fields");
    }
    catch (InvalidPositionException &exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
    catch (DuplicateMovieException &exception) {
        QMessageBox::critical(this, "Error", exception.what());
    }
}

void AdminWidget::displayPlot() {

    std::map<std::string, int> genreCount = this->service.getMapOfMoviesByGenre();

    QCustomPlot *customPlot = new QCustomPlot;

    customPlot->setFixedWidth(800);
    customPlot->setFixedHeight(500);
    customPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QCPBars *genres = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    genres->setAntialiased(false);
    genres->setStackingGap(1);
    genres->setName("Genres");
    // set color to green
    genres->setPen(QPen(QColor(0, 0, 0)));
    genres->setBrush(QColor(17, 140, 54));

    QVector<double> ticks;
    QVector<double> moviesData;
    QVector<QString> labels;
    int positionOfBarChartInTheGraph = 0;
    for (auto &iteratorForBarChart : genreCount) {
        ticks << ++positionOfBarChartInTheGraph;
        labels << QString::fromStdString(iteratorForBarChart.first);
        moviesData << iteratorForBarChart.second;
    }
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);


    textTicker->addTicks(ticks, labels);
    genres->setData(ticks, moviesData);

    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setLabel("Genre");
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 8);
    customPlot->xAxis->grid()->setVisible(true);

    customPlot->yAxis->setRange(0, 12.1);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Number of movies");
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->show();
}