#include "patient information.h"
#include "login.h"
#include "cpr.h"
#include "dosage.h"
#include "timestamp.h"

void print_patient(const char *cpr_to_find) {
    // This code attempts to open the file "users.json" for reading.
    // If it fails to open the file (e.g., due to a file not found), it prints an error message and returns from the function.
    FILE *fp = fopen("users.json", "r");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    // Move the file pointer to the end of the file
    fseek(fp, 0, SEEK_END);

    // Get the size of the file
    long file_size = ftell(fp);

    // Move the file pointer back to the beginning of the file
    fseek(fp, 0, SEEK_SET);

    // Dynamically allocate the buffer based on the file size
    char *buffer = (char *) malloc(file_size + 1);
    if (buffer == NULL) {
        printf("Error: Unable to allocate memory.\n");
        fclose(fp);
        return;
    }

    // Read the contents of the file into the buffer
    size_t len = fread(buffer, 1, file_size, fp);
    buffer[len] = '\0'; // Null-terminate the buffer
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

                //int which is used as a counter for the amount of medication that a patient can be given
                int medicineCounter = 0;
                //If the medicine is not NULL, the counter is increased by 1

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
                    medicineCounter++;
                }

                if (cJSON_IsString(dosage1) && (dosage1->valuestring != NULL)) {
                    printf("Dosage1: %s\n", dosage1->valuestring);
                }

                if (cJSON_IsString(medicine2) && (medicine2->valuestring != NULL)) {
                    printf("Medicine2: %s\n", medicine2->valuestring);
                    medicineCounter++;
                }

                if (cJSON_IsString(dosage2) && (dosage2->valuestring != NULL)) {
                    printf("Dosage2: %s\n", dosage2->valuestring);
                }

                if (cJSON_IsString(medicine3) && (medicine3->valuestring != NULL)) {
                    printf("Medicine3: %s\n", medicine3->valuestring);
                    medicineCounter++;
                }

                if (cJSON_IsString(dosage3) && (dosage3->valuestring != NULL)) {
                    printf("Dosage3: %s\n", dosage3->valuestring);
                }

                if (cJSON_IsString(medicine4) && (medicine4->valuestring != NULL)) {
                    printf("Medicine4: %s\n", medicine4->valuestring);
                    medicineCounter++;
                }

                if (cJSON_IsString(dosage4) && (dosage4->valuestring != NULL)) {
                    printf("Dosage4: %s\n", dosage4->valuestring);
                }

                if (cJSON_IsString(medicine5) && (medicine5->valuestring != NULL)) {
                    printf("Medicine5: %s\n", medicine5->valuestring);
                    medicineCounter++;
                }

                if (cJSON_IsString(dosage5) && (dosage5->valuestring != NULL)) {
                    printf("Dosage5: %s\n", dosage5->valuestring);
                }

                if (cJSON_IsString(medicine6) && (medicine6->valuestring != NULL)) {
                    printf("Medicine6: %s\n", medicine6->valuestring);
                    medicineCounter++;
                }

                if (cJSON_IsString(dosage6) && (dosage6->valuestring != NULL)) {
                    printf("Dosage6: %s\n", dosage6->valuestring);
                }

                if (cJSON_IsString(medicine7) && (medicine7->valuestring != NULL)) {
                    printf("Medicine7: %s\n", medicine7->valuestring);
                    medicineCounter++;
                }

                if (cJSON_IsString(dosage7) && (dosage7->valuestring != NULL)) {
                    printf("Dosage7: %s\n", dosage7->valuestring);
                }

                if (cJSON_IsString(medicine8) && (medicine8->valuestring != NULL)) {
                    printf("Medicine8: %s\n", medicine8->valuestring);
                    medicineCounter++;
                }

                if (cJSON_IsString(dosage8) && (dosage8->valuestring != NULL)) {
                    printf("Dosage8: %s\n", dosage8->valuestring);
                }

                printf("Do you need help calculating the dosage?\n");
                printf("Type 1 for yes or 2 for no\n>");
                int help = 0;
                scanf("%d", &help);
                if (help == 1) {
                    dosageCalculator();
                }


                int valg = 0;
                printf("How many different medications have you administered?\n");
                scanf("%d", &valg);
                if(medicineCounter < valg){
                    printf("You have entered a number that is higher than the amount of medicine the patient can be given\n");
                    printf("Please enter a number between 0 and %d\n", medicineCounter);
                    scanf("%d", &valg);

                }
                //How to know how many medicine rows there are in the json file?

                //For loop that runs the amount of times the user has entered in the previous scanf
                for (int j = 0; j < valg; ++j) {
                    char medicine[100];
                    printf("Please enter the medicine you have administered\n>");
                    scanf("%s", medicine);
                    medicine[0] = toupper(medicine[0]);
                    addTimestampToField(patient, medicine);

                    FILE *outputFile = fopen("users.json", "w");

                    char *updatedJsonText = cJSON_Print(json);
                    fprintf(outputFile, "%s", updatedJsonText);
                    fclose(outputFile);
                    free(updatedJsonText);

                }
                cJSON_Delete(patient);
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
    for (int t = 0; t < 2; t++) {
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
        switch (valg) {
            case 1:
                //Makes free lines between the previous and the current patient information.
                for (int t = 0; t < 8; t++) {
                    printf("\n");
                }
                EnterCPR();
                break;
                //if 2 moves user to log-in screen and forward to EnterCPR when user has logged in again succesfully
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
    } while (valg != 1 && valg != 2);

    // Delete the JSON object
    cJSON_Delete(json);

    //Free the memory for the buffer
    free(buffer);
}