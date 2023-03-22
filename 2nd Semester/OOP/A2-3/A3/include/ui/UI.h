#pragma once
#ifndef A23_914MAIEREANMIRCEA_UI_H
#define A23_914MAIEREANMIRCEA_UI_H
#endif // A23_914MAIEREANMIRCEA_UI_H
#include "../service/Service.h"

typedef struct
{
    Service *service;
} UI;

UI *createUI(Service *service);
Service *getService(UI *ui);
void destroyUI(UI *ui);
void startUI(UI *ui);
void addMedicineUI(UI *ui);
void deleteMedicineUI(UI *ui);
void updateMedicineUI(UI *ui);
void undoMedicineUI(UI *ui);
void redoMedicineUI(UI *ui);
void listMedicinesUIBasedOnStringRequirement(UI *ui);
void listMedicinesThatAreInAShortSupply(UI *ui);
