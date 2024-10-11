//
// Created by Mircea Maierean on 15.03.2023.
//
#ifndef A23_914MAIEREANMIRCEA_DYNAMICARRAY_H
#define A23_914MAIEREANMIRCEA_DYNAMICARRAY_H

#endif //A23_914MAIEREANMIRCEA_DYNAMICARRAY_H
#pragma once
#include "Medicine.h"

typedef void *TElem;

typedef void (*DestroyElementFunctionPointer)(TElem);

typedef struct {
    TElem *elements;
    int length, capacity;
    DestroyElementFunctionPointer destroyElementFunctionPointer;
} DynamicArray;

DynamicArray *createDynamicArray(int, DestroyElementFunctionPointer);
void destroyDynamicArray(DynamicArray *);
TElem *getElementOnPosition(DynamicArray *, int);
void addElementToDynamicArray(DynamicArray *, TElem);
void deleteElementFromDynamicArray(DynamicArray *, int);
void updateElementOnPosition(DynamicArray *, int, TElem);
void swapElementsOnDynamicArray(DynamicArray *, int, int);
