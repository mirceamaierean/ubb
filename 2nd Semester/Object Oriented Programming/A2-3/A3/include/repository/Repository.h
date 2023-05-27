#ifndef A23_914MAIEREANMIRCEA_REPOSITORY_H
#define A23_914MAIEREANMIRCEA_REPOSITORY_H
#endif // A23_914MAIEREANMIRCEA_REPOSITORY_H
#pragma once
#include "../domain/DynamicArray.h"

typedef struct
{
    DynamicArray *dynamicArray;
} Repository;

Repository *createRepository();
int getRepositoryLength(Repository *);
int checkIfMedicineIsInRepository(Repository *, Medicine *);
void destroyRepository(Repository *);
void addMedicineToRepository(Repository *, Medicine *);
void deleteMedicineFromRepository(Repository *, int);
void updateMedicineFromRepository(Repository *, int, Medicine *);
Medicine *getMedicineFromRepository(Repository *, int);
void sortMedicineBasedOnCondition(Repository *, OperationOfComparisonBetweenMedicines);
DynamicArray *getDynamicArray(Repository *);
Repository *copyRepository(Repository *);
void setRepository(Repository *, Repository *);