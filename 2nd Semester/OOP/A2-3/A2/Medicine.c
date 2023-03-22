//
// Created by Mircea Măierean on 14.03.2023.
//
#pragma once
#include "Medicine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Medicine *createMedicine(char *name, double concentration, int quantity, double price) {
    Medicine *medicine = (Medicine *)malloc(sizeof(Medicine));
    medicine->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(medicine->name, name);
    medicine->concentration = concentration;
    medicine->quantity = quantity;
    medicine->price = price;
    return medicine;
}

int medicineContainsString(Medicine* medicine, char *string) {
    return (strstr(medicine->name, string) != NULL);
}

int medicineDoesNotContainString(Medicine* medicine, char *string) {
    return !(medicineContainsString(medicine, string));
}

void destroyMedicine(Medicine *medicine) {
    free(medicine->name);
    free(medicine);
}

char *formatMedicineAsString(Medicine *medicine) {
    char *string = (char *)malloc(sizeof(char) * 500);
    sprintf(string, "%s %lf %d %lf", medicine->name, medicine->concentration, medicine->quantity, medicine->price);
    return string;
}

int compareMedicines(Medicine *medicine1, Medicine *medicine2) {
    if (strcmp(medicine1->name, medicine2->name) == 0 && medicine1->concentration == medicine2->concentration)
        return 1;
    return 0;
}

int firstMedicineHasNameSmallerThanSecondMedicine(Medicine *medicine1, Medicine *medicine2) {
    return (strcmp(medicine1->name, medicine2->name) < 0);
}

int firstMedicineIsInAShorterSupplyThanSecondMedicine(Medicine *medicine1, Medicine *medicine2) {
    return (medicine1->quantity < medicine2->quantity);
}

int firstMedicineIsInAGreaterSupplyThanSecondMedicine(Medicine *medicine1, Medicine *medicine2) {
    return (medicine1->quantity > medicine2->quantity);
}
