#ifndef USERWIDGET_H
#define USERWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include "Service.h"
#include "FileWatchList.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"

namespace CONSTANTS
{
    const int DEFAULT_SPACING = 20;
}

class UserWidget : public QWidget
{
    Q_OBJECT
private:
    Service &service;
    QPushButton *filterMoviesByGenre,
                *deleteMovieFromWatchlistButton,
                *giveLikeAndDeleteMovie,
                *addMovieToWatchList,
                *nextMovie,
                *exportWatchlist;
    QLineEdit *movieGenreInputFilter,
              *movieTitleInput,
              *movieGenreInput,
              *indexOfMovieInPlaylist,
              *movieYearInput;
    QComboBox *watchFileType;

public:
    UserWidget(Service &service, QWidget *parent = nullptr);
    ~UserWidget() {};
    QHBoxLayout *createComboBoxLayout();
    QHBoxLayout *createGenreGroupFilter();
    QVBoxLayout *createDeleteMovieFromWatchListLayout();
    QHBoxLayout *createMovieTitleLayout();
    QHBoxLayout *createMovieGenreLayout();
    QHBoxLayout *createMovieYearLayout();
    QHBoxLayout *createButtonsLayout();
    QVBoxLayout *createWatchListInformation(QHBoxLayout *movieGenreGroupFilter, QVBoxLayout *deleteMovieFromWatchlistLayout);
    void connectSignalsAndSlots();
    public slots:
    void filterMoviesByGenreHandler();
    void deleteMovieFromWatchlistByTitleHandler();
    void addMovieToWatchListHandler();
    void nextMovieHandler();
    void exportWatchlistHandler();
    void watchlistFileTypeHandler();
    void likeMovieAndDeleteIt();
};

#endif // USERWIDGET_H
