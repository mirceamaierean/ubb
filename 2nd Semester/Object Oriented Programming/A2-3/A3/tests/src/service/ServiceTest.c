#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../../include/service/ServiceTest.h"
#include "../../../include/domain/Medicine.h"
#include "../../../include/service/Service.h"

void testStartService(int typeOfUndoRedo)
{
  Repository *repository = createRepository();
  UndoRedoRepository *undoRedoRepository = createUndoRedoRepository(typeOfUndoRedo);
  Service *service = createService(repository, undoRedoRepository, typeOfUndoRedo);
  assert(getRepository(service) == repository);
  assert(getUndoRedoRepository(service) == undoRedoRepository);
  assert(getTypeOfUndoRedo(service) == typeOfUndoRedo);
  generateRandomEntries(service, 10);
  assert(getRepositoryLength(getRepository(service)) == 10);
  destroyService(service);
}

void testPerformOperationsOnMedicineService(int typeOfUndoRedo)
{
  Repository *repository = createRepository();
  UndoRedoRepository *undoRedoRepository = createUndoRedoRepository(typeOfUndoRedo);
  Service *service = createService(repository, undoRedoRepository, typeOfUndoRedo);
  Medicine *medicine = createMedicine("AA", 15, 10, 10);
  // Test to see if a new element is added
  assert(addMedicineService(service, medicine) == 1);
  Medicine *medicine2 = createMedicine("AA", 15, 15, 20);
  // Element already exists, so quantity must be updated
  assert(addMedicineService(service, medicine2) == 0);
  // Check the length to see that it was indeed only updated
  assert(getRepositoryLength(getRepository(service)) == 1);
  // Assertion to see if the quantity was updated
  Medicine *medicine3 = createMedicine("AB", 12, 25, 20);
  assert(updateMedicineService(service, copyMedicine(medicine2), copyMedicine(medicine3)) == 1);
  // Test to see if a non existing medicine is not deleted
  Medicine *medicine4 = createMedicine("AC", 15, 30, 20);
  assert(deleteMedicineService(service, medicine4) == 0);
  // Test to ensure that non existing medicines are not updated
  assert(updateMedicineService(service, medicine4, copyMedicine(medicine3)) == 0);
  // Test to see if an existing medicine
  assert(deleteMedicineService(service, medicine3) == 1);
  // Add multiple medicines
  destroyMedicine(medicine2);
  destroyMedicine(medicine3);
  medicine2 = createMedicine("AAAAAA", 20, 30, 10);
  assert(addMedicineService(service, medicine2) == 1);
  medicine3 = createMedicine("AABABABA", 20, 35, 10);
  assert(addMedicineService(service, medicine3) == 1);
  medicine4 = createMedicine("BBBBB", 20, 45, 10);
  assert(addMedicineService(service, medicine4) == 1);

  assert(getRepositoryLength(getRepository(service)) == 3);

  // Test to see if all the entities have been stored in undo
  int lengthOfUndoArray = getLengthOfDynamicArray(getUndoOperations(getUndoRedoRepository(service))), lengthOfRedoArray = getLengthOfDynamicArray(getRedoOperations(getUndoRedoRepository(service)));
  assert(lengthOfUndoArray == 7 && lengthOfRedoArray == 0);
  for (int i = 0; i < lengthOfUndoArray; ++i)
    assert(undoRedoService(service, getUndoOperations(getUndoRedoRepository(service)), getRedoOperations(getUndoRedoRepository(service))) == 1);

  lengthOfUndoArray = getLengthOfDynamicArray(getUndoOperations(getUndoRedoRepository(service))), lengthOfRedoArray = getLengthOfDynamicArray(getRedoOperations(getUndoRedoRepository(service)));

  assert(lengthOfUndoArray == 0 && lengthOfRedoArray == 7);
  for (int i = 0; i < lengthOfRedoArray; ++i)
    assert(undoRedoService(service, getRedoOperations(getUndoRedoRepository(service)), getUndoOperations(getUndoRedoRepository(service))) == 1);

  assert(getRepositoryLength(getRepository(service)) == 3);

  // Test to see the filtering of medicines
  OperationOfComparison operation = &medicineContainsString;
  char stringToSearchFor[101] = "";
  DynamicArray *medicinesFiltered = getMedicineBasedOnFiltering(service, stringToSearchFor, operation);
  assert(getLengthOfDynamicArray(medicinesFiltered) == 3);
  destroyDynamicArray(medicinesFiltered);
  char stringToSearchFor1[101] = "AA";
  medicinesFiltered = getMedicineBasedOnFiltering(service, stringToSearchFor1, operation);
  assert(getLengthOfDynamicArray(medicinesFiltered) == 2);
  destroyDynamicArray(medicinesFiltered);
  char stringNotToSearchAfter[101] = "AA";
  operation = &medicineDoesNotContainString;
  medicinesFiltered = getMedicineBasedOnFiltering(service, stringNotToSearchAfter, operation);
  assert(getLengthOfDynamicArray(medicinesFiltered) == 1);
  destroyDynamicArray(medicinesFiltered);

  // Test to see filtering on quantity
  OperationOfComparisonBetweenMedicines operationComparisonMedicines = &firstMedicineIsInAShorterSupplyThanSecondMedicine;
  DynamicArray *medicinesQuantityFilter = getMedicineThatAreInAShortSupply(service, 36, operationComparisonMedicines);
  assert(getLengthOfDynamicArray(medicinesQuantityFilter) == 2);
  medicine2 = createMedicine("AAAAAA", 20, 30, 10);
  medicine3 = createMedicine("AABABABA", 20, 35, 10);
  medicine4 = createMedicine("BBBBB", 20, 45, 10);
  assert(compareMedicines((Medicine *)getElementOnPosition(medicinesQuantityFilter, 0), medicine2));
  destroyDynamicArray(medicinesFiltered);
  operationComparisonMedicines = &firstMedicineIsInAGreaterSupplyThanSecondMedicine;
  medicinesQuantityFilter = getMedicineThatAreInAShortSupply(service, 36, operationComparisonMedicines);
  assert(getLengthOfDynamicArray(medicinesQuantityFilter) == 2);
  assert(compareMedicines((Medicine *)getElementOnPosition(medicinesQuantityFilter, 0), medicine3));
  destroyDynamicArray(medicinesFiltered);
  destroyMedicine(medicine2);
  destroyMedicine(medicine3);
  destroyMedicine(medicine4);
  destroyService(service);
}

void testAllService()
{
  testStartService(1);
  testStartService(2);
  testPerformOperationsOnMedicineService(1);
  testPerformOperationsOnMedicineService(2);
}