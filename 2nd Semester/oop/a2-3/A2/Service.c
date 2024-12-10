//
// Created by Mircea Maierean on 14.03.2023.
//
#include "Service.h"
#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>

Service* createService(Repository* repository) {
    Service* service = (Service*)malloc(sizeof(Service));
    service->repository = repository;
    return service;
}

void destroyService(Service* service) {
    destroyRepository(service->repository);
    free(service);
}

int addMedicineService(Service* service, Medicine* medicine) {
    int indexOfExistingMedicine = checkIfMedicineIsInRepository(service->repository, medicine);
    if (indexOfExistingMedicine == -1) {
        addMedicineToRepository(service->repository, medicine);
        sortMedicineBasedOnCondition(service->repository, &firstMedicineHasNameSmallerThanSecondMedicine);
        return 1;
    }
    Medicine *existingMedicine = getMedicineFromRepository(service->repository, indexOfExistingMedicine);
    existingMedicine->quantity += medicine->quantity;
    return 0;
}

int deleteMedicineService(Service* service, Medicine* medicine) {
    int indexOfExistingMedicine = checkIfMedicineIsInRepository(service->repository, medicine);
    if (indexOfExistingMedicine == -1)
        return 0;
    deleteMedicineFromRepository(service->repository, indexOfExistingMedicine);
    return 1;
}

int updateMedicineService(Service* service, Medicine* medicine, Medicine* newMedicine) {
    int indexOfExistingMedicine = checkIfMedicineIsInRepository(service->repository, medicine);
    destroyMedicine(medicine);
    if (indexOfExistingMedicine == -1)
    {
        destroyMedicine(newMedicine);
        return 0;
    }
    updateMedicineFromRepository(service->repository, indexOfExistingMedicine, newMedicine);
    sortMedicineBasedOnCondition(service->repository, &firstMedicineHasNameSmallerThanSecondMedicine);
   return 1;
}

DynamicArray* getMedicineBasedOnFiltering(Service* service, char* string, OperationOfComparison operationOfComparison) {
    string[strlen(string) - 1] = '\0';
    DynamicArray* dynamicArray = createDynamicArray(10, destroyMedicine);
    for (int i = 0; i < getRepositoryLength(service->repository); ++i) {
        Medicine* medicine = getMedicineFromRepository(service->repository, i);
        if (operationOfComparison(medicine, string)) {
            Medicine *medicineCopy = createMedicine(medicine->name, medicine->concentration, medicine->quantity,
                                                    medicine->price);
            addElementToDynamicArray(dynamicArray, medicineCopy);
        }
    }
    return dynamicArray;
}

DynamicArray* getMedicineThatAreInAShortSupply(Service* service, int quantity, OperationOfComparisonBetweenMedicines operationOfComparisonBetweenMedicines) {
    sortMedicineBasedOnCondition(service->repository, operationOfComparisonBetweenMedicines);
    DynamicArray* dynamicArray = createDynamicArray(10, destroyMedicine);
    for (int i = 0; i < getRepositoryLength(service->repository); ++i) {
        Medicine* medicine = getMedicineFromRepository(service->repository, i);
        if (medicine->quantity <= quantity) {
            Medicine *medicineCopy = createMedicine(medicine->name, medicine->concentration, medicine->quantity, medicine->price);
            addElementToDynamicArray(dynamicArray, medicineCopy);
        }
    }
    return dynamicArray;
}