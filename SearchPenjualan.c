#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char name[101];
    char type[15];
    int stock;
    int price;
    char date[30];
    int sold;
    
} Electronics;

struct Tanggal{
	int day;
	char month[10];
	int year;
};

int search_penjualan(char data[], int choice){
	
	Electronics electro[150];
	struct Tanggal dates[150];
    FILE* file = fopen("penjualan.txt", "r");

    if (file == NULL) {
        printf("Error Reading the TXT file.\n");
        fclose(file);
        return 1;
    }

    int rows = 0;
    char line[1000];

    if (fgets(line, sizeof(line), file) == NULL) {
        printf("There's no Data'\n");
        fclose(file);
        return 1;
    }

    do {
        fgets(line, sizeof(line), file);

        int read = sscanf(line, "%100[^,],%14[^,],%d,%d,%29[^,],%d", electro[rows].name, electro[rows].type, &electro[rows].stock,
        				  &electro[rows].price, electro[rows].date, &electro[rows].sold);				  
        				  
		sscanf(electro[rows].date, "%d %s %d", &dates[rows].day, dates[rows].month, &dates[rows].year);
		
        if (read != 6) {
            printf("Invalid Data Format\n");
            fclose(file);
            return 1;
        }

        rows++;

    } while (!feof(file));
    
    int found = 0;
    int find = 0;
    int many = 0;
    char *match = NULL;
    for(int i = 0; i < rows; i++){
    	switch(choice)
		{
	    	case 1://name
				{
					Electronics temp;
		        	temp = electro[i];
		        	for (int j = 0; j < strlen(temp.name); j++) {
		            	temp.name[j] = tolower(temp.name[j]);
		            	data[j] = tolower(data[j]);
		        	}
		        	
		    		match = strstr(temp.name, data);
					break;
				}
			case 2://type
			{
				Electronics temp;
       			temp = electro[i];
        		for (int j = 0; j < strlen(temp.type); j++) {
            		temp.type[j] = tolower(temp.type[j]);
            		data[j] = tolower(data[j]);
        		}
				
				match = strstr(temp.type,data);	
				break;
			}
			case 3://stock
			{
			
				find = (atoi(data) == electro[i].stock);
				break;
			}
			case 4://price
			{
				find = (atoi(data)== electro[i].price);
				break;
			}
			case 5: //month
			{
				struct Tanggal temp;
				temp = dates[i];
        		for (int j = 0; j < strlen(temp.month); j++) {
            		temp.month[j] = tolower(temp.month[j]);
            		data[j] = tolower(data[j]);
        		}
				
				match = strstr(temp.month,data);	
				break;
			}
			case 6: //year
			{
				find = (atoi(data) == dates[i].year);
				break;
			}
			case 7: //sold
			{
				find = (atoi(data) == electro[i].sold);
				break;
			}

		}
		
		if (match != NULL || find) {
			many++;
            if (!found) {
                printf("Data Found. Detail of data:\n");
				printf("\n---------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf("| %-4s | %-45s | %-15s | %-6s | %-9s | %-20s | %-20s |\n", "No", "Nama Barang", "Jenis", "Stok", "Harga", "Tanggal transaksi", "Barang yang dibeli");
    			printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
                found = 1;
            }
            printf("| %-4d | %-45s | %-15s | %-6d | %-9d | %-20s | %-20d |\n", many, electro[i].name, electro[i].type, electro[i].stock,
            		electro[i].price, electro[i].date, electro[i].sold);
        }
	}
	
	if (found) printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    else printf("Data not found.\n");
    
	fclose(file);
}
