#ifndef A23_914MAIEREANMIRCEA_OPERATION_H
#define A23_914MAIEREANMIRCEA_OPERATION_H

#endif // A23_914MAIEREANMIRCEA_OPERATION_H
#pragma once
#include "Medicine.h"

typedef struct
{
  /*
  ** typeOfOperation: 1 - Add, 2 - Delete, 3 - Update
  ** 1) Add medicine1, medicine2 = NULL
  ** 2) Delete medicine1, medicine2 = NULL
  ** 3) Update medicine1, medicine2
  ** Note: In case there has been an add for an element that already exists, it is equivalent to an update, where only the quantity has been affected
  */
  int typeOfOperation;
  Medicine *medicine1, *medicine2;
} Operation;

Operation *createOperation(int typeOfOperation, Medicine *medicine1, Medicine *medicine2);
void destroyOperation(Operation *operation);
int getTypeOfOperation(Operation *operation);
Medicine *getMedicine1(Operation *operation);
Medicine *getMedicine2(Operation *operation);
