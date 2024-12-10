#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Movie Rental");
    MainWindow w;
    w.show();
    return a.exec();
}
