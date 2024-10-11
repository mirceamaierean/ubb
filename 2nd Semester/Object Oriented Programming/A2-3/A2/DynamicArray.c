//
// Created by Mircea Măierean on 15.03.2023.
//
#include "DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>

DynamicArray *createDynamicArray(int capacity, DestroyElementFunctionPointer destroyElementFunctionPointer) {
    DynamicArray *dynamicArray = (DynamicArray *) malloc(sizeof(DynamicArray));
    dynamicArray->elements = (TElem *) malloc(capacity * sizeof(TElem));
    dynamicArray->length = 0;
    dynamicArray->capacity = capacity;
    dynamicArray->destroyElementFunctionPointer = destroyElementFunctionPointer;

    return dynamicArray;
}

void destroyDynamicArray(DynamicArray *dynamicArray) {
    for (int i = 0; i < dynamicArray->length; ++i) {
        dynamicArray->destroyElementFunctionPointer(dynamicArray->elements[i]);
    }
    free(dynamicArray->elements);
    free(dynamicArray);
}

TElem *getElementOnPosition(DynamicArray *dynamicArray, int position) {
    if (position < 0 || position >= dynamicArray->length) {
        return NULL;
    }
    return dynamicArray->elements[position];
}

// create a resize function
void resizeDynamicArray(DynamicArray *dynamicArray) {
    dynamicArray->capacity *= 2;
    dynamicArray->elements = (TElem *) realloc(dynamicArray->elements, dynamicArray->capacity * sizeof(TElem));
}

void updateElementOnPosition(DynamicArray *dynamicArray, int position, TElem element) {
    if (position < 0 || position >= dynamicArray->length) {
        return;
    }
    dynamicArray->destroyElementFunctionPointer(dynamicArray->elements[position]);
    dynamicArray->elements[position] = element;
}

void swapElementsOnDynamicArray(DynamicArray *dynamicArray, int position1, int position2) {
    if (position1 < 0 || position1 >= dynamicArray->length || position2 < 0 || position2 >= dynamicArray->length) {
        return;
    }
    TElem aux = dynamicArray->elements[position1];
    dynamicArray->elements[position1] = dynamicArray->elements[position2];
    dynamicArray->elements[position2] = aux;
}

void addElementToDynamicArray(DynamicArray *dynamicArray, TElem element) {
    if (dynamicArray->length == dynamicArray->capacity) {
        resizeDynamicArray(dynamicArray);
    }
    dynamicArray->elements[dynamicArray->length] = element;
    dynamicArray->length++;
}

void deleteElementFromDynamicArray(DynamicArray *dynamicArray, int position) {
    if (position < 0 || position >= dynamicArray->length) {
        return;
    }
    dynamicArray->destroyElementFunctionPointer(dynamicArray->elements[position]);
    for (int i = position; i < dynamicArray->length - 1; ++i) {
        dynamicArray->elements[i] = dynamicArray->elements[i + 1];
    }
    dynamicArray->elements[dynamicArray->length - 1] = NULL;
    dynamicArray->length--;
}