#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

int deleteEntry(const char *fileName, const char *itemName);


int deleteEntry(const char *fileName, const char *itemName) {
    FILE *file = fopen(fileName, "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    char line[MAX_CHAR];
    int entryDeleted = 0; // Flag to check if any entry is deleted

    // Read each line from the original file
    while (fgets(line, MAX_CHAR, file) != NULL) {
        // Check if the line contains the item to be deleted
        if (strstr(line, itemName) == NULL) {
            // Write the line to the temporary file
            fputs(line, tempFile);
        } else {
            entryDeleted = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file only if an entry was deleted
    if (entryDeleted) {
        if (remove(fileName) != 0) {
            perror("Error deleting the original file");
            exit(EXIT_FAILURE);
        }

        // Rename the temporary file to the original file
        if (rename("temp.txt", fileName) != 0) {
            perror("Error renaming the temporary file");
            exit(EXIT_FAILURE);
        }

        return 1; // Deletion successful
    } else {
        return 0; // No matching entry found
    }
}
