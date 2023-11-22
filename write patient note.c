#include "write patient note.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "cJSON.h"

char* getTimestamp();

void write_note(const char *PatientCPR){

    //open file and read the file into a string and parse it

    //Scan patient note
    char PatientNote[100];
    printf("Please type error or note:\n");
    //To allow the user to write sentences the program scans for %[^\n] which means that it scans for input until it records 'Enter'
    scanf(" %[^\n]", PatientNote);

    //Get timestamp (using top-down to make write_note() clearer)
    char *timestamp = getTimestamp();

    if (IsInSystem == 0) {
        //Creates new object to write in
        cJSON *json = cJSON_CreateObject();
        //Writes information to the object
        cJSON_AddStringToObject(json, "Patient CPR", PatientCPR);
        cJSON_AddStringToObject(json, timestamp, PatientNote);

        // convert the cJSON object to a JSON string which can be "uploaded" to the JSON file
        char *json_str = cJSON_Print(json);
    }

    //if is in system, write to object...


    // Openes the JSON file in append mode to allow us to add the object without deleting the existing file
        //This means that the JSON file shows 'error cases' in chronological order
    FILE *fp = fopen("patient_notes.json", "a");
    //error message if unable to open file
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return 1;
    }

    //prints the object being uploaded
    printf("\n\nFollowing note is being uploaded:\n%s\n", json_str);
    //adds the new object to the JSON file
    fputs(json_str, fp);
    //closes the JSON file
    fclose;
    // free temp the JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(json);







    /*
    char *PatientCPR = "308031234";//temp

    //Scan patient note
    char PatientNote[100];
    printf("Please type error or note:\n");
    scanf("%s\n", PatientNote);

    cJSON *Patient = cJSON_CreateObject();
    //cJSON_AddStringToObject(json, "note", PatientNote);
    cJSON *note, cJSON_AddItemToObject(Patients, "PatientNote", "note");


    char *json_str = cJSON_Print(note);

    FILE *fp = fopen("patient_notes.json", "w");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    // This code reads the contents of the opened file into a character buffer named buffer.
    //char buffer[3048];
    //int len = fread(buffer, 1, sizeof(buffer), fp);

    //Extracts the array from the parsed JSON data
    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return;
    }

    bool PatientInFile = 0;

    //To check if the patient is registered in the notes system, check if the given CPR can be read in the file
    cJSON *patients = cJSON_GetObjectItemCaseSensitive(json, "Patients");
    if (cJSON_IsArray(patients)) {
        for (int i = 0; i < cJSON_GetArraySize(patients); i++) {
            cJSON *ReadingPatient = cJSON_GetArrayItem(patients, i);
            cJSON *cpr = cJSON_GetObjectItemCaseSensitive(ReadingPatient, "CPR");


            //The atof funktion converts the array of chars (String) into a float
            if (cJSON_IsNumber(cpr) && (cpr->valuedouble == atof(PatientCPR))) {
                cJSON *cpr = cJSON_GetObjectItemCaseSensitive(patients, "cpr");
                cJSON *note = cJSON_GetObjectItemCaseSensitive(patients, "note");

                if (cJSON_IsNumber(cpr) && (patients->valuestring != NULL)) {
                    PatientInFile = 1;
                    break;
                }
                }
            }
        } else{
        printf("Error: 'Patients' is not an array in the JSON.\n");
    }


    printf("%s\n", json_str);
    fputs(json_str, fp);
    fclose;
    // free the JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(note);*/

    //Open JSON file in 'W' ?? eller skal den åbnes efter og skrive en 'kopi' til den? eller 'R+'?
    //kan ogs bruge 'A', så vil JSON bare være en liste over noter, ikke sorteret i personer, men den nyeste nederst.
    //det kunne også være muglig. Hvis den bliver 'wiped' hver dag og hver dag bliver en "rapport" af errors sendt til kontoret
    // (hvis det overhovedet kommer til at være så ofte(det er det nok egentlig ikke...))

    //create object for the CPR if PatientInFIle == 0
    //CJSON_PUBLIC(cJSON *) cJSON_CreateObject(void); - ????
    //if (PatientInFile == 0){
    //    cJSON_CreateObject();
    //}

    //create item in object (CPR)
    //CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
    //item = current time
    //string = scanned note
    //object = PatientCPR

    //fclose(fp);

    // Don't forget to free the allocated memory



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

