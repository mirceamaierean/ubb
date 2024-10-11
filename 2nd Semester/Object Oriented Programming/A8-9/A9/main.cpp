#include "mainwindow.h"

#include <QApplication>
#include "Service.h"
#include "testMovie.h"
#include "testRepository.h"
#include "testService.h"

int main(int argc, char *argv[]) {
    TestsMovie::testMovie();
    TestsRepository::testRepository();
    TestsService::testService();
    QApplication mainApplication(argc, argv);
    QCoreApplication::setApplicationName("Movie Rental");
    Service service;
    MainWindow mainWindow(service);
    mainWindow.show();
    return mainApplication.exec();
}

