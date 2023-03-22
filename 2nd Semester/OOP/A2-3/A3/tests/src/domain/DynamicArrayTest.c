#include "../../include/domain/DynamicArrayTest.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void testDynamicArrayAll()
{
  DynamicArray *dynamicArray = createDynamicArray(1, destroyMedicine);
  assert(dynamicArray);
  assert(getLengthOfDynamicArray(dynamicArray) == 0);
  assert(getCapacityOfDynamicArray(dynamicArray) == 1);

  Medicine *medicine = createMedicine("Paracetamol", 17, 23, 10);
  addElementToDynamicArray(dynamicArray, medicine);
  assert(getLengthOfDynamicArray(dynamicArray) == 1);
  assert(getCapacityOfDynamicArray(dynamicArray) == 1);
  assert(compareMedicines((Medicine *)getElementOnPosition(dynamicArray, 0), medicine));

  Medicine *medicine1 = createMedicine("Algocalmin", 25, 72, 12);
  addElementToDynamicArray(dynamicArray, medicine1);
  assert(compareMedicines((Medicine *)getElementOnPosition(dynamicArray, 1), medicine1));
  assert(getLengthOfDynamicArray(dynamicArray) == 2);
  assert(getCapacityOfDynamicArray(dynamicArray) == 2);

  Medicine *medicine2 = createMedicine("Ibuprofen", 10, 12, 0.5);

  addElementToDynamicArray(dynamicArray, medicine2);

  assert(getLengthOfDynamicArray(dynamicArray) == 3);

  assert(getCapacityOfDynamicArray(dynamicArray) == 4);

  assert(!getElementOnPosition(dynamicArray, 3));
  assert(!getElementOnPosition(dynamicArray, -1));

  swapElementsOnDynamicArray(dynamicArray, 0, 2);

  assert(compareMedicines((Medicine *)getElementOnPosition(dynamicArray, 0), medicine2));
  assert(compareMedicines((Medicine *)getElementOnPosition(dynamicArray, 1), medicine1));
  assert(compareMedicines((Medicine *)getElementOnPosition(dynamicArray, 2), medicine));
  deleteElementFromDynamicArray(dynamicArray, 2);
  assert(getLengthOfDynamicArray(dynamicArray) == 2);
  assert(getCapacityOfDynamicArray(dynamicArray) == 4);
  medicine2 = createMedicine("Ibuprofen", 10, 12, 0.5);
  updateElementOnPosition(dynamicArray, 0, medicine2);
  assert(compareMedicines((Medicine *)getElementOnPosition(dynamicArray, 0), medicine2));
  destroyDynamicArray(dynamicArray);
}
