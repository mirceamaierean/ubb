#include <QApplication>
#include "repository.h"
#include "window.h"
#include "session.h"
#include "stats.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repository repo;

    Session session{repo};

    for (auto department : repo.getDepartments())
    {
        auto *window = new Window(session, department);
        window->show();
    }

    auto *stats = new Statistics(session);
    stats->show();

    return QApplication::exec();
}