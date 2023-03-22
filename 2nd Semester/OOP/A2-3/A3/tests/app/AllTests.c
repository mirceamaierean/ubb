#ifndef A23_914MAIEREANMIRCEA_ALLTESTS_H
#define A23_914MAIEREANMIRCEA_ALLTESTS_H

#endif // A23_914MAIEREANMIRCEA_ALLTESTS_H

#include "AllTests.h"
#include "../include/domain/DynamicArrayTest.h"
#include "../include/domain/MedicineTest.h"
#include "../include/service/ServiceTest.h"
#include <stdio.h>

void testAll()
{
  // testDynamicArrayAll();
  testMedicineAll();
  testAllService();
}