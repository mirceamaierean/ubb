#include "../../include/repository/Repository.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Repository *createRepository()
{
    Repository *repository = (Repository *)malloc(sizeof(Repository));
    repository->dynamicArray = createDynamicArray(1000, destroyMedicine);
    return repository;
}

DynamicArray *getDynamicArray(Repository *repository)
{
    return repository->dynamicArray;
}

int getRepositoryLength(Repository *repository)
{
    return getLengthOfDynamicArray(getDynamicArray(repository));
}

void destroyRepository(Repository *repository)
{
    destroyDynamicArray(getDynamicArray(repository));
    free(repository);
}

void addMedicineToRepository(Repository *repository, Medicine *medicine)
{
    addElementToDynamicArray(getDynamicArray(repository), medicine);
}

void deleteMedicineFromRepository(Repository *repository, int position)
{
    deleteElementFromDynamicArray(getDynamicArray(repository), position);
}

void updateMedicineFromRepository(Repository *repository, int position, Medicine *medicine)
{
    updateElementOnPosition(getDynamicArray(repository), position, medicine);
}

void sortMedicineBasedOnCondition(Repository *repository, OperationOfComparisonBetweenMedicines operationOfComparisonBetweenMedicines)
{
    for (int i = 0; i < getRepositoryLength(repository) - 1; ++i)
    {
        for (int j = i + 1; j < getRepositoryLength(repository); ++j)
        {
            Medicine *medicine1 = (Medicine *)getElementOnPosition(getDynamicArray(repository), i);
            Medicine *medicine2 = (Medicine *)getElementOnPosition(getDynamicArray(repository), j);
            if (medicine1 && medicine2 && operationOfComparisonBetweenMedicines(medicine2, medicine1) > 0)
                swapElementsOnDynamicArray(getDynamicArray(repository), i, j);
        }
    }
}

Medicine *getMedicineFromRepository(Repository *repository, int position)
{
    return (Medicine *)(getElementOnPosition(getDynamicArray(repository), position));
}

int checkIfMedicineIsInRepository(Repository *repository, Medicine *medicine)
{
    for (int i = 0; i < getRepositoryLength(repository); ++i)
    {
        Medicine *med = getMedicineFromRepository(repository, i);
        if (med && compareMedicines(med, medicine) == 1)
            return i;
    }
    return -1;
}

Repository *copyRepository(Repository *repository)
{
    Repository *newRepository = createRepository();
    int length = getRepositoryLength(repository);
    for (int i = 0; i < length; ++i)
    {
        Medicine *medicine = getMedicineFromRepository(repository, i);
        addMedicineToRepository(newRepository, copyMedicine(medicine));
    }
    newRepository->dynamicArray->length = length;
    return newRepository;
}

void setRepository(Repository *repository, Repository *newRepository)
{
    destroyRepository(repository);
    repository = copyRepository(newRepository);
}