#include "../../include/service/Service.h"
#include "../../include/domain/DynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

Service *createService(Repository *repository, UndoRedoRepository *undoRedoRepository, int typeOfUndoRedo)
{
    Service *service = (Service *)malloc(sizeof(Service));
    service->repository = repository;
    service->undoRedoRepository = undoRedoRepository;
    service->typeOfUndoRedo = typeOfUndoRedo;
    return service;
}

Repository *getRepository(Service *service)
{
    return service->repository;
}

UndoRedoRepository *getUndoRedoRepository(Service *service)
{
    return service->undoRedoRepository;
}

int getTypeOfUndoRedo(Service *service)
{
    return service->typeOfUndoRedo;
}

void destroyService(Service *service)
{
    destroyRepository(getRepository(service));
    destroyUndoRedoRepository(getUndoRedoRepository(service));
    free(service);
}

int updateMedicineService(Service *service, Medicine *medicine, Medicine *newMedicine)
{
    // Because I have performed an operation, I shall delete redo repository (can't redo after performing an operation)
    int indexOfExistingMedicine = checkIfMedicineIsInRepository(getRepository(service), medicine);
    destroyMedicine(medicine);
    if (indexOfExistingMedicine == -1)
    {
        destroyMedicine(newMedicine);
        return 0;
    }
    // I have updated, so I shall update with the values that were before
    if (getTypeOfUndoRedo(service) == 1)
    {
        resetRedoOperations(getUndoRedoRepository(service));
        Medicine *medicineFromRepository = getMedicineFromRepository(getRepository(service), indexOfExistingMedicine);
        Operation *operation = createOperation(3, newMedicine, medicineFromRepository);
        addUndoOperation(getUndoRedoRepository(service), operation);
    }
    else
    {
        resetRedoDynamicArray(getUndoRedoRepository(service));
        DynamicArray *dynamicArray = copyDynamicArrayOfMedicines(getDynamicArray(getRepository(service)));
        addUndoDynamicArray(getUndoRedoRepository(service), dynamicArray);
    }
    updateMedicineFromRepository(getRepository(service), indexOfExistingMedicine, newMedicine);
    return 1;
}

int addMedicineService(Service *service, Medicine *medicine)
{
    int indexOfExistingMedicine = checkIfMedicineIsInRepository(getRepository(service), medicine);
    if (indexOfExistingMedicine == -1)
    {
        // Because I have performed an operation, I shall delete redo repository (can't redo after performing an operation)
        if (getTypeOfUndoRedo(service) == 1)
        {
            resetRedoOperations(getUndoRedoRepository(service));
            Operation *operation = createOperation(2, medicine, NULL);
            addUndoOperation(getUndoRedoRepository(service), operation);
        }
        else
        {
            resetRedoDynamicArray(getUndoRedoRepository(service));
            DynamicArray *dynamicArray = copyDynamicArrayOfMedicines(getDynamicArray(getRepository(service)));
            addUndoDynamicArray(getUndoRedoRepository(service), dynamicArray);
        }
        addMedicineToRepository(getRepository(service), medicine);
        return 1;
    }
    Medicine *existingMedicine = getMedicineFromRepository(getRepository(service), indexOfExistingMedicine);
    Medicine *newMedicine = createMedicine(getNameOfMedicine(existingMedicine), getConcentrationOfMedicine(existingMedicine), getQuantityOfMedicine(existingMedicine) + getQuantityOfMedicine(medicine), getPriceOfMedicine(existingMedicine)), *existingMedicineCopy = copyMedicine(existingMedicine);
    updateMedicineService(service, existingMedicineCopy, newMedicine);
    return 0;
}

int deleteMedicineService(Service *service, Medicine *medicine)
{
    // Because I have performed an operation, I shall delete redo repository (can't redo after performing an operation)
    int indexOfExistingMedicine = checkIfMedicineIsInRepository(getRepository(service), medicine);
    if (indexOfExistingMedicine == -1)
        return 0;
    // I have deleted, so I shall add when I perform undo
    if (getTypeOfUndoRedo(service) == 1)
    {
        resetRedoOperations(getUndoRedoRepository(service));
        addUndoOperation(getUndoRedoRepository(service), createOperation(1, medicine, NULL));
    }
    else
    {
        resetRedoDynamicArray(getUndoRedoRepository(service));
        DynamicArray *dynamicArray = copyDynamicArrayOfMedicines(getDynamicArray(getRepository(service)));
        addUndoDynamicArray(getUndoRedoRepository(service), dynamicArray);
    }
    deleteMedicineFromRepository(getRepository(service), indexOfExistingMedicine);
    return 1;
}

