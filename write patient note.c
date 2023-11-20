#include "write patient note.h"

void write_note(){
    char *PatientCPR = "308031234";//temp

    //Scan patient note
    char PatientNote[100];
    printf("Please type error or note:\n");
    scanf("%s\n", PatientNote);

    FILE *fp = fopen("patient_notes.json", "r+");
    if (fp == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    // This code reads the contents of the opened file into a character buffer named buffer.
    char buffer[3048];
    int len = fread(buffer, 1, sizeof(buffer), fp);

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



    //Open JSON file in 'W' ?? eller skal den åbnes efter of skrive "buffer" til den? det skal den nok...

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
}

