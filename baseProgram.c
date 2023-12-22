#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 1000

struct Barang {
    char nama[100];
    char jenis[50];
    int stok;
    int harga;
};

void displayMenu() {
    printf("Choose an option:\n");
    printf("1. Add new data\n");
    printf("2. Update data\n");
    printf("Your choice: ");
}

void displayUpdateOptions() {
    printf("Choose an update option:\n");
    printf("1. Update stock\n");
    printf("2. Update price\n");
    printf("3. Rewrite 'nama barang' by name\n");
    printf("4. Rewrite 'Jenis' column by name\n");
}

int getItemIndexFromFile(const char *filename, const char *itemName) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    char line[256];
    int itemIndex = 0;

    // Skip the first line (headers)
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        printf("Error reading file.\n");
        return -1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char currentItemName[100];
        sscanf(line, "%[^,],", currentItemName);

        if (strcasecmp(currentItemName, itemName) == 0) {
            fclose(file);
            return itemIndex;  // Return the index if found
        }

        itemIndex++;
    }

    fclose(file);
    printf("Item '%s' not found.\n", itemName);
    return -1;  // Return -1 if not found
}

void updateStock(const char *filename, const char *itemName, int newStock, struct Barang barang[]) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("tempFile.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char line[256];
    int currentIndex = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char currentItemName[100];
        int currentStock;

        sscanf(line, "%[^,],%[^,],%d,%d", currentItemName, barang[currentIndex].jenis, &currentStock, &barang[currentIndex].harga);

        if (strcasecmp(currentItemName, itemName) == 0) {
            found = 1;
            barang[currentIndex].stok = newStock;
            fprintf(tempFile, "%s,%s,%d,%d\n", currentItemName, barang[currentIndex].jenis, barang[currentIndex].stok, barang[currentIndex].harga);
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentIndex++;
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Item '%s' not found.\n", itemName);
        remove("tempFile.txt");
    } else {
        remove(filename);
        rename("tempFile.txt", filename);
        printf("Stock updated successfully.\n");
    }
}
void updatePrice(const char *filename, const char *itemName, int newPrice, struct Barang barang[]) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("tempFile.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char line[256];
    int currentIndex = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char currentItemName[100];
        int currentStock, currentPrice;

        sscanf(line, "%[^,],%[^,],%d,%d", currentItemName, barang[currentIndex].jenis, &currentStock, &currentPrice);

        if (strcasecmp(currentItemName, itemName) == 0) {
            found = 1;
            barang[currentIndex].harga = newPrice;
            fprintf(tempFile, "%s,%s,%d,%d\n", currentItemName, barang[currentIndex].jenis, currentStock, barang[currentIndex].harga);
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentIndex++;
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Item '%s' not found.\n", itemName);
        remove("tempFile.txt");
    } else {
        remove(filename);
        rename("tempFile.txt", filename);
        printf("Price updated successfully.\n");
    }
}

int isNameDuplicate(const char *filename, const char *newName) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;  // Treat as duplicate if file cannot be opened
    }

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        char currentItemName[100];
        sscanf(line, "%[^,],", currentItemName);

        if (strcasecmp(currentItemName, newName) == 0) {
            fclose(file);
            return 1;  // Name is found, treat as duplicate
        }
    }

    fclose(file);
    return 0;  // Name is not found, not a duplicate
}

void rewriteName(const char *filename, const char *oldName, const char *newName, struct Barang barang[]) {
    // Check for duplicate name
    if (isNameDuplicate(filename, newName)) {
        printf("Error: The name '%s' already exists in the file.\n", newName);
        return;
    }

    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("tempFile.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char line[256];
    int currentIndex = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char currentItemName[100];
        int currentStock, currentPrice;

        sscanf(line, "%[^,],%[^,],%d,%d", currentItemName, barang[currentIndex].jenis, &currentStock, &currentPrice);

        if (strcasecmp(currentItemName, oldName) == 0) {
            found = 1;
            fprintf(tempFile, "%s,%s,%d,%d\n", newName, barang[currentIndex].jenis, currentStock, currentPrice);
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentIndex++;
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Item '%s' not found.\n", oldName);
        remove("tempFile.txt");
    } else {
        remove(filename);
        rename("tempFile.txt", filename);
        printf("Name updated successfully.\n");
    }
}

void displayItemListFromFile() {
    FILE *file = fopen("file.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Available items for updating:\n");

    char line[256];
    int itemNumber = 1;

    // Skip the first line (headers)
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        printf("Error reading file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char itemName[100];
        sscanf(line, "%[^,],", itemName);
        printf("%d. %s\n", itemNumber++, itemName);
    }

    fclose(file);
}


void rewriteJenis(const char *filename, const char *itemName, const char *newJenis, struct Barang barang[]) {
    FILE *file = fopen(filename, "r");
    FILE *tempFile = fopen("tempFile.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char line[256];
    int currentIndex = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char currentItemName[100];
        char currentJenis[50];
        int currentStock, currentPrice;

        sscanf(line, "%[^,],%[^,],%d,%d", currentItemName, currentJenis, &currentStock, &currentPrice);

        if (strcasecmp(currentItemName, itemName) == 0) {
            found = 1;
            fprintf(tempFile, "%s,%s,%d,%d\n", currentItemName, newJenis, currentStock, currentPrice);
        } else {
            fprintf(tempFile, "%s", line);
        }

        currentIndex++;
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        printf("Item '%s' not found.\n", itemName);
        remove("tempFile.txt");
    } else {
        remove(filename);
        rename("tempFile.txt", filename);
        printf("Jenis updated successfully.\n");
    }
}
int isNameDuplicate2(const char *filename, const char *newName) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;  // Treat as duplicate if file cannot be opened
    }

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        char currentItemName[100];
        sscanf(line, "%[^,],", currentItemName);

        if (strcasecmp(currentItemName, newName) == 0) {
            fclose(file);
            return 1;  // Name is found, treat as duplicate
        }
    }

    fclose(file);
    return 0;  // Name is not found, not a duplicate
}

void addToFile(struct Barang barang[], int n) {
    FILE *file = fopen("file.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int errorFlag = 0;  // Flag to track errors

    for (int i = 0; i < n; ++i) {
        // Input validation checks
        if (strlen(barang[i].nama) == 0) {
            printf("Error: Nama Barang cannot be empty.\n");
            errorFlag = 1;
            continue;
        }

        if (strlen(barang[i].jenis) == 0) {
            printf("Error: Jenis Barang cannot be empty.\n");
            errorFlag = 1;
            continue;
        }

        if (barang[i].stok <= 0) {
            printf("Error: Stok must be greater than 0.\n");
            errorFlag = 1;
            continue;
        }

        if (barang[i].harga <= 0) {
            printf("Error: Harga must be greater than 0.\n");
            errorFlag = 1;
            continue;
        }

        // Check for duplicate names
        if (isNameDuplicate("file.txt", barang[i].nama)) {
            printf("Error: Duplicate Nama Barang found.\n");
            errorFlag = 1;
            continue;
        }

        // If all validation checks pass, add the data to the file
        fprintf(file, "\n%s,%s,%d,%d", barang[i].nama, barang[i].jenis, barang[i].stok, barang[i].harga);
    }

    fclose(file);

    if (!errorFlag) {
        printf("Data has been added to file.txt.\n");
    }
}
