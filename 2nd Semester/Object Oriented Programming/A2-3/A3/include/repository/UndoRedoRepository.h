#ifndef A23_914MAIEREANMIRCEA_UNDO_REDO_REPOSITORY_H
#define A23_914MAIEREANMIRCEA_UNDO_REDO_REPOSITORY_H
#endif // A23_914MAIEREANMIRCEA_UNDO_REDO_REPOSITORY_H
#pragma once
#include "../domain/DynamicArray.h"
#include "../domain/Operation.h"
#include "../repository/Repository.h"

typedef struct
{
  DynamicArray *undoOperations;
  DynamicArray *redoOperations;
} UndoRedoRepository;

UndoRedoRepository *createUndoRedoRepository(int);
Operation *getUndoOperation(UndoRedoRepository *);
Operation *getRedoOperation(UndoRedoRepository *);
DynamicArray *getUndoDynamicArray(UndoRedoRepository *);
DynamicArray *getRedoDynamicArray(UndoRedoRepository *);
DynamicArray *getUndoOperations(UndoRedoRepository *);
DynamicArray *getRedoOperations(UndoRedoRepository *);
void destroyUndoOperations(UndoRedoRepository *);
void destroyRedoOperations(UndoRedoRepository *);
void resetRedoOperations(UndoRedoRepository *);
void resetRedoDynamicArray(UndoRedoRepository *);
void destroyUndoRedoRepository(UndoRedoRepository *);
void addUndoOperation(UndoRedoRepository *, Operation *);
void addRedoOperation(UndoRedoRepository *, Operation *);
void addUndoDynamicArray(UndoRedoRepository *, DynamicArray *);
void addRedoDynamicArray(UndoRedoRepository *, DynamicArray *);
void removeUndoOperation(UndoRedoRepository *);
void removeRedoOperation(UndoRedoRepository *);
