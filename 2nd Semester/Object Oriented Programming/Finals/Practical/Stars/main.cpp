#include <QApplication>
#include "Service.h"
#include "starsModels.h"
#include "AstronautWindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository repository("/Users/mirceamaierean/stars/astronauts.txt", "/Users/mirceamaierean/stars/stars.txt");
    auto *model = new starsModel(repository);

    Service service(repository);
    for (const auto& astronaut : service.getAstronauts())
    {
        auto *astronautWindow = new AstronautWindow(astronaut, service, model);
        astronautWindow->show();
    }
    return QApplication::exec();
}
