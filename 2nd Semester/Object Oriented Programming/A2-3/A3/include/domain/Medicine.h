#ifndef A23_914MAIEREANMIRCEA_MEDICINE_H
#define A23_914MAIEREANMIRCEA_MEDICINE_H
#endif // A23_914MAIEREANMIRCEA_MEDICINE_H
#pragma once

typedef struct
{
    char *name;
    int quantity;
    double concentration, price;
} Medicine;

typedef int (*OperationOfComparison)(Medicine *, char *);
typedef int (*OperationOfComparisonBetweenMedicines)(Medicine *, Medicine *);

Medicine *createMedicine(char *, double, int, double);
Medicine *copyMedicine(Medicine *);
void destroyMedicine(Medicine *);
char *formatMedicineAsString(Medicine *);
int compareMedicines(Medicine *, Medicine *);
int medicineContainsString(Medicine *, char *);
int medicineDoesNotContainString(Medicine *, char *);
int firstMedicineHasNameSmallerThanSecondMedicine(Medicine *, Medicine *);
int firstMedicineIsInAShorterSupplyThanSecondMedicine(Medicine *, Medicine *);
int firstMedicineIsInAGreaterSupplyThanSecondMedicine(Medicine *, Medicine *);
char *getNameOfMedicine(Medicine *);
int getQuantityOfMedicine(Medicine *);
double getConcentrationOfMedicine(Medicine *);
double getPriceOfMedicine(Medicine *);
