#include "../../include/domain/Operation.h"
#include <stdlib.h>
#include <stdio.h>

Operation *createOperation(int typeOfOperation, Medicine *medicine1, Medicine *medicine2)
{
  Operation *operation = (Operation *)malloc(sizeof(Operation));
  operation->typeOfOperation = typeOfOperation;
  operation->medicine1 = createMedicine(medicine1->name, medicine1->concentration, medicine1->quantity, medicine1->price);
  operation->medicine2 = NULL;
  if (medicine2)
    operation->medicine2 = createMedicine(medicine2->name, medicine2->concentration, medicine2->quantity, medicine2->price);
  return operation;
}

Medicine *getMedicine1(Operation *operation)
{
  return operation->medicine1;
}

Medicine *getMedicine2(Operation *operation)
{
  return operation->medicine2;
}

int getTypeOfOperation(Operation *operation)
{
  return operation->typeOfOperation;
}

void destroyOperation(Operation *operation)
{
  destroyMedicine(getMedicine1(operation));
  if (getMedicine2(operation))
    destroyMedicine(getMedicine2(operation));
  free(operation);
}
