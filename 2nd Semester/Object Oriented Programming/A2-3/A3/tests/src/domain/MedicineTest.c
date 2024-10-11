#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../../include/domain/MedicineTest.h"
#include "../../../include/domain/Medicine.h"

void testMedicineCreateAndDelete()
{
  Medicine *medicine = createMedicine("Paracetamol", 10, 12, 0.5);
  assert(medicine != NULL);
  assert(strcmp(getNameOfMedicine(medicine), "Paracetamol") == 0);
  assert(getConcentrationOfMedicine(medicine) == 10);
  assert(getQuantityOfMedicine(medicine) == 12);
  assert(getPriceOfMedicine(medicine) == 0.5);
  destroyMedicine(medicine);
}

void testMedicineCopy()
{
  Medicine *medicine = createMedicine("Algocalmin", 10, 12, 0.5);
  Medicine *copy = copyMedicine(medicine);
  assert(copy != NULL);
  assert(strcmp(getNameOfMedicine(copy), "Algocalmin") == 0);
  assert(getConcentrationOfMedicine(copy) == 10);
  assert(getQuantityOfMedicine(copy) == 12);
  assert(getPriceOfMedicine(copy) == 0.5);
  destroyMedicine(medicine);
  destroyMedicine(copy);
}

void testMedicineFormat()
{
  Medicine *medicine = createMedicine("Algocalmin", 10, 12, 0.5);
  char *formattedMedicineString = formatMedicineAsString(medicine);
  assert(formattedMedicineString != NULL);
  assert(strcmp(formattedMedicineString, "Algocalmin 10.000000 12 0.500000") == 0);
  destroyMedicine(medicine);
  free(formattedMedicineString);
}

void testMedicineComparisons()
{
  Medicine *medicine1 = createMedicine("Algocalmin", 9, 11, 0.5);
  Medicine *medicine2 = createMedicine("Paracetamol", 10, 12, 0.5);
  Medicine *medicine3 = createMedicine("Algocalmin", 9, 11, 0.5);
  assert(compareMedicines(medicine1, medicine2) == 0);
  assert(compareMedicines(medicine2, medicine1) == 0);
  assert(compareMedicines(medicine1, medicine3));
  assert(compareMedicines(medicine3, medicine1));
  assert(medicineContainsString(medicine1, "Algo") == 1);
  assert(medicineContainsString(medicine1, "Paracetamol") == 0);
  assert(medicineDoesNotContainString(medicine1, "Algo") == 0);
  assert(medicineDoesNotContainString(medicine1, "Paracetamol") == 1);
  assert(firstMedicineHasNameSmallerThanSecondMedicine(medicine1, medicine2) == 1);
  assert(firstMedicineHasNameSmallerThanSecondMedicine(medicine2, medicine1) == 0);
  assert(firstMedicineIsInAShorterSupplyThanSecondMedicine(medicine1, medicine2) == 1);
  assert(firstMedicineIsInAShorterSupplyThanSecondMedicine(medicine2, medicine1) == 0);
  assert(firstMedicineIsInAGreaterSupplyThanSecondMedicine(medicine1, medicine2) == 0);
  assert(firstMedicineIsInAGreaterSupplyThanSecondMedicine(medicine2, medicine1) == 1);
  destroyMedicine(medicine1);
  destroyMedicine(medicine2);
  destroyMedicine(medicine3);
}

void testMedicineAll()
{
  testMedicineCreateAndDelete();
  testMedicineCopy();
  testMedicineFormat();
  testMedicineComparisons();
}