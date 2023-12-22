#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char name[101];
    char type[15];
    int stock;
    int price;
} Electronic;

int search(char data[], int choice){
	
	Electronic electro[150];
    FILE* file = fopen("file.txt", "r");

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

        int read = sscanf(line, "%99[^,],%14[^,],%d,%d",
            electro[rows].name, electro[rows].type, &electro[rows].stock, &electro[rows].price);

        if (read != 4) {
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
	    	case 1:
				{
					Electronic temp;
		        	temp = electro[i];
		        	for (int j = 0; j < strlen(temp.name); j++) {
		            	temp.name[j] = tolower(temp.name[j]);
		            	data[j] = tolower(data[j]);
		        	}
		        	
		    		match = strstr(temp.name, data);
					break;
				}
			case 2:
				{
					Electronic temp;
	       			temp = electro[i];
	        		for (int j = 0; j < strlen(temp.type); j++) {
	            		temp.type[j] = tolower(temp.type[j]);
	            		data[j] = tolower(data[j]);
	        		}
					
					match = strstr(temp.type,data);	
					break;
				}
			case 3:
				{
				
					find = (atoi(data) == electro[i].stock);
					break;
				}
			case 4:
				{
					find = (atoi(data)== electro[i].price);
					break;
				}
		}
		
		if (match != NULL || find) {
			many++;
            if (!found) {
                printf("Data Found. Detail of data:\n");
				printf("\n-----------------------------------------------------------------------------------------------\n");
    			printf("| %-4s | %-45s | %-15s | %-6s | %-9s |\n", "No", "Nama Barang", "Jenis", "Stok", "Harga");
    			printf("-----------------------------------------------------------------------------------------------\n");
                found = 1;
            }
            printf("| %-4d | %-45s | %-15s | %-6d | %-9d |\n", many, electro[i].name, electro[i].type, electro[i].stock,
                electro[i].price);
        }
	}
	
	if (found) printf("-----------------------------------------------------------------------------------------------\n");
    else printf("Data not found.\n");
    
	fclose(file);
}
