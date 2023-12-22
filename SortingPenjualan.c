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
    char tanggaltransaksi[50];
    int barangdibeli;
} tabel_penjualan;

void displayData_penjualan(tabel_penjualan data[], int numRows) {
    printf("\n---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-4s | %-45s | %-15s | %-6s | %-9s | %-20s | %-20s |\n", "No", "Nama Barang", "Jenis", "Stok", "Harga", "Tanggal transaksi", "Barang yang dibeli");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < numRows && i < Row; i++) {
        printf("| %-4d | %-45s | %-15s | %-6d | %-9d | %-20s | %-20d |\n",
               i + 1, data[i].namabarang, data[i].jenis, data[i].stok, data[i].harga, data[i].tanggaltransaksi, data[i].barangdibeli);
        printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
}

void sortBy_penjualan(tabel_penjualan data[], int numRows, const char *column, const char *order, int number) {
    int i, j;
    tabel_penjualan temp;

    for (i = 0; i < numRows - 1; i++) {
        for (j = 0; j < numRows - i - 1; j++) {
            int compareResult = 0;

            // Compare based on the selected column
            if (strcmp(column, "Nama Barang") == 0) {
                compareResult = strcmp(data[j].namabarang, data[j + 1].namabarang);
            } else if (strcmp(column, "Jenis") == 0) {
                compareResult = strcmp(data[j].jenis, data[j + 1].jenis);
            } else if (strcmp(column, "Stok") == 0) {
                compareResult = data[j].stok - data[j + 1].stok;
            } else if (strcmp(column, "Harga") == 0) {
                compareResult = data[j].harga - data[j + 1].harga;
            } else if (strcmp(column, "Tanggal transaksi") == 0) {
                compareResult = strcmp(data[j].tanggaltransaksi, data[j + 1].tanggaltransaksi);
            } else if (strcmp(column, "Barang yang dibeli") == 0) {
                compareResult = data[j].barangdibeli - data[j + 1].barangdibeli;
            } else {
                printf("Invalid column name.\n");
                return;
            }

            // Swap if required based on order
            if ((strcmp(order, "ascend") == 0 && compareResult > 0) ||
                (strcmp(order, "descend") == 0 && compareResult < 0)) {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    printf("Data found. Detail of data:\n");
    displayData_penjualan(data, number);
}

int readCSVFile_penjualan(tabel_penjualan data[], const char *filename) {
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
        sscanf(line, "%49[^,],%49[^,],%d,%d,%49[^,],%d",
               data[row].namabarang, data[row].jenis, &data[row].stok,
               &data[row].harga, data[row].tanggaltransaksi, &data[row].barangdibeli);
        row++;
    }

    fclose(file);
    return row;
}

void overwriteFile(tabel_penjualan data[], int numRows, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "Nama Barang,Jenis,Stok,Harga,Tanggal transaksi,Barang yang dibeli\n");

    for (int i = 0; i < numRows; i++) {
        fprintf(file, "%s,%s,%d,%d,%s,%d\n",
                data[i].namabarang, data[i].jenis, data[i].stok,
                data[i].harga, data[i].tanggaltransaksi, data[i].barangdibeli);
    }

    fclose(file);
    printf("File overwritten successfully.\n");
}

void updateFile(tabel_penjualan data[], int numRows, const char *filename) {
    char newFilename[50];
    printf("Enter the name for the new file: ");
    scanf("%s", newFilename);

    FILE *file = fopen(newFilename, "w");
    if (file == NULL) {
        printf("Error opening new file for writing.\n");
        return;
    }

    fprintf(file, "Nama Barang,Jenis,Stok,Harga,Tanggal transaksi,Barang yang dibeli\n");

    for (int i = 0; i < numRows; i++) {
        fprintf(file, "%s,%s,%d,%d,%s,%d\n",
                data[i].namabarang, data[i].jenis, data[i].stok,
                data[i].harga, data[i].tanggaltransaksi, data[i].barangdibeli);
    }

    fclose(file);
    printf("Data written to the new file '%s'.\n", newFilename);
}
