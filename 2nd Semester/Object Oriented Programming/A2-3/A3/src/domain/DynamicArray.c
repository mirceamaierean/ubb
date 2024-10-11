#include "../../include/domain/DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>

DynamicArray *createDynamicArray(int capacity, DestroyElementFunctionPointer destroyElementFunctionPointer)
{
    DynamicArray *dynamicArray = (DynamicArray *)malloc(sizeof(DynamicArray));
    dynamicArray->elements = (TElem *)malloc(capacity * sizeof(TElem));
    dynamicArray->length = 0;
    dynamicArray->capacity = capacity;
    dynamicArray->destroyElementFunctionPointer = destroyElementFunctionPointer;

    return dynamicArray;
}

// create a resize function
void resizeDynamicArray(DynamicArray *dynamicArray)
{
    dynamicArray->capacity *= 2;
    dynamicArray->elements = (TElem *)realloc(dynamicArray->elements, dynamicArray->capacity * sizeof(TElem));
}

int getLengthOfDynamicArray(DynamicArray *dynamicArray)
{
    return dynamicArray->length;
}

int getCapacityOfDynamicArray(DynamicArray *dynamicArray)
{
    return dynamicArray->capacity;
}

TElem *getElements(DynamicArray *dynamicArray)
{
    return dynamicArray->elements;
}

DestroyElementFunctionPointer getDestroyElementFunctionPointer(DynamicArray *dynamicArray)
{
    return dynamicArray->destroyElementFunctionPointer;
}

void setLengthOfDynamicArray(DynamicArray *dynamicArray, int length)
{
    dynamicArray->length = length;
}

TElem *getElementOnPosition(DynamicArray *dynamicArray, int position)
{
    if (position < 0 || position >= getLengthOfDynamicArray(dynamicArray))
        return NULL;
    TElem *elements = getElements(dynamicArray);
    return elements[position];
}

void destroyDynamicArray(DynamicArray *dynamicArray)
{
    for (int i = 0; i < getLengthOfDynamicArray(dynamicArray); i++)
    {
        if (dynamicArray->elements[i])
            dynamicArray->destroyElementFunctionPointer(dynamicArray->elements[i]);
    }
    free(dynamicArray->elements);
    free(dynamicArray);
}

void updateElementOnPosition(DynamicArray *dynamicArray, int position, TElem element)
{
    if (position < 0 || position >= getLengthOfDynamicArray(dynamicArray))
        return;
    DestroyElementFunctionPointer destroyElementFunctionPointer = getDestroyElementFunctionPointer(dynamicArray);
    TElem *elements = getElements(dynamicArray);
    destroyElementFunctionPointer(elements[position]);
    elements[position] = element;
}

void swapElementsOnDynamicArray(DynamicArray *dynamicArray, int position1, int position2)
{
    int length = getLengthOfDynamicArray(dynamicArray);
    TElem *elements = getElements(dynamicArray);
    if (position1 < 0 || position1 >= length || position2 < 0 || position2 >= length)
        return;

    TElem aux = elements[position1];
    elements[position1] = elements[position2];
    elements[position2] = aux;
}

void addElementToDynamicArray(DynamicArray *dynamicArray, TElem element)
{
    int length = getLengthOfDynamicArray(dynamicArray);
    int capacity = getCapacityOfDynamicArray(dynamicArray);
    TElem *elements = getElements(dynamicArray);

    if (length == capacity)
        resizeDynamicArray(dynamicArray);

    elements[length] = element;
    dynamicArray->length += 1;
}

void deleteElementFromDynamicArray(DynamicArray *dynamicArray, int position)
{
    DestroyElementFunctionPointer destroyElementFunctionPointer = getDestroyElementFunctionPointer(dynamicArray);
    TElem *elements = getElements(dynamicArray);
    int length = getLengthOfDynamicArray(dynamicArray);
    if (position < 0 || position >= length)
        return;

    destroyElementFunctionPointer(elements[position]);
    for (int i = position; i < length - 1; ++i)
        elements[i] = elements[i + 1];

    elements[length - 1] = NULL;
    setLengthOfDynamicArray(dynamicArray, length - 1);
}

DynamicArray *copyDynamicArrayOfMedicines(DynamicArray *dynamicArray)
{
    int length = getLengthOfDynamicArray(dynamicArray);
    DynamicArray *copy = createDynamicArray(length, destroyMedicine);
    for (int i = 0; i < length; i++)
    {
        TElem *element = getElementOnPosition(dynamicArray, i);
        addElementToDynamicArray(copy, copyMedicine((Medicine *)element));
    }
    return copy;
}