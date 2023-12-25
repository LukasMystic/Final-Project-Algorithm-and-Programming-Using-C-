#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

struct Product {
    char name[100];
    char type[20];
    int stock;
    int price;
};

struct Date {
    int day;
    int month;
    int year;
};

// Global variable for month names
const char *monthNames[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni",
                            "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

// Function prototypes
int readProductDetails(struct Product **products);
void shuffleProducts(struct Product *products, int numProducts);
void readDate(struct Date *date);
void generateAndDisplaySales(struct Product *products, int numProducts, struct Date *date);
void appendToPenjualanFile(struct Product *product, struct Date *date, int quantity, FILE *file);

//int main() {
//    srand(time(NULL));
//
//    struct Date transactionDate;
//    readDate(&transactionDate);
//
//    int totalPembayaran = 0, kembalian = 0, totalItems, numNamaBarangTypes, totalCost;
//
//    struct Product *allProducts;
//    int numAllProducts = readProductDetails(&allProducts);
//
//    if (numAllProducts == -1) {
//        printf("Error opening or reading product details from file.\n");
//        return 1;
//    }
//
//    shuffleProducts(allProducts, numAllProducts);
//
//    generateAndDisplaySales(allProducts, numAllProducts, &transactionDate);
//
//    free(allProducts);
//
//    return 0;
//}

int readProductDetails(struct Product **products) {
    FILE *file = fopen("file.txt", "r");

    if (!file) {
        return -1;
    }

    fscanf(file, "%*[^\n]\n");

    int i = 0, bytesRead;
    struct Product *tempProducts = NULL;

    while (1) {
        tempProducts = realloc(tempProducts, (i + 1) * sizeof(struct Product));

        bytesRead = fscanf(file, "%99[^,],%19[^,],%d,%d\n", tempProducts[i].name, tempProducts[i].type,
                           &tempProducts[i].stock, &tempProducts[i].price);

        if (strlen(tempProducts[i].name) > 0) {
            i++;
        }

        if (bytesRead == EOF || bytesRead < 4) {
            break;
        }
    }

    fclose(file);

    *products = tempProducts;

    return i;
}

void shuffleProducts(struct Product *products, int numProducts) {
    for (int i = numProducts - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        struct Product temp = products[i];
        products[i] = products[j];
        products[j] = temp;
    }
}

int isValidDate(int day, int month, int year, int maxYear, int maxMonth, int maxDay) {
    // Basic validation for month and day ranges
    if (month < 1 || month > 12 || day < 1) {
        return 0; // Invalid month or day
    }

    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (day > 31) {
                return 0; // Invalid day for months with 31 days
            }
            break;

        case 4: case 6: case 9: case 11:
            if (day > 30) {
                return 0; // Invalid day for months with 30 days
            }
            break;

        case 2:
            // Leap year check for February
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                if (day > 29) {
                    return 0; // Invalid day for a leap year
                }
            } else {
                if (day > 28) {
                    return 0; // Invalid day for a non-leap year
                }
            }
            break;

        default:
            return 0; // Invalid month
    }

    // Check if the year is within the specified range
    if (year < 1970 || year > maxYear) {
        return 0; // Invalid year
    }

    // Check if the month is within the specified range
    if (year == maxYear && month > maxMonth) {
        return 0; // Invalid month for the current year
    }

    // Check if the day is within the specified range
    if (year == maxYear && month == maxMonth && day > maxDay) {
        return 0; // Invalid day for the current month
    }

    return 1; // Valid date
}

void readDate(struct Date *date) {
    int isValid = 0;

    // Get current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    do {
        printf("Enter the transaction date (dd mm yyyy): ");
        int result = scanf("%d %d %d", &date->day, &date->month, &date->year);

        // Check if the input format is valid and the date itself is valid
        if (result == 3 && isValidDate(date->day, date->month, date->year, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday)) {
            isValid = 1;
        } else {
            // Clear the input buffer
            while (getchar() != '\n');
            printf("Invalid date. Please enter a valid date between 1970 and %d.\n", tm.tm_year + 1900);
        }
    } while (!isValid);
}

void generateAndDisplaySales(struct Product *products, int numProducts, struct Date *date) {
    int totalItems = rand() % 21;

    if (totalItems == 0) {
        printf("No sales were made on %02d %s %d.\n", date->day, monthNames[date->month - 1], date->year);
    } else {
    	printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------\n");                                                              
    	printf("| %-4s | %-45s | %-15s | %-6s | %-9s | %-22s | %-20s |\n", "No", "Nama Barang", "Jenis", "Stok", "Harga", "Tanggal transaksi", "Barang yang terjual");
   		printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
		     
        FILE *file = fopen("penjualan.txt", "a");
        if (!file) {
            printf("Error opening or creating penjualan.txt.\n");
            return;
        }

        bool usedProducts[numProducts];
        memset(usedProducts, false, sizeof(usedProducts));

        int totalPembayaran = 0, totalCost = 0, kembalian = 0;

        for (int i = 0; i < totalItems; i++) {
            int randomIndex;

            // Find an unused product
            do {
                randomIndex = rand() % numProducts;
            } while (usedProducts[randomIndex]);

            usedProducts[randomIndex] = true;

            int quantity;

            do {
                quantity = rand() % 5;
            } while (quantity <= 0);
            
            printf("| %-4d | %-45s | %-15s | %-6d | %-9d | %02d %s %d\t\t| %-20d |\n",
                   i+1, products[randomIndex].name, products[randomIndex].type, products[randomIndex].stock,
                   products[randomIndex].price, date->day, monthNames[date->month - 1], date->year, quantity);

            appendToPenjualanFile(&products[randomIndex], date, quantity, file);
            products[randomIndex].stock -= quantity;

            // Update total payment and total cost
            totalPembayaran += products[randomIndex].price * quantity;
            totalCost += products[randomIndex].price * quantity;
        }
        printf("------------------------------------------------------------------------------------------------------------------------------------------------\n\n");                                                              

        // Calculate kembalian (ensure it's not zero)
        do {
            // Add a random amount to the total payment
            kembalian = rand() % (500 * totalItems) + 1;
        } while (kembalian == 0);

        // Round kembalian to the nearest multiple of 100
        kembalian = ((kembalian + 99) / 100) * 100;

        // Calculate total payment as the sum of total cost and kembalian
        totalPembayaran = totalCost + kembalian;

        fclose(file);

        printf("Transaction details appended to penjualan.txt.\n");
        printf("----------------------------------------------------------------------------------------+\n");
        printf("%-40s%s %d\n", "Total biaya belanja =", "", totalCost);
        printf("%-40s%s %d\n", "Total pembayaran =", "", totalPembayaran);
        printf("%-40s%s %d\n", "Kembalian =", "", kembalian);
    }
}

void appendToPenjualanFile(struct Product *product, struct Date *date, int quantity, FILE *file) {
    fprintf(file, "\n%s,%s,%d,%d,%02d %s %d,%d", product->name, product->type, product->stock,
            product->price, date->day, monthNames[date->month - 1], date->year, quantity);
}
