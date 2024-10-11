#pragma once // this is a preprocessor directive
#ifndef A23_914MAIEREANMIRCEA_SERVICE_H
#define A23_914MAIEREANMIRCEA_SERVICE_H
#endif // A23_914MAIEREANMIRCEA_SERVICE_H
#include "../repository/Repository.h"
#include "../repository/UndoRedoRepository.h"

typedef struct
{
    Repository *repository;
    UndoRedoRepository *undoRedoRepository;
    int typeOfUndoRedo;
} Service;

Service *createService(Repository *, UndoRedoRepository *, int);
void destroyService(Service *);
void generateRandomEntries(Service *, int);
int addMedicineService(Service *, Medicine *);
int deleteMedicineService(Service *, Medicine *);
int updateMedicineService(Service *, Medicine *, Medicine *);
int undoRedoService(Service *, DynamicArray *, DynamicArray *);
int undoService(Service *);
int redoService(Service *);
int getTypeOfUndoRedo(Service *);
DynamicArray *getMedicineBasedOnFiltering(Service *, char *, OperationOfComparison);
DynamicArray *getMedicineThatAreInAShortSupply(Service *, int, OperationOfComparisonBetweenMedicines);
Repository *getRepository(Service *);
UndoRedoRepository *getUndoRedoRepository(Service *);
