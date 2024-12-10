//
// Created by Mircea Maierean on 15.03.2023.
//
#include "Repository.h"
#include <stdlib.h>
#include <string.h>

Repository* createRepository() {
    Repository* repository = (Repository*)malloc(sizeof(Repository));
    repository->dynamicArray = createDynamicArray(10, destroyMedicine);
    return repository;
}

int getRepositoryLength(Repository* repository){
    return repository->dynamicArray->length;
}

void destroyRepository(Repository* repository) {
    destroyDynamicArray(repository->dynamicArray);
    free(repository);
}

void addMedicineToRepository(Repository* repository, Medicine * medicine) {
    addElementToDynamicArray(repository->dynamicArray, medicine);
}

void deleteMedicineFromRepository(Repository* repository, int position) {
    deleteElementFromDynamicArray(repository->dynamicArray, position);
}

void updateMedicineFromRepository(Repository* repository, int position, Medicine* medicine) {
    updateElementOnPosition(repository->dynamicArray, position, medicine);
}

void sortMedicineBasedOnCondition(Repository* repository, OperationOfComparisonBetweenMedicines operationOfComparisonBetweenMedicines) {
    for (int i = 0; i < repository->dynamicArray->length - 1; ++i) {
        for (int j = i + 1; j < repository->dynamicArray->length; ++j) {
            Medicine *medicine1 = (Medicine*)getElementOnPosition(repository->dynamicArray, i);
            Medicine *medicine2 = (Medicine*)getElementOnPosition(repository->dynamicArray, j);
            if (operationOfComparisonBetweenMedicines(medicine2, medicine1) > 0)
                swapElementsOnDynamicArray(repository->dynamicArray, i, j);
        }
    }
}

int checkIfMedicineIsInRepository(Repository* repository, Medicine* medicine) {
    for (int i = 0; i < repository->dynamicArray->length; i++) {
        if (compareMedicines((Medicine*)(getElementOnPosition(repository->dynamicArray, i)), medicine) == 1)
            return i;
    }
    return -1;
}

Medicine *getMedicineFromRepository(Repository *repository, int position) {
    return (Medicine*)(getElementOnPosition(repository->dynamicArray, position));
}

