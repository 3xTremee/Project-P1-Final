#include "smaller functions.h"


// If it fails to open the file (e.g., due to a file not found), it prints an error message and returns from the function.
void file_opening(FILE *fp) {
if (fp == NULL) {
printf("Error: Unable to open the file.\n");
return;
}}