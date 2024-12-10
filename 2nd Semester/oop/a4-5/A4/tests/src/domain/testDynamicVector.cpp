#include "../../include/domain/testDynamicVector.h"
#include "../../../include/domain/DynamicVector.h"
#include <cstring>
#include <cassert>
#include <iostream>
#include <cctype>

void TestsDynamicVector::testDynamicVector()
{
  DynamicVector<int> vectorOfIntegers{2};
  vectorOfIntegers.addElementInDynamicVector(10);
  vectorOfIntegers.addElementInDynamicVector(20);
  assert(vectorOfIntegers.getSizeOfDynamicVector() == 2);
  assert(vectorOfIntegers[1] == 20);
  vectorOfIntegers[1] = 25;
  assert(vectorOfIntegers[1] == 25);
  vectorOfIntegers.addElementInDynamicVector(30);
  assert(vectorOfIntegers.getSizeOfDynamicVector() == 3);

  try
  {
    vectorOfIntegers.removeElementFromDynamicVector(-1);
    assert(false);
  }
  catch (const std::exception &caughtException)
  {
    assert(true);
  }
  try
  {
    vectorOfIntegers.getElement(100);
    assert(false);
  }
  catch (const std::exception &caughtException)
  {
    assert(true);
  }

  DynamicVector<int> copyOfVectorOfIntegersWithConstructorBasedOnExistingVector{vectorOfIntegers};
  assert(copyOfVectorOfIntegersWithConstructorBasedOnExistingVector.getSizeOfDynamicVector() == 3);

  DynamicVector<int> copyOfVectorOfIntegersThatReceivesValueBasedOnCopyAssignmentOperator;
  copyOfVectorOfIntegersThatReceivesValueBasedOnCopyAssignmentOperator = vectorOfIntegers;
  assert(copyOfVectorOfIntegersThatReceivesValueBasedOnCopyAssignmentOperator[0] == 10);
  assert(copyOfVectorOfIntegersThatReceivesValueBasedOnCopyAssignmentOperator[0] == 10);
  int returnedPositionFromCopiedVector = copyOfVectorOfIntegersThatReceivesValueBasedOnCopyAssignmentOperator.returnPosition(25);
  assert(returnedPositionFromCopiedVector == 1);
  copyOfVectorOfIntegersThatReceivesValueBasedOnCopyAssignmentOperator.removeElementFromDynamicVector(1);
  assert(copyOfVectorOfIntegersThatReceivesValueBasedOnCopyAssignmentOperator.getSizeOfDynamicVector() == 2);

  // Test iterator
  DynamicVector<int>::Iterator iteratorForVectorOfIntegers = vectorOfIntegers.begin();
  DynamicVector<int>::Iterator copyOfIteratorForVectorOfIntegers = vectorOfIntegers.begin();

  assert(iteratorForVectorOfIntegers == copyOfIteratorForVectorOfIntegers);
  // Test to see if the iterator points to the first element of the vector
  assert(*iteratorForVectorOfIntegers == 10);
  // Test to ensure that the iterator is not equal to the end of the vector
  assert(iteratorForVectorOfIntegers != vectorOfIntegers.end());
  // Test post-increment operator
  iteratorForVectorOfIntegers++;
  assert(*iteratorForVectorOfIntegers == 25);
  // Test pre-increment operator
  ++iteratorForVectorOfIntegers;
  assert(*iteratorForVectorOfIntegers == 30);
}