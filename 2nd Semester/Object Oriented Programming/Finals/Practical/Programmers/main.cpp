#include <QApplication>
#include <QPushButton>
#include "Session.h"
#include "Window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Session session;

    for (auto &person : session.getPersons())
    {
        auto *window = new Window(session, person);
        window->show();
    }
    return QApplication::exec();
}
