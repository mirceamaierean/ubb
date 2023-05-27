#include "../../include/domain/Medicine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Medicine *createMedicine(char *name, double concentration, int quantity, double price)
{
    Medicine *medicine = (Medicine *)malloc(sizeof(Medicine));
    medicine->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(medicine->name, name);
    medicine->concentration = concentration;
    medicine->quantity = quantity;
    medicine->price = price;
    return medicine;
}

Medicine *copyMedicine(Medicine *medicine)
{
    return createMedicine(getNameOfMedicine(medicine), getConcentrationOfMedicine(medicine), getQuantityOfMedicine(medicine), getPriceOfMedicine(medicine));
}

char *getNameOfMedicine(Medicine *medicine)
{
    return medicine->name;
}

int getQuantityOfMedicine(Medicine *medicine)
{
    return medicine->quantity;
}

double getConcentrationOfMedicine(Medicine *medicine)
{
    return medicine->concentration;
}

double getPriceOfMedicine(Medicine *medicine)
{
    return medicine->price;
}

int medicineContainsString(Medicine *medicine, char *string)
{
    return (strstr(getNameOfMedicine(medicine), string) != NULL);
}

int medicineDoesNotContainString(Medicine *medicine, char *string)
{
    return !(medicineContainsString(medicine, string));
}

void destroyMedicine(Medicine *medicine)
{
    if (medicine)
    {
        if (getNameOfMedicine(medicine))
            free(getNameOfMedicine(medicine));
        free(medicine);
    }
}

char *formatMedicineAsString(Medicine *medicine)
{
    char *string = (char *)malloc(sizeof(char) * 500);
    sprintf(string, "%s %lf %d %lf", getNameOfMedicine(medicine), getConcentrationOfMedicine(medicine), getQuantityOfMedicine(medicine), getPriceOfMedicine(medicine));
    return string;
}

int compareMedicines(Medicine *medicine1, Medicine *medicine2)
{
    if (strcmp(getNameOfMedicine(medicine1), getNameOfMedicine(medicine2)) == 0 && getConcentrationOfMedicine(medicine1) == getConcentrationOfMedicine(medicine2))
        return 1;
    return 0;
}

int firstMedicineHasNameSmallerThanSecondMedicine(Medicine *medicine1, Medicine *medicine2)
{
    return (strcmp(getNameOfMedicine(medicine1), getNameOfMedicine(medicine2)) < 0);
}

int firstMedicineIsInAShorterSupplyThanSecondMedicine(Medicine *medicine1, Medicine *medicine2)
{
    return (getQuantityOfMedicine(medicine1) < getQuantityOfMedicine(medicine2));
}

int firstMedicineIsInAGreaterSupplyThanSecondMedicine(Medicine *medicine1, Medicine *medicine2)
{
    return (getQuantityOfMedicine(medicine1) > getQuantityOfMedicine(medicine2));
}
