#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define Row 150
#define Column 4

typedef struct {
    char namabarang[50];
    char jenis[50];
    int stok;
    int harga;
} tabel;


void sortBy(tabel data[], int numRows, const char *column, const char *order,int number);
void displayData(tabel data[], int numRows);
int readCSVFile(tabel data[], const char *filename);

void sortBy(tabel data[], int numRows, const char *column, const char *order, int number) {
    int i, j;
    tabel temp;

    for (i = 0; i < numRows - 1; i++) {
        for (j = 0; j < numRows - i - 1; j++) {
            int compareResult = 0;

    
            if (strcmp(column, "Nama Barang") == 0) {
                compareResult = strcmp(data[j].namabarang, data[j + 1].namabarang);
            } else if (strcmp(column, "Jenis") == 0) {
                compareResult = strcmp(data[j].jenis, data[j + 1].jenis);
            } else if (strcmp(column, "Stok") == 0) {
                compareResult = data[j].stok - data[j + 1].stok;
            } else if (strcmp(column, "Harga") == 0) {
                compareResult = data[j].harga - data[j + 1].harga;
            } else {
                printf("Invalid column name.\n");
                return;
            }
			int UpOrDown;
            if ((strcmp(order, "ascend") == 0 && compareResult > 0) ||
                (strcmp(order, "descend") == 0 && compareResult < 0)) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    printf("Data found. Detail of data:\n");
    displayData(data, number);
}



void displayData(tabel data[], int numRows) {
    printf("\n-----------------------------------------------------------------------------------------------\n");
    printf("| %-4s | %-45s | %-15s | %-6s | %-9s |\n", "No", "Nama Barang", "Jenis", "Stok", "Harga");
    printf("-----------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < numRows && i < Row; i++) {
        printf("| %-4d | %-45s | %-15s | %-6d | %-9d |\n",
               i + 1, data[i].namabarang, data[i].jenis, data[i].stok, data[i].harga);
        printf("-----------------------------------------------------------------------------------------------\n");
    }
}

int readCSVFile(tabel data[], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    char line[500];
    int row = 0;

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return -1;
    }

    while (fgets(line, sizeof(line), file) != NULL && row < Row) {
        sscanf(line, "%49[^,],%49[^,],%d,%d,%d,%d,%49[^,],%49[^\n]",
               data[row].namabarang, data[row].jenis, &data[row].stok,
               &data[row].harga);
        row++;
    }

    fclose(file);
    return row;
}


