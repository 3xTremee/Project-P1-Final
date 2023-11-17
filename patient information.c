#include "patient information.h"
#include "login.h"
#include "cpr.h"

void print_patient(const char *cpr_to_find) {
    // This code attempts to open the file "users.json" for reading.
    // If it fails to open the file (e.g., due to a file not found), it prints an error message and returns from the function.
    FILE *fp = fopen("users.json", "r");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    // This code reads the contents of the opened file into a character buffer named buffer.
    char buffer[2048];
    int len = fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);

    // This part of the code extracts the "Users" array from the parsed JSON data.
    // If "Users" is an array, it proceeds to iterate through its elements using a for loop.
    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return;
    }

    // Find the JSON object with the specified "CPR"
    cJSON *users = cJSON_GetObjectItemCaseSensitive(json, "Users");
    if (cJSON_IsArray(users)) {
        bool HasPrinted = 0;
        for (int i = 0; i < cJSON_GetArraySize(users); i++) {
            cJSON *patient = cJSON_GetArrayItem(users, i);
            cJSON *cpr = cJSON_GetObjectItemCaseSensitive(patient, "CPR");


            //atof funktionen converter vores array of chars (String) til en float
            if (cJSON_IsNumber(cpr) && (cpr->valuedouble == atof(cpr_to_find))) {
                cJSON *name = cJSON_GetObjectItemCaseSensitive(patient, "Name");
                cJSON *age = cJSON_GetObjectItemCaseSensitive(patient, "Age");
                cJSON *gender = cJSON_GetObjectItemCaseSensitive(patient, "Gender");
                cJSON *diagnosis1 = cJSON_GetObjectItemCaseSensitive(patient, "Diagnosis1");
                cJSON *medicine1 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine1");
                cJSON *dosage1 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage1");
                cJSON *diagnosis2 = cJSON_GetObjectItemCaseSensitive(patient, "Diagnosis2");
                cJSON *medicine2 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine2");
                cJSON *dosage2 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage2");

                if (cJSON_IsString(name) && (name->valuestring != NULL)) {
                    printf("Name: %s\n", name->valuestring);
                    //If the CPR number has an assosiated name (as in it has information) the program prints data
                    // and sets the bool to TRUE to reflect that
                    HasPrinted = 1;
                }

                if (cJSON_IsNumber(age)) {
                    printf("Age: %d\n", age->valueint);
                }

                if (cJSON_IsString(gender) && (gender->valuestring != NULL)) {
                    printf("Gender: %s\n", gender->valuestring);
                }

                if (cJSON_IsString(diagnosis1) && (diagnosis1->valuestring != NULL)) {
                    printf("Diagnosis1: %s\n", diagnosis1->valuestring);
                }

                if (cJSON_IsString(medicine1) && (medicine1->valuestring != NULL)) {
                    printf("Medicine1: %s\n", medicine1->valuestring);
                }

                if (cJSON_IsString(dosage1) && (dosage1->valuestring != NULL)) {
                    printf("Dosage1: %s\n", dosage1->valuestring);
                }

                if (cJSON_IsString(diagnosis2) && (diagnosis2->valuestring != NULL)) {
                    printf("Diagnosis2: %s\n", diagnosis2->valuestring);
                }

                if (cJSON_IsString(medicine2) && (medicine2->valuestring != NULL)) {
                    printf("Medicine2: %s\n", medicine2->valuestring);
                }

                if (cJSON_IsString(dosage2) && (dosage2->valuestring != NULL)) {
                    printf("Dosage2: %s\n", dosage2->valuestring);
                }
                break;  // Exit the loop once the desired "CPR" is found
            }

        }
        //If the CPR number does not have information to print, the program prompts the user to reenter CPR.number
        if (HasPrinted == 0) {
            //If the loop has not been broken that means that the CPR number is not in the json file
            // so we can insert an error message and run EnterCPR again
            printf("CPR-number not in system\n");
            EnterCPR();
        }
    } else {
        //Hvis der ikke er en "Users" i JSON filen printer den det her.
        printf("Error: 'Users' is not an array in the JSON.\n");
    }

    char valg;
    printf("Do you want to find a new person or log out?\nType 'Y' for yes or 'N' for log out\n>");

    do {
        //Kode som tjekker om valg er Y eller N og derefter kører switch casen.
        scanf(" %c", &valg);
        valg = toupper(valg);
        char CPRnr[11];

        //Switch case på valg fra tidligere. Hvis Y spørger den om CPR, ellers N.
        switch(valg) {
            case 'Y':
                EnterCPR(CPRnr);
                break;
            case 'N':
                printf("Du bliver nu logget ud \n");
                login();
                break;
            default:
                printf("Du har hverken valgt ja eller nej. Prøv igen, men vælg 'Y' eller 'N'.\n");
        }
    } while(valg != 'Y' && valg != 'N');

    // Delete the JSON object
    cJSON_Delete(json);
}