#include "write patient note.h"

char *getTimestamp();           //Returns time in 'Year/Month-Day Hour:Min:Sec' format

//logic:
/*
>open and parse file
>go through JSON to check if the CPR number is in it already, and which object it is (avoids having empty objects for patients w/o notes in file
>does one of two operations based on the return, [==0]: create new object with the item note, [!=0]: adds an item to exising object
*/

void write_note(const char InputCPR[11]){
    //instead of using atof multiple times further down, simply creating a double with the atof of inputCPR to refer to instead
    double PatientCPR = atof(InputCPR);

    // open the JSON file
    FILE *fp = fopen("patient_notes.json", "r");
    //If file read is empty, run error
    if (fp == NULL) {
        printf("Error: Unable to open read file.\n");
        return;
    }

    // Move the file pointer to the end of the file
    fseek(fp, 0, SEEK_END);
    // Get the current position, which is the size of the file
    long file_size = ftell(fp);
    // Move the file pointer back to the beginning of the file
    fseek(fp, 0, SEEK_SET);


    //create buffer
    char* buffer = (char *)malloc(file_size * 1);

    int len = fread(buffer, 1, file_size, fp);
    buffer[len] = '\0'; // Null-terminate the buffer
    fclose(fp);

    // parse the JSON data into 'json'
    cJSON *json = cJSON_Parse(buffer);
    // if 'json' is empty, run error
    if (json == NULL) {
        // get error message if possible
        const char *error_ptr = cJSON_GetErrorPtr();
        // if we get an error message, print it
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return;
    }

    //create variables to 'extract' from file
        //Patient_object is extracting which object (if any) has the InputCPR
    int patient_object;
        //If the CPR is in the file, sets bool to 1, allows for different operations based on
        // if it needs to add item to an existing object or create a new to add to
    bool patient_in_system = 0;

    //To check if the patient is registered in the notes system, check if the given CPR can be read in the file
    cJSON *patients = cJSON_GetObjectItemCaseSensitive(json, "Patients");
    //makes sure the item is an array, else print error message
    if (cJSON_IsArray(patients)) {
        //loops through each object in the array
        for (int i = 0; i < cJSON_GetArraySize(patients); i++) {
            //extracts "CPR" item from the current object
            cJSON *patient = cJSON_GetArrayItem(patients, i);
            cJSON *cpr = cJSON_GetObjectItemCaseSensitive(patient, "CPR");

            //check if the extracted "CPR" item == Input CPR
            if (cJSON_IsNumber(cpr) && (cpr->valuedouble == PatientCPR)){
                //If they match, reflect TRUE and index in the variables
                patient_in_system = 1;
                patient_object = i;
                //Stop the loop with break
                break;
            }
        }
    } else{
        printf("Error: 'Patients' is not an array in the JSON.\n");
    }



    //Scan for patient note (limited to 100, may change if needed)
    char Note[100];
    printf("Please type error or note:\n");
    //scans user input until it meets a new line, allows it to scan full sentences (but not paragraphs)
    scanf(" %[^\n]", Note);

    //Get current timestamp
    char *timestamp = getTimestamp();

    char PatientNote[120] = "";

    strcat(PatientNote, timestamp);
    strcat(PatientNote, Note);


    //If the patient CPR is not in system, it needs to add a new object and note to the new object
    if (patient_in_system == 0) {
        //Creates new object "NewPatient"
        cJSON *NewPatient = cJSON_CreateObject();
        //Adds both CPR number and the patient note to the new object
        cJSON_AddNumberToObject(NewPatient, "CPR", PatientCPR);
        cJSON_AddStringToObject(NewPatient, "NOTE", PatientNote);

        //adds the new object to the array
        cJSON_AddItemToArray(patients, NewPatient);

        printf("Patient not already in file.\nCreating file for new patient.\nAdding note to patient file.\n");

    //if patient is in system, need only add new item to it
    }else if (patient_in_system == 1) {
        //Finds the object from the array and the object index extracted from loop earlier
        cJSON *patient = cJSON_GetArrayItem(patients, patient_object);
        //Adds patient note to the existing object
        cJSON_AddStringToObject(patient, "NOTE", PatientNote);

        printf("Adding note to patient file.\n");
    //If somehow neither is true, prints error message
    } else {
        printf("ERROR: couldnt add note to file");
    }



    //Makes a string to put it in file
    char *json_str = cJSON_Print(json);

    // write the JSON string to the file
    fp = fopen("patient_notes.json", "w");
    if (fp == NULL) {
        printf("Error: Unable to open write file.\n");
        return;
    }
    //puts the new string into the file
    fputs(json_str, fp);
    fclose(fp);

    // free the buffer, timestamp, JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(json);
    free(timestamp);
    free(buffer);
}

char* getTimestamp() {
    time_t t;
    //the tm struct allows for the program to translate the time_t to something readable for a human
    struct tm *timestamp;

    // Use time function to get current time
    t = time(NULL);

    // Use localtime to convert the time_t value to a tm structure
    timestamp = localtime(&t);

    // Create a char string to store the formatted timestamp
    char *timestampString = (char *) malloc(36); // 36 because the timestamp is 35 characters long

    // Use strftime to format the timestamp string
    strftime(timestampString, 36, "\nDATE: %Y/%m-%d %X\nNOTE: ", timestamp);

    // Return the formatted timestamp
    return timestampString;
}

