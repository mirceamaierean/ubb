#ifndef USERWIDGET_H
#define USERWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace CONSTANTS
{
    const int DEFAULT_SPACING = 20;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    UserWidget(QWidget *parent = nullptr);
    ~UserWidget(){};
    QHBoxLayout *createComboBoxLayout();
    void createMovieGenreFilterSearch(QHBoxLayout *movieGenreGroupFilter);
    QHBoxLayout *createGenreGroupFilter();
    QVBoxLayout *createDeleteMovieFromWatchListLayout();
    QHBoxLayout *createMovieTitleLayout();
    QHBoxLayout *createMovieGenreLayout();
    QHBoxLayout *createMovieYearLayout();
    QVBoxLayout *createMovieInformationLayout(QHBoxLayout *movieGenreGroupFilter);
    QHBoxLayout *createButtonsLayout();
    QVBoxLayout *createWatchListInformation(QHBoxLayout *movieGenreGroupFilter, QVBoxLayout *deleteMovieFromWatchlistLayout);
};

#endif // USERWIDGET_H
