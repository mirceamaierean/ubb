#include <stdio.h>
#include "../include/ui/UI.h"
#include "../include/repository/UndoRedoRepository.h"
#include "../tests/app/AllTests.h"

int main(int argc, char *argv[])
{
    testAll();
    int typeOfUndoRedo = 2;
    Repository *repository = createRepository();
    UndoRedoRepository *undoRedoRepository = createUndoRedoRepository(typeOfUndoRedo);
    Service *service = createService(repository, undoRedoRepository, typeOfUndoRedo);
    UI *ui = createUI(service);
    startUI(ui);
    destroyUI(ui);
    return 0;
}