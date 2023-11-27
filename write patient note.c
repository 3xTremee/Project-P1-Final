#include "write patient note.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "cJSON.h"

char *getTimestamp();           //Returns time in 'Year-Month-Day Hour:Min:Sec' format

//logic:
/*
>open and parse file
>go through JSON to check if the CPR number is in it already (dont want to have 'empty' objects for patients w/o notes
>>return 'patient' (if in system, otherwise NULL?)
>does one of two operations based on the return, [==NULL]: create new object with the item note, [!=NULL]: adds an item to exising object
*/

void write_note(){
    char PCPR[11] = "1511991234";
    double PatientCPR = atof(PCPR);

    // open the JSON file
    // open the JSON file
    FILE *fp = fopen("patient_notes.json", "r");
    if (fp == NULL) {
        printf("Error: Unable to open read file.\n");
        return;
    }

    // read the file contents into a string
    char buffer[1024];
    int len = fread(buffer, 1, sizeof(buffer), fp);
    fclose(fp);

    // parse the JSON data
    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return;
    }


    int patient_object;
    bool patient_in_system = 0;

    //To check if the patient is registered in the notes system, check if the given CPR can be read in the file
    cJSON *users = cJSON_GetObjectItemCaseSensitive(json, "Patients");
    if (cJSON_IsArray(users)) {
        for (int i = 0; i < cJSON_GetArraySize(users); i++) {
            cJSON *patient = cJSON_GetArrayItem(users, i);
            cJSON *cpr = cJSON_GetObjectItemCaseSensitive(patient, "CPR");

            //
            if (cJSON_IsNumber(cpr) && (cpr->valuedouble == PatientCPR)){

                patient_in_system = 1;
                patient_object = i;
                break;
            }
        }
    } else{
        printf("Error: 'Patients' is not an array in the JSON.\n");
    }




    char PatientNote[100];
    printf("Please type error or note:\n");
    //To allow the user to write sentences the program scans for %[^\n] which means that it scans for input until it records 'Enter'
    scanf(" %[^\n]", PatientNote);

    //Get timestamp (using top-down to make write_note() clearer)
    char *timestamp = getTimestamp();




    if (patient_in_system == 0) {           //have to be fixed to add object to array
        //Creates new object to write in
        cJSON *NewPatient = cJSON_CreateObject();
        //Writes information to the object
        cJSON_AddNumberToObject(NewPatient, "CPR", PatientCPR);
        cJSON_AddStringToObject(NewPatient, timestamp, PatientNote);

        //adds the new object to the array
        cJSON_AddItemToArray(users, NewPatient);

        printf("Patient not already in file.\nCreating file for new patient.\nAdding note to patient file.\n");

    //if patient is in system, need only add new item to it
    }else if (patient_in_system == 1) {
        //adds item to object
        cJSON *patient = cJSON_GetArrayItem(users, patient_object);
        cJSON_AddStringToObject(patient, timestamp, PatientNote);

        printf("Adding note to patient file.\n");
    } else {
        printf("Error interpreting patient object");
    }




    char *json_str = cJSON_Print(json);

    // write the JSON string to the file
    fp = fopen("patient_notes.json", "w");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }
    fputs(json_str, fp);
    fclose(fp);

    // free the JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(json);

    free(timestamp);

}

char* getTimestamp() {
    time_t t;
    //the tm struct allows for the program to translate the time_t to something readable for a human
    struct tm *timestamp;

    // Use time function to get current time
    t = time(NULL);

    // Use localtime to convert the time_t value to a tm structure
    timestamp = localtime(&t);

    // Create a char array to store the formatted timestamp
    char *timestampString = (char *) malloc(20); // Adjust the size as needed

    // Check if memory allocation was successful
    if (timestampString == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Use strftime to format the timestamp as a string, here the tm struct allows for it to be formatted propperly
    strftime(timestampString, 20, "%Y-%m-%d %H:%M:%S", timestamp);

    // Return the formatted timestamp
    return timestampString;
}

