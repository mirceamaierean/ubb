//
// Created by Mircea Maierean on 14.03.2023.
//
#pragma once
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

UI *createUI(Service *service) {
    UI *ui = (UI *)malloc(sizeof(UI));
    ui->service = service;
    return ui;
}

void destroyUI(UI *ui) {
    destroyService(ui->service);
    free(ui);
}

void printMenu(){
    printf("Welcome to the administrations of SMILES \U0001F603 Pharmacy. To perform an action, please enter the corresponding number: \n");
    printf("0. Exit the application \n");
    printf("1. Add a new medicine \n");
    printf("2. Delete a medicine \n");
    printf("3. Update a medicine \n");
    printf("4. List all available medicines, based on a string that YOU will enter \n");
    printf("5. List all medicines that have a quantity lower than a given number \n");
}


void addMedicineUI(UI *ui){
    char name[101];
    double concentration, price;
    int quantity;
    printf("Enter the name of the medicine: ");
    scanf(" %[^\n]", name);
    do {
        printf("Enter the concentration of the medicine. It must be between 0 and 100: ");
        scanf("%lf", &concentration);
        if (concentration < 0 || concentration > 100)
            printf("Invalid concentration \U0001F61E! Try again \n");
    }while(concentration < 0 || concentration > 100);
    printf("Enter the price of the medicine: ");
    scanf("%lf", &price);
    printf("Enter the quantity of the medicine: ");
    scanf("%d", &quantity);
    Medicine *medicine = createMedicine(name, concentration, quantity, price);
    if (addMedicineService(ui->service, medicine) == 1)
        printf("Medicine added successfully! \U0001F60A \n");
    else
    {
        printf("Medicine already exists, thus the quantity has been updated \n");
        destroyMedicine(medicine);
    }
}

void deleteMedicineUI(UI *ui){
    char name[101];
    double concentration;
    printf("Enter the name of the medicine you want to delete: ");
    scanf(" %[^\n]", name);
    printf("Enter the concentration of the medicine you want to delete: ");
    scanf("%lf", &concentration);
    Medicine *medicine = createMedicine(name, concentration, 0, 0);
    if (deleteMedicineService(ui->service, medicine) == 1)
        printf("Medicine deleted successfully! \U0001F60A \n");
    else
        printf("Medicine does not exist! \U0001F61E \n");
    destroyMedicine(medicine);
}

void updateMedicineUI(UI *ui){
    char nameBeforeUpdate[101], nameAfterUpdate[101];
    double concentrationBeforeUpdate, concentrationAfterUpdate, price;
    int quantity;
    printf("Enter the name of the medicine you want to update: ");
    scanf(" %[^\n]", nameBeforeUpdate);
    printf("Enter the concentration of the medicine you want to update: ");
    scanf("%lf", &concentrationBeforeUpdate);
    printf("Enter the new name of the medicine: ");
    scanf(" %[^\n]", nameAfterUpdate);
    printf("Enter the new concentration of the medicine: ");
    scanf("%lf", &concentrationAfterUpdate);
    printf("Enter the new price of the medicine: ");
    scanf("%lf", &price);
    printf("Enter the new quantity of the medicine: ");
    scanf("%d", &quantity);
    Medicine *medicineBeforeUpdate = createMedicine(nameBeforeUpdate, concentrationBeforeUpdate, 0, 0),
             *medicineAfterUpdate = createMedicine(nameAfterUpdate, concentrationAfterUpdate, quantity, price);
    if (updateMedicineService(ui->service, medicineBeforeUpdate, medicineAfterUpdate) == 1)
        printf("Medicine updated successfully! \U0001F60A \n");
    else
        printf("Medicine does not exist! \U0001F61E \n");
}

void listMedicinesUIBasedOnStringRequirement(UI *ui){
    int command = -1;
    OperationOfComparison operation = &medicineContainsString;
    while (command != 1 && command != 2){
        printf("Enter command in which you want to search\n "
               "1. Show the medicines that CONTAIN the given string \n "
               "2. Show the medicines that DO NOT CONTAIN the given string \n");
        printf("Your option is: ");
        scanf("%d", &command);
        switch (command) {
            case 1:
                operation = &medicineContainsString;
                break;
            case 2:
                operation = &medicineDoesNotContainString;
                break;
            default:
                printf("Invalid command! Please try again \U0001F61E \n");
        }
    }
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
    char stringToSearchFor[101];
    printf("Enter the string you want to search for. For displaying all the entities, just press enter: ");
    fgets(stringToSearchFor, 101, stdin);
    DynamicArray *medicines = getMedicineBasedOnFiltering(ui->service, stringToSearchFor, operation);
    if (medicines->length == 0)
    {
        printf("There are no medicines that satisfy your requirements! \U0001F60A \n");
        free(medicines->elements);
        free(medicines);
        return;
    }
    for (int i = 0; i < medicines->length; ++i) {
        char * medicineAsString = formatMedicineAsString(medicines->elements[i]);
        printf("%s \n", medicineAsString);
        free(medicineAsString);
    }
    destroyDynamicArray(medicines);
}

void listMedicinesThatAreInAShortSupply(UI *ui){
    int quantity;
    printf("Enter the quantity of medicines that you will be in a shorter supply than the quantity you will provide: ");
    scanf("%d", &quantity);
    int command = -1;
    OperationOfComparisonBetweenMedicines operation = &firstMedicineIsInAShorterSupplyThanSecondMedicine;
    while (command != 1 && command != 2){
        printf("In which way do you want the meds to be sorted? \n "
               "1. Increasing \n "
               "2. Decreasing \n");
        printf("Your option is: ");
        scanf("%d", &command);
        switch (command) {
            case 1:
                operation = &firstMedicineIsInAShorterSupplyThanSecondMedicine;
                break;
            case 2:
                operation = &firstMedicineIsInAGreaterSupplyThanSecondMedicine;
                break;
            default:
                printf("Invalid command! Please try again \U0001F61E \n");
        }
    }
    DynamicArray *medicines = getMedicineThatAreInAShortSupply(ui->service, quantity, operation);
    if (medicines->length == 0) {
        printf("There are no medicines that are in a shorter supply! \U0001F60A \n");
        return;
    }
    for (int i = 0; i < medicines->length; ++i) {
        char * medicineAsString = formatMedicineAsString(medicines->elements[i]);
        printf("%s \n", medicineAsString);
        free(medicineAsString);
    }
    destroyDynamicArray(medicines);
}

void startUI(UI *ui) {
    int command = -1;
    while (command != 0) {
        printMenu();
        printf("Enter command: ");
        scanf("%d", &command);
        switch (command) {
            case 0:
                printf("Thank you for using our application! \U0001F60A \n");
                break;
            case 1:
                addMedicineUI(ui);
                break;
            case 2:
                deleteMedicineUI(ui);
                break;
            case 3:
                updateMedicineUI(ui);
                break;
            case 4:
                listMedicinesUIBasedOnStringRequirement(ui);
                break;
            case 5:
                listMedicinesThatAreInAShortSupply(ui);
                break;
            default:
                printf("Invalid command! Please try again \U0001F61E \n");
        }
    }
}