#include "timestamp.h"

/*
Add item to array/object.
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToArray(cJSON *array, cJSON *item)
{
    return add_item_to_array(array, item);
}

*/

/*void timestamp_administration() {

    char choice;
    printf("Has the medicine been administered?\n\nType 'Y' for yes or 'N' no \n>");

//Kode som tjekker om valg er Y eller N
    scanf(" %c", &choice);
    choice = toupper(choice);

    if (choice == 'Y') {
        time_t t;
        time(&t);
        char adm[100];
        sprintf(adm, "Time of administration: %s", ctime(&t));
*/
        //cJSON_AddItemToArray( , adm) /* Hvordan får jeg fat i det rigtige cjson array*/

    //}

//}

/* Mulig løsning
 * // Your existing JSON array as a string
    const char *existingJsonArray = "[\"value1\", \"value2\", \"value3\"]";

    // Parse the existing JSON array
    cJSON *jsonArray = cJSON_Parse(existingJsonArray);
    if (jsonArray == NULL) {
        fprintf(stderr, "Failed to parse existing JSON array\n");
        return 1;
    }

    // Create a cJSON string with the desired value (timestamp)
    time_t t;
    time(&t);
    char adm[100];
    sprintf(adm, "Time of administration: %s", ctime(&t));

    cJSON *jsonString = cJSON_CreateString(adm);

    // Add the cJSON string to the end of the existing cJSON array
    cJSON_AddItemToArray(jsonArray, jsonString);

    // Print the updated cJSON array to stdout
    char *updatedJsonArray = cJSON_Print(jsonArray);
    printf("%s\n", updatedJsonArray);

    // Don't forget to free the cJSON objects
    cJSON_free(updatedJsonArray);
    cJSON_Delete(jsonArray);
    */