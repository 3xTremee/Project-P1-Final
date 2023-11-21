#include <stdlib.h>
#include "cJSON.h"
#include <stdio.h>
#include "dosage.h"

#define LIQUID_DOSAGE 2
#define WEIGHT_BASED_DOSAGE 1

// Function to calculate the dosage of a medicine
double dosageCalculator() {
    double liquidDose, *dosage = NULL, concentration, patientWeight, maxDosage;
    int unitChoice, unitChoice2, unitChoice3;

    dosage = (double*)malloc(sizeof(double));

    do {
        // Takes input choice 1/2 for to choose either weight-based dosage or liquid dosage
        printf("Press 1 for weight-based dosage calculator, press 2 for liquid dosage calculator.\n>");
        scanf("%d", &unitChoice2);

        // Validate unit choice
        if (unitChoice2 != WEIGHT_BASED_DOSAGE && unitChoice2 != LIQUID_DOSAGE) {
            printf("Invalid choice. Exiting...\n");
            free(dosage);
            return 1;
        }
    } while (unitChoice2 != WEIGHT_BASED_DOSAGE && unitChoice2 != LIQUID_DOSAGE);

    // Take input for liquid dosage if selected
    if (unitChoice2 == LIQUID_DOSAGE) {
        printf("Select the unit of measurement for the liquid dosage.\n");
        printf("1 for ml/L, 2 for mg/L, 3 for mcg/L.\n>");
        scanf("%d", &unitChoice);

        printf("Enter the medicine concentration.\n>");
        scanf("%lf", &concentration);

        // Dosage here is a pointer
        printf("Enter the dosage.\n>");
        scanf("%lf", dosage);

        // Calculate dosage and print based on selection
        switch (unitChoice) {
            case 1:
                liquidDose = *dosage / concentration;
                printf("The liquid dosage is: %.2lf ml.\n", liquidDose);
                break;
            case 2:
                liquidDose = (*dosage / concentration) * 1000;
                printf("The liquid dosage is: %.2lf ml.\n", liquidDose);
                break;
            case 3:
                liquidDose = (*dosage / concentration) * 1000000;
                printf("The liquid dosage is: %.2lf ml.\n", liquidDose);
                break;
            default:
                printf("Invalid unit choice. Exiting...\n");
                free(dosage);
                return 1;
        }
    }
        // Take input for weight-based dosage if selected
    else if (unitChoice2 == WEIGHT_BASED_DOSAGE) {
        printf("Enter the patient's weight in kilograms\n>");
        scanf("%lf", &patientWeight);

        printf("Input medicine dosage per kg\n>");
        scanf("%lf", dosage);

        printf("Choose the unit (1 for g, 2 for mg, 3 for mcg)\n>");
        scanf("%d", &unitChoice3);

        printf("Enter the maximum allowable dosage\n>");
        scanf("%lf", &maxDosage);

        // Validate maximum dosage
        while (*dosage > maxDosage) {
            printf("The dosage is too high, please enter a new dosage.\n>");
            scanf("%lf", dosage);
        }

        // Calculate dosage based on unit choice
        if (*dosage < maxDosage) {
            switch (unitChoice3) {
                case 1:
                    *dosage *= patientWeight;
                    printf("The calculated dosage is: %.2lf g.\n", *dosage);
                    break;
                case 2:
                    *dosage *= patientWeight * 1000;
                    printf("The calculated dosage is: %.2lf mg.\n", *dosage);
                    break;
                case 3:
                    *dosage *= patientWeight * 1000000;
                    printf("The calculated dosage is: %.2lf mcg.\n", *dosage);
                    break;
                default:
                    printf("Invalid unit choice. Exiting...\n");
                    free(dosage);
                    return 1;
            }
        }
    }
    // Free allocated dosage memory
    free(dosage);
    return 0;
}