void generateRandomEntries(Service *service, int numberOfEntries)
{
    srand(time(NULL));
    char medicineNames[][50] = {"Paracetamol",
                                "Ibuprofen",
                                "Aspirin",
                                "Nurofen",
                                "Doliprane",
                                "Naproxen",
                                "Diclofenac",
                                "Voltaren",
                                "Cataflam",
                                "Celebrex",
                                "Dolgit",
                                "Dolocordralan",
                                "Dolormin",
                                "Dolotren",
                                "Dolovisano",
                                "Doloxene",
                                "Doxylin",
                                "Panadol",
                                "Bisoprolol",
                                "Captopril"};
    for (int i = 0; i < numberOfEntries; i++)
    {
        int nameIndex = rand() % 20;
        double concentration = (double)(rand() % 1000) / 10.00;
        int quantity = rand() % 1000;
        double price = (double)(rand() % 1000) / 100;
        Medicine *medicine = createMedicine(medicineNames[nameIndex], concentration, quantity, price);
        addMedicineToRepository(getRepository(service), medicine);
    }
}

int undoRedoService(Service *service, DynamicArray *undoFromThisArray, DynamicArray *redoToThisArray)
{
    if (getTypeOfUndoRedo(service) == 1)
    {
        if (getLengthOfDynamicArray(undoFromThisArray) == 0)
            return 0;
        Operation *operation = (Operation *)getElementOnPosition(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
        Operation *operationToBeAddedToRedo = NULL;

        if (getTypeOfOperation(operation) == 1)
        {
            addMedicineToRepository(getRepository(service), copyMedicine(getMedicine1(operation)));
            operationToBeAddedToRedo = createOperation(2, getMedicine1(operation), NULL);
        }
        else if (getTypeOfOperation(operation) == 2)
        {
            deleteMedicineFromRepository(getRepository(service), checkIfMedicineIsInRepository(getRepository(service), getMedicine1(operation)));
            operationToBeAddedToRedo = createOperation(1, getMedicine1(operation), NULL);
        }
        else if (getTypeOfOperation(operation) == 3)
        {
            updateMedicineFromRepository(getRepository(service), checkIfMedicineIsInRepository(getRepository(service), getMedicine1(operation)), copyMedicine(getMedicine2(operation)));
            operationToBeAddedToRedo = createOperation(3, getMedicine2(operation), getMedicine1(operation));
        }
        addElementToDynamicArray(redoToThisArray, operationToBeAddedToRedo);
        deleteElementFromDynamicArray(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
    }
    else if (getTypeOfUndoRedo(service) == 2)
    {
        if (getLengthOfDynamicArray(undoFromThisArray) == 0)
            return 0;
        DynamicArray *dynamicArray = (DynamicArray *)getElementOnPosition(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
        DynamicArray *dynamicArrayToBeAddedToRedo = copyDynamicArrayOfMedicines(getDynamicArray(getRepository(service)));
        addElementToDynamicArray(redoToThisArray, dynamicArrayToBeAddedToRedo);
        DynamicArray *swap1;
        swap1 = getDynamicArray(getRepository(service));
        service->repository->dynamicArray = copyDynamicArrayOfMedicines(dynamicArray);
        destroyDynamicArray(swap1);
        deleteElementFromDynamicArray(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
    }
    return 1;
}

DynamicArray *getMedicineBasedOnFiltering(Service *service, char *string, OperationOfComparison operationOfComparison)
{
    sortMedicineBasedOnCondition(getRepository(service), &firstMedicineHasNameSmallerThanSecondMedicine);
    string[strlen(string) - 1] = '\0';
    DynamicArray *dynamicArray = createDynamicArray(getLengthOfDynamicArray(getDynamicArray(getRepository(service))), destroyMedicine);
    for (int i = 0; i < getRepositoryLength(getRepository(service)); ++i)
    {
        Medicine *medicine = getMedicineFromRepository(getRepository(service), i);
        if (medicine && operationOfComparison(medicine, string))
            addElementToDynamicArray(dynamicArray, copyMedicine(medicine));
    }
    return dynamicArray;
}

DynamicArray *getMedicineThatAreInAShortSupply(Service *service, int quantity, OperationOfComparisonBetweenMedicines operationOfComparisonBetweenMedicines)
{
    sortMedicineBasedOnCondition(getRepository(service), operationOfComparisonBetweenMedicines);
    DynamicArray *dynamicArray = createDynamicArray(getLengthOfDynamicArray(getDynamicArray(getRepository(service))), destroyMedicine);
    for (int i = 0; i < getRepositoryLength(getRepository(service)); ++i)
    {
        Medicine *medicine = getMedicineFromRepository(getRepository(service), i);
        if (medicine && getQuantityOfMedicine(medicine) <= quantity)
            addElementToDynamicArray(dynamicArray, copyMedicine(medicine));
    }
    return dynamicArray;
}
