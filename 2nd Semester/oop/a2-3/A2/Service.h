//
// Created by Mircea Maierean on 14.03.2023.
//
#pragma once    // this is a preprocessor directive
#ifndef A23_914MAIEREANMIRCEA_SERVICE_H
#define A23_914MAIEREANMIRCEA_SERVICE_H
#endif //A23_914MAIEREANMIRCEA_SERVICE_H
#include "Repository.h"

typedef struct {
    Repository* repository;
} Service;

Service* createService(Repository* );
void destroyService(Service* );
int addMedicineService(Service*, Medicine*);
int deleteMedicineService(Service*, Medicine*);
int updateMedicineService(Service*, Medicine *, Medicine*);
DynamicArray *getMedicineBasedOnFiltering(Service*, char*, OperationOfComparison);
DynamicArray *getMedicineThatAreInAShortSupply(Service*, int, OperationOfComparisonBetweenMedicines);

