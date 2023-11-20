#include "timestamp.h"

// Function to add timestamp to an arbitrary field in a JSON object
void addTimestampToField(cJSON *userObject, const char *fieldName) {
    // Locate the specified field in the cJSON object
    cJSON *fieldObj = cJSON_GetObjectItemCaseSensitive(userObject, fieldName);

    if (cJSON_IsString(fieldObj)) {
        // Retrieve the existing string value
        char *existingValue = cJSON_GetStringValue(fieldObj);

        // Append the timestamp to the existing string between the quotes
        time_t t;
        time(&t);
        char timestamp[100];
        sprintf(timestamp, " : Time of administration: %s", ctime(&t));

        char *newValue = (char *) malloc(strlen(existingValue) + strlen(timestamp) + 1);
        strcpy(newValue, existingValue);
        strcat(newValue, timestamp);

        // Check if the existing string ends with a newline character, and adjust the format accordingly
        /* if (existingValue[strlen(existingValue)  - 1] == '\n') {
            strcat(newValue, timestamp);
        } else {
            strcat(newValue, timestamp + strlen(": Time of administration: "));
        }
        */
        // Replace the existing string with the new value
        cJSON_ReplaceItemInObjectCaseSensitive(userObject, fieldName, cJSON_CreateString(newValue));

        // Free the allocated memory
        free(newValue);

        /*
    } else if (fieldObj == NULL) {
        // If the field does not exist, create a new string with the timestamp
        cJSON_AddStringToObject(userObject, fieldName, ": Time of administration: ");
    } else {
        fprintf(stderr, "Error: %s is not a string in the JSON object.\n", fieldName);
    }
}
*/
    }}
/*

\\ Skal muligvis være en anden funktion som bruger timestamp funktionen, ellers skal variablerne være en del af main

int main() {
    \\ Output og input fil skal umiddelbart være den samme for at kunne opdatere
    const char *inputFilePath = "users.json";
    const char *outputFilePath = "users..json";
    \\ Vi skal finde en måde hvorpå brugeren skal markere hvilken medicin, ellers skal det opdateres automatisk
    \\ User index kigger på hvilken person der er tale om
    const int targetUserIndex = 0;  // Choose the user index you want to modify
    \\ Target field er hvilket felt som vi ønsker at adde timestamp til
    const char *targetFieldName = "Medicine1";  // Choose the field you want to modify


    // Læser user filen og lægger det i en fil variabel
    FILE *file = fopen(inputFilePath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    \\ Kigger på hvor stor filen er
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    \\ Allkokerer plads til stringen
    char *jsonString = (char *)malloc(fileSize + 1);
    if (jsonString == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    fread(jsonString, 1, fileSize, file);
    fclose(file);

    jsonString[fileSize] = '\0';

    // Parse the JSON string into a cJSON object
    cJSON *jsonObject = cJSON_Parse(jsonString);
    if (jsonObject == NULL) {
        fprintf(stderr, "Error parsing JSON string.\n");
        free(jsonString);
        return 1;
    }

    // Locate the "Users" array in the cJSON object
    cJSON *usersArray = cJSON_GetObjectItemCaseSensitive(jsonObject, "Users");

    // Call the function to add the timestamp to the specified field
    addTimestampToField(cJSON_GetArrayItem(usersArray, targetUserIndex), targetFieldName);

    // Write the updated cJSON object back to the file
    FILE *outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        cJSON_Delete(jsonObject);
        free(jsonString);
        return 1;
    }

    char *updatedJsonText = cJSON_Print(jsonObject);
    fprintf(outputFile, "%s", updatedJsonText);
    fclose(outputFile);


    // Don't forget to free the cJSON objects and allocated memory
    cJSON_Delete(jsonObject);
    free(updatedJsonText);
    free(jsonString);

    return 0;
*/