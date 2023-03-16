#include <stdio.h>
#include "Repository.h"
#include "Service.h"
#include "ui.h"

int main(int argc, char *argv[]) {
    Repository *repository = createRepository();
    Service *service = createService(repository);
    UI *ui = createUI(service);
    startUI(ui);
    destroyUI(ui);
    return 0;
}