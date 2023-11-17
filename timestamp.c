#include "timestamp.h"

/*
Add item to array/object.
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToArray(cJSON *array, cJSON *item)
{
    return add_item_to_array(array, item);
}

*/

void timestamp_administration() {

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

        cJSON_AddItemToArray( , adm) /* Hvordan får jeg fat i det rigtige cjson array*/

    }

}
