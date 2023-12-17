#include "../../include/ui/UI.h"
#include <stdio.h>
#include <stdlib.h>

UI *createUI(Service *service)
{
    UI *ui = (UI *)malloc(sizeof(UI));
    ui->service = service;
    return ui;
}

Service *getService(UI *ui)
{
    return ui->service;
}

void destroyUI(UI *ui)
{
    destroyService(getService(ui));
    free(ui);
}

void printMenu()
{
    printf("Welcome to the administrations of SMILES \U0001F603 Pharmacy. To perform an action, please enter the corresponding number: \n");
    printf("0. Exit the application \n");
    printf("1. Add a new medicine \n");
    printf("2. Delete a medicine \n");
    printf("3. Update a medicine \n");
    printf("4. List all available medicines, based on a string that YOU will enter \n");
    printf("5. List all medicines that have a quantity lower than a given number \n");
    printf("6. Undo last performed operation \n");
    printf("7. Redo last available operation \n");
}

void addMedicineUI(UI *ui)
{
    char name[1001];
    double concentration, price;
    int quantity;

    printf("Enter the name of the medicine \U0001F48A: ");
    scanf(" %[^\n]", name);

    do
    {
        printf("Enter the concentration of the medicine. It must be between 0 and 100: ");
        scanf("%lf", &concentration);
        if (concentration < 0 || concentration > 100)
            printf("Invalid concentration \U0001F61E! Try again \n");
    } while (concentration < 0 || concentration > 100);

    printf("Enter the price of the medicine. It must be a positive integer (No medication is given as a gift \U0001F4B7!): ");
    scanf("%lf", &price);

    printf("Enter the quantity of the medicine. It must be a positive integer: ");
    scanf("%d", &quantity);

    Medicine *medicine = createMedicine(name, concentration, quantity, price);
    if (addMedicineService(getService(ui), medicine) == 1)
        printf("Medicine added successfully! \U00002705 \n");
    else
    {
        printf("Medicine already exists, thus the quantity has been updated \U0001F504 \n");
        destroyMedicine(medicine);
    }
}

void deleteMedicineUI(UI *ui)
{
    char name[101];
    double concentration;
    printf("Enter the name of the medicine you want to delete \U0001F48A: ");
    scanf(" %[^\n]", name);

    do
    {
        printf("Enter the concentration of the medicine. It must be between 0 and 100: ");
        scanf("%lf", &concentration);
        if (concentration < 0 || concentration > 100)
            printf("Invalid concentration \U0001F61E! Try again \n");
    } while (concentration < 0 || concentration > 100);

    Medicine *medicine = createMedicine(name, concentration, 0, 0);
    if (deleteMedicineService(getService(ui), medicine) == 1)
        printf("Medicine deleted successfully! \U00002705 \n");
    else
        printf("Medicine does not exist! \U0000274C \n");
    destroyMedicine(medicine);
}

void updateMedicineUI(UI *ui)
{
    char nameBeforeUpdate[101], nameAfterUpdate[101];
    double concentrationBeforeUpdate, concentrationAfterUpdate, price;
    int quantity;

    printf("Enter the name of the medicine you want to update \U0001F48A: ");
    scanf(" %[^\n]", nameBeforeUpdate);

    do
    {
        printf("Enter the concentration of the medicine. It must be between 0 and 100: ");
        scanf("%lf", &concentrationBeforeUpdate);
        if (concentrationBeforeUpdate < 0 || concentrationBeforeUpdate > 100)
            printf("Invalid concentration \U0001F61E! Try again \n");
    } while (concentrationBeforeUpdate < 0 || concentrationBeforeUpdate > 100);

    printf("Enter the new name of the medicine: ");
    scanf(" %[^\n]", nameAfterUpdate);
    do
    {
        printf("Enter the concentration of the medicine. It must be between 0 and 100: ");
        scanf("%lf", &concentrationAfterUpdate);
        if (concentrationAfterUpdate < 0 || concentrationAfterUpdate > 100)
            printf("Invalid concentration \U0001F61E! Try again \n");
    } while (concentrationAfterUpdate < 0 || concentrationAfterUpdate > 100);

    printf("Enter the new price of the medicine \U0001F4B7: ");
    scanf("%lf", &price);
    printf("Enter the new quantity of the medicine: ");
    scanf("%d", &quantity);
    Medicine *medicineBeforeUpdate = createMedicine(nameBeforeUpdate, concentrationBeforeUpdate, 0, 0),
             *medicineAfterUpdate = createMedicine(nameAfterUpdate, concentrationAfterUpdate, quantity, price);
    if (updateMedicineService(getService(ui), medicineBeforeUpdate, medicineAfterUpdate) == 1)
        printf("Medicine updated successfully! \U00002705 \n");
    else
        printf("Medicine does not exist! \U0000274C \n");
}

