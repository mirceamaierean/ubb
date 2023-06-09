#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AdminWidget.h"
#include "UserWidget.h"
#include "Service.h"
#include "FileRepository.h"
#include "Exceptions.h"

namespace CONSTANTS {
    const std::string FILENAME = "movies.txt";
    const int INITIAL_WIDTH = 300;
    const int INITIAL_HEIGHT = 300;
    const int ADMIN_WIDTH = 200;
    const int ADMIN_HEIGHT = 700;
    const int USER_WIDTH = 800;
    const int USER_HEIGHT = 400;
    const int ADMIN_LAYOUT_INDEX = 1;
    const int USER_LAYOUT_INDEX = 2;
}

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    Service &service;

public:
    MainWindow(Service &service, QWidget *parent = Q_NULLPTR);

    ~MainWindow();

public slots:

    void addMovie(Movie movie);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
