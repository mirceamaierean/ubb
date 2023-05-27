#include "../../include/repository/UndoRedoRepository.h"
#include "../../include/repository/Repository.h"
#include <stdlib.h>
#include <string.h>

UndoRedoRepository *createUndoRedoRepository(int typeOfUndoRedo)
{
  UndoRedoRepository *undoRedoRepository = (UndoRedoRepository *)malloc(sizeof(UndoRedoRepository));
  if (typeOfUndoRedo == 1)
  {
    undoRedoRepository->undoOperations = createDynamicArray(1000, destroyOperation);
    undoRedoRepository->redoOperations = createDynamicArray(1000, destroyOperation);
  }
  else
  {
    undoRedoRepository->undoOperations = createDynamicArray(1000, destroyDynamicArray);
    undoRedoRepository->redoOperations = createDynamicArray(1000, destroyDynamicArray);
  }
  return undoRedoRepository;
}

void destroyUndoOperations(UndoRedoRepository *undoRedoRepository)
{
  destroyDynamicArray(getUndoOperations(undoRedoRepository));
}

void destroyRedoOperations(UndoRedoRepository *undoRedoRepository)
{
  destroyDynamicArray(getRedoOperations(undoRedoRepository));
}

DynamicArray *getUndoOperations(UndoRedoRepository *undoRedoRepository)
{
  return undoRedoRepository->undoOperations;
}

DynamicArray *getRedoOperations(UndoRedoRepository *undoRedoRepository)
{
  return undoRedoRepository->redoOperations;
}

void resetRedoOperations(UndoRedoRepository *undoRedoRepository)
{
  destroyRedoOperations(undoRedoRepository);
  undoRedoRepository->redoOperations = createDynamicArray(1000, destroyOperation);
}

void resetRedoDynamicArray(UndoRedoRepository *undoRedoRepository)
{
  destroyRedoOperations(undoRedoRepository);
  undoRedoRepository->redoOperations = createDynamicArray(1000, destroyDynamicArray);
}

void destroyUndoRedoRepository(UndoRedoRepository *undoRedoRepository)
{
  destroyUndoOperations(undoRedoRepository);
  destroyRedoOperations(undoRedoRepository);
  free(undoRedoRepository);
}

void addUndoOperation(UndoRedoRepository *undoRedoRepository, Operation *operation)
{
  addElementToDynamicArray(getUndoOperations(undoRedoRepository), operation);
}

void addRedoOperation(UndoRedoRepository *undoRedoRepository, Operation *operation)
{
  addElementToDynamicArray(getRedoOperations(undoRedoRepository), operation);
}

void addUndoDynamicArray(UndoRedoRepository *undoRedoRepository, DynamicArray *dynamicArray)
{
  addElementToDynamicArray(getUndoOperations(undoRedoRepository), dynamicArray);
}

void addRedoDynamicArray(UndoRedoRepository *UndoRedoRepository, DynamicArray *dynamicArray)
{
  addElementToDynamicArray(getRedoOperations(UndoRedoRepository), dynamicArray);
}

Operation *getUndoOperation(UndoRedoRepository *undoRedoRepository)
{
  DynamicArray *undoOperations = getUndoOperations(undoRedoRepository);
  return (Operation *)getElementOnPosition(undoOperations, getLengthOfDynamicArray(undoOperations) - 1);
}

Operation *getRedoOperation(UndoRedoRepository *undoRedoRepository)
{
  DynamicArray *redoOperations = getRedoOperations(undoRedoRepository);
  return (Operation *)getElementOnPosition(redoOperations, getLengthOfDynamicArray(redoOperations) - 1);
}

DynamicArray *getUndoDynamicArray(UndoRedoRepository *undoRedoRepository)
{
  DynamicArray *undoOperations = getUndoOperations(undoRedoRepository);
  return (DynamicArray *)getElementOnPosition(undoOperations, getLengthOfDynamicArray(undoOperations) - 1);
}

DynamicArray *getRedoDynamicArray(UndoRedoRepository *undoRedoRepository)
{
  DynamicArray *redoOperations = getRedoOperations(undoRedoRepository);
  return (DynamicArray *)getElementOnPosition(redoOperations, getLengthOfDynamicArray(redoOperations) - 1);
}

void removeUndoOperation(UndoRedoRepository *undoRedoRepository)
{
  DynamicArray *undoOperations = getUndoOperations(undoRedoRepository);
  deleteElementFromDynamicArray(undoOperations, getLengthOfDynamicArray(undoOperations) - 1);
}

void removeRedoOperation(UndoRedoRepository *undoRedoRepository)
{
  DynamicArray *redoOperations = getRedoOperations(undoRedoRepository);
  deleteElementFromDynamicArray(redoOperations, getLengthOfDynamicArray(redoOperations) - 1);
}