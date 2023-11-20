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
    char buffer[3048];
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


            //The atof funktion converts the array of chars (String) into a float
            if (cJSON_IsNumber(cpr) && (cpr->valuedouble == atof(cpr_to_find))) {
                cJSON *name = cJSON_GetObjectItemCaseSensitive(patient, "Name");
                cJSON *age = cJSON_GetObjectItemCaseSensitive(patient, "Age");
                cJSON *gender = cJSON_GetObjectItemCaseSensitive(patient, "Gender");
                cJSON *diagnosis = cJSON_GetObjectItemCaseSensitive(patient, "Diagnosis");
                cJSON *medicine1 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine1");
                cJSON *dosage1 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage1");
                cJSON *medicine2 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine2");
                cJSON *dosage2 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage2");
                cJSON *medicine3 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine3");
                cJSON *dosage3 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage3");
                cJSON *medicine4 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine4");
                cJSON *dosage4 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage4");
                cJSON *medicine5 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine5");
                cJSON *dosage5 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage5");
                cJSON *medicine6 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine6");
                cJSON *dosage6 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage6");
                cJSON *medicine7 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine7");
                cJSON *dosage7 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage7");
                cJSON *medicine8 = cJSON_GetObjectItemCaseSensitive(patient, "Medicine8");
                cJSON *dosage8 = cJSON_GetObjectItemCaseSensitive(patient, "Dosage8");

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

                if (cJSON_IsString(diagnosis) && (diagnosis->valuestring != NULL)) {
                    printf("Diagnosis: %s\n", diagnosis->valuestring);
                }

                if (cJSON_IsString(medicine1) && (medicine1->valuestring != NULL)) {
                    printf("Medicine1: %s\n", medicine1->valuestring);
                }

                if (cJSON_IsString(dosage1) && (dosage1->valuestring != NULL)) {
                    printf("Dosage1: %s\n", dosage1->valuestring);
                }

                if (cJSON_IsString(medicine2) && (medicine2->valuestring != NULL)) {
                    printf("Medicine2: %s\n", medicine2->valuestring);
                }

                if (cJSON_IsString(dosage2) && (dosage2->valuestring != NULL)) {
                    printf("Dosage2: %s\n", dosage2->valuestring);
                }

                if (cJSON_IsString(medicine3) && (medicine3->valuestring != NULL)) {
                    printf("Medicine3: %s\n", medicine3->valuestring);
                }

                if (cJSON_IsString(dosage3) && (dosage3->valuestring != NULL)) {
                    printf("Dosage3: %s\n", dosage3->valuestring);
                }

                if (cJSON_IsString(medicine4) && (medicine4->valuestring != NULL)) {
                    printf("Medicine4: %s\n", medicine4->valuestring);
                }

                if (cJSON_IsString(dosage4) && (dosage4->valuestring != NULL)) {
                    printf("Dosage4: %s\n", dosage4->valuestring);
                }

                if (cJSON_IsString(medicine5) && (medicine5->valuestring != NULL)) {
                    printf("Medicine5: %s\n", medicine5->valuestring);
                }

                if (cJSON_IsString(dosage5) && (dosage5->valuestring != NULL)) {
                    printf("Dosage5: %s\n", dosage5->valuestring);
                }

                if (cJSON_IsString(medicine6) && (medicine6->valuestring != NULL)) {
                    printf("Medicine6: %s\n", medicine6->valuestring);
                }

                if (cJSON_IsString(dosage6) && (dosage6->valuestring != NULL)) {
                    printf("Dosage6: %s\n", dosage6->valuestring);
                }

                if (cJSON_IsString(medicine7) && (medicine7->valuestring != NULL)) {
                    printf("Medicine7: %s\n", medicine7->valuestring);
                }

                if (cJSON_IsString(dosage7) && (dosage7->valuestring != NULL)) {
                    printf("Dosage7: %s\n", dosage7->valuestring);
                }

                if (cJSON_IsString(medicine8) && (medicine8->valuestring != NULL)) {
                    printf("Medicine8: %s\n", medicine8->valuestring);
                }

                if (cJSON_IsString(dosage8) && (dosage8->valuestring != NULL)) {
                    printf("Dosage8: %s\n", dosage8->valuestring);
                }
                break;  // Exit the loop once the desired "CPR" is found
            }

        }
        //If the CPR number does not have information to print, the program prompts the user to reenter CPR.number
        // so we can insert an error message and run EnterCPR again
        if (HasPrinted == 0) {
            printf("CPR-number not in system\n");
            EnterCPR();
        }
        
    } else {
        //If no "Users" is found in the JSON file, prints error message.
        printf("Error: 'Users' is not an array in the JSON.\n");
    }

    //Makes a space between the patients printed info and the printf below.
    for(int t = 0; t < 2; t++) {
        printf("\n");
    }
    int valg;
    printf("Do you want to find a new person or log out?\nType 1 for new person or 2 for log out\n>");

    do {
        //Scans the user input based on the previous printed message and acts on the input in the switch case,
        // either continuing to the next patient 1 or log out 2
        scanf(" %d", &valg);
        char CPRnr[11];

        //Switch case, if input is 1, it runs EnterCPR
        switch(valg) {
            case 1:
                //Makes free lines between the previous and the current patient information.
                for(int t = 0; t < 8; t++) {
                    printf("\n");
                }
                EnterCPR(CPRnr);
                break;
        //, if 2 moves user to log-in screen and forward to EnterCPR when user has logged in again succesfully
            case 2:
                printf("You are being logged out \n");
                login();
                EnterCPR();
                break;
        //If user types something that is not 1 or 2, runs an error message
            default:
                printf("You have not chosen a valid option. Please choose 1 or 2.\n");
        }
        //Because it is in a do while function, if it was not broken (runs case 1 or 2)
        // , the while is still true and runs again
    } while(valg != 1 && valg != 2);

    // Delete the JSON object
    cJSON_Delete(json);
}