void undoMedicineUI(UI *ui)
{
    Service *service = getService(ui);
    UndoRedoRepository *undoRedoRepository = getUndoRedoRepository(service);
    DynamicArray *undoOperations = getUndoOperations(undoRedoRepository), *redoOperations = getRedoOperations(undoRedoRepository);
    if (undoRedoService(service, undoOperations, redoOperations))
        printf("Undo performed successfully! \U00002705 \n");
    else
        printf("No more undos available! \U0001F6D1 \n");
}

void redoMedicineUI(UI *ui)
{
    Service *service = getService(ui);
    UndoRedoRepository *undoRedoRepository = getUndoRedoRepository(service);
    DynamicArray *undoOperations = getUndoOperations(undoRedoRepository), *redoOperations = getRedoOperations(undoRedoRepository);
    if (undoRedoService(service, redoOperations, undoOperations))
        printf("Redo performed successfully! \U00002705 \n");
    else
        printf("No more redos available! \U0001F6D1 \n");
}

void listMedicinesUIBasedOnStringRequirement(UI *ui)
{
    int command = -1;
    OperationOfComparison operation = &medicineContainsString;
    while (command != 1 && command != 2)
    {
        printf("Enter command in which you want to search\n "
               "1. Show the medicines that CONTAIN the given string \n "
               "2. Show the medicines that DO NOT CONTAIN the given string \n");
        printf("Your option is: ");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            operation = &medicineContainsString;
            break;
        case 2:
            operation = &medicineDoesNotContainString;
            break;
        default:
            printf("Invalid command! Please try again \U0000274C \n");
        }
    }
    int character;
    while ((character = getchar()) != '\n' && character != EOF)
        ;
    char stringToSearchFor[101];
    printf("Enter the string you want to search for. For displaying all the entities, just press enter: ");
    fgets(stringToSearchFor, 101, stdin);
    DynamicArray *medicines = getMedicineBasedOnFiltering(getService(ui), stringToSearchFor, operation);
    if (getLengthOfDynamicArray(medicines) == 0)
    {
        printf("There are no medicines that satisfy your requirements! \U0001FAB9 \n");
        free(getElements(medicines));
        free(medicines);
        return;
    }
    for (int i = 0; i < getLengthOfDynamicArray(medicines); ++i)
    {
        char *medicineAsString = formatMedicineAsString((Medicine *)getElementOnPosition(medicines, i));
        printf("%s \n", medicineAsString);
        free(medicineAsString);
    }
    destroyDynamicArray(medicines);
}

void listMedicinesThatAreInAShortSupply(UI *ui)
{
    int quantity;
    printf("Enter the quantity after which the query will be performed: ");
    scanf("%d", &quantity);
    int command = -1;
    OperationOfComparisonBetweenMedicines operation = &firstMedicineIsInAShorterSupplyThanSecondMedicine;
    while (command != 1 && command != 2)
    {
        printf("In which way do you want the meds to be sorted? \n "
               "1. Increasing \U0001F4C8 \n "
               "2. Decreasing \U0001F4C9 \n");
        printf("Your option is: ");
        scanf("%d", &command);
        switch (command)
        {
        case 1:
            operation = &firstMedicineIsInAShorterSupplyThanSecondMedicine;
            break;
        case 2:
            operation = &firstMedicineIsInAGreaterSupplyThanSecondMedicine;
            break;
        default:
            printf("Invalid command! Please try again \U0000274C \n");
        }
    }
    DynamicArray *medicines = getMedicineThatAreInAShortSupply(getService(ui), quantity, operation);
    if (getLengthOfDynamicArray(medicines) == 0)
    {
        destroyDynamicArray(medicines);
        printf("There are no medicines that are in a shorter supply! \U0001FAB9 \n");
        return;
    }
    for (int i = 0; i < getLengthOfDynamicArray(medicines); ++i)
    {
        char *medicineAsString = formatMedicineAsString((Medicine *)getElementOnPosition(medicines, i));
        printf("%s \n", medicineAsString);
        free(medicineAsString);
    }
    destroyDynamicArray(medicines);
}

void startUI(UI *ui)
{
    generateRandomEntries(getService(ui), 15);
    int command = -1;
    while (command != 0)
    {
        printMenu();
        printf("Number of undo operations available: %d, Number of redo operations available: %d \n", getLengthOfDynamicArray(getUndoOperations(getUndoRedoRepository(getService(ui)))), getLengthOfDynamicArray(getRedoOperations(getUndoRedoRepository(getService(ui)))));
        printf("Enter command: ");
        scanf("%d", &command);
        switch (command)
        {
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
        case 6:
            undoMedicineUI(ui);
            break;
        case 7:
            redoMedicineUI(ui);
            break;
        default:
            printf("Invalid command! Please try again \U0001F61E \n");
        }
    }
}