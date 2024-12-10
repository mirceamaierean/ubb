#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AdminWidget.h"
#include "UserWidget.h"
#include "Service.h"
#include "FileRepository.h"
#include "Exceptions.h"

namespace CONSTANTS
{
    const std::string FILENAME = "movies.txt";
    const int INITIAL_WIDTH = 300;
    const int INITIAL_HEIGHT = 300;
    const int ADMIN_WIDTH = 1500;
    const int ADMIN_HEIGHT = 400;
    const int USER_WIDTH = 800;
    const int USER_HEIGHT = 400;
    const int ADMIN_LAYOUT_INDEX = 1;
    const int USER_LAYOUT_INDEX = 2;
}

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Service service;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
