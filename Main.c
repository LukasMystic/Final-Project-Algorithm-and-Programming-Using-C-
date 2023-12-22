#include "Sorting.c"
#include "SortingPenjualan.c"
#include "Search.c"
#include "SearchPenjualan.c"
#include "baseProgram.c"
#include "Penjualandata.c"
#include "deleteData.c"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void animateText(char string[1001]) {
    const char *text = string;
    int len = strlen(text);

    for (int i = 0; i <= len; i++) {
        printf("\r"); 
        for (int j = 0; j < i; j++) {
            printf("%c", text[j]);
        }
        fflush(stdout); 
        usleep(80000);
    }
    printf("\n");
}

int main(){
	animateText("----------------------------");
	animateText("Welcome to the Animatronics!");
	animateText("----------------------------");
	animateText("Members:");
	animateText("1. Stanley Pratama Teguh - 2702311566");
	animateText("2. Nicholas Andianto - 2702277175");
	animateText("3. Owen Limantoro - 2702262330");

	printf("\nPress enter to continue....");
	getchar(); //Waiting the user to press anything
	clearScreen();
	
	int pilihan, pilihan2, pilihan3;
	
	do{
		printf("------------\n");
		printf("PROCESS DATA\n");
		printf("------------\n");
		printf("1. Stock\n");
		printf("2. Penjualan\n");
		printf("3. Delete data\n");
		printf("4. Exit\n");
		printf("What data do you want to process: ");
		scanf("%d", &pilihan);
		clearScreen();
		
		switch(pilihan){ //File Stock
			case 1:
			{	
				printf("------------\n");
				printf("MENU CHOICES\n");
				printf("------------\n");
				printf("1. Display Data\n");
				printf("2. Update Data\n");
				printf("3. Sorting Data\n");
				printf("4. Searching Data\n");
				printf("Enter your choice: ");
				scanf("%d", &pilihan2);
				
				switch(pilihan2)
				{
					case 1:
					{
						tabel data[150];
						clearScreen();
						int totalRows = readCSVFile(data, "file.txt");
						int choice1;
						printf("------------\n");
						printf("Display Data\n");
						printf("------------\n");
						
						while(1){
							printf("How many rows do you want to display: ");
							scanf("%d", &choice1);
							
							if(totalRows < choice1){
								printf("That's too many, you only have %d\n", totalRows);
							}else if(choice1 < 1){
								printf("Invalid Input, you should enter from 1 to %d\n", totalRows);
							}else 
								break;	
						}

						displayData(data, choice1);
						break;	
					}
					
					case 2:
					{
						int choice;
					    do {
					    	clearScreen();
							printf("-----------\n");
							printf("Update Data\n");
							printf("-----------\n");
							struct Barang barang[MAX_ITEMS];
					    	int n;
					    	
					        displayMenu();
					        scanf("%d", &choice);
					
					        switch (choice) {
					            case 1:
					                clearScreen();
					                while(1){
					                	printf("Enter the number of items: ");
					                	scanf("%d", &n);
					                
					                	if(n <= 0){
					                		printf("You cant add that much data!\n");
										}else break;
									}

					                for (int i = 0; i < n; ++i) {
					                    printf("Enter data for item %d:\n", i + 1);
					                    printf("Nama Barang: ");
					                    scanf(" %[^\n]", barang[i].nama);
					                    printf("Jenis: ");
					                    scanf(" %[^\n]", barang[i].jenis);
					                    printf("Stok: ");
					                    scanf("%d", &barang[i].stok);
					                    printf("Harga: ");
					                    scanf("%d", &barang[i].harga);
					                }
					
					                addToFile(barang, n);
					                break;
					
					            case 2:
								{
					                clearScreen();
					                displayUpdateOptions();
					                int updateChoice;
					                printf("Your choice: ");
					                scanf("%d", &updateChoice);
					
					                switch (updateChoice) {
					                    case 1:
										{
					                    	clearScreen();
											char search_name[100];
											printf("Search for the name of file you want to update: ");
											scanf(" %[^\n]", search_name);
											search(search_name, 1);
											
					                        char itemToUpdateStock[100];
					                        int newStock;
					                        printf("Enter the name of the item to update stock: ");
					                        scanf(" %[^\n]", itemToUpdateStock);
					                        printf("Enter the new stock value: ");
					                        scanf("%d", &newStock);
					                        updateStock("file.txt", itemToUpdateStock, newStock, barang);
											break;
										}
					
					                    case 2:
										{
					                    	clearScreen();
											char search_name[100];
											printf("Search for the name of file you want to update: ");
											scanf(" %[^\n]", search_name);
											search(search_name, 1);
											
					                        char itemToUpdatePrice[100];
					                        int newPrice;
					                        printf("Enter the name of the item to update price: ");
					                        scanf(" %[^\n]", itemToUpdatePrice);
					                        printf("Enter the new price value: ");
					                        scanf("%d", &newPrice);
					                        updatePrice("file.txt", itemToUpdatePrice, newPrice, barang);
					                        break;
										}
					
					                    case 3:
										{
					                    	clearScreen();
					                        char search_name[100];
											printf("Search for the name of file you want to update: ");
											scanf(" %[^\n]", search_name);
											search(search_name, 1);
											
					                        char oldItemName[100], newItemName[100];
					                        printf("Enter the current name of the item: ");
					                        scanf(" %[^\n]", oldItemName);
					                        printf("Enter the new name for the item: ");
					                        scanf(" %[^\n]", newItemName);
					                        rewriteName("file.txt", oldItemName, newItemName, barang);
											break;
										}
					
					                    case 4:
										{
					                    	clearScreen();
					                        char search_name[100];
											printf("Search for the name of file you want to update: ");
											scanf(" %[^\n]", search_name);
											search(search_name, 1);
											
					                        char itemToUpdateJenis[100], newJenis[50];
					                        printf("Enter the name of the item to update jenis: ");
					                        scanf(" %[^\n]", itemToUpdateJenis);
					                        printf("Enter the new jenis value: ");
					                        scanf(" %[^\n]", newJenis);
					                        rewriteJenis("file.txt", itemToUpdateJenis, newJenis, barang);
											break;
										}
					
					                    default:
					                        printf("Invalid update choice.\n");
					                        break;
					                }
					                break;
					            }
					
					            default:
					                printf("Invalid choice. Please enter 1 or 2.\n");
					                break;
					        }
					        
							if(choice != 1 && choice != 2){
								printf("Press Enter to continue...");
						        while (getchar() != '\n');  // Clear the input buffer
						        getchar();  // Wait for Enter key press
					       		clearScreen();	
							}
					
					    } while (choice != 1 && choice != 2);
						
						break;
					}
					
					case 3:
					{
						clearScreen();
					    printf("------------\n");
					    printf("Sorting Data\n");
					    printf("------------\n");
					
					    tabel data[Row];
					    int totalRows = readCSVFile(data, "file.txt");
					    if (totalRows == -1) {
					        printf("Error reading the CSV file.\n");
					        return 1;
					    }
					
					    printf("Available Columns for Sorting:\n");
					    printf("1. Nama Barang\n");
					    printf("2. Jenis\n");
					    printf("3. Stok\n");
					    printf("4. Harga\n");
					
					    int columnChoice;
					    do {
					        printf("Enter the number of the column to Sort: ");
					        if (scanf("%d", &columnChoice) != 1) {
					            printf("Invalid input. Please enter a number.\n");
					            while (getchar() != '\n');  
					        } else if (columnChoice < 1 || columnChoice > 4) {
					            printf("Invalid choice. Please enter a number between 1 and 4.\n");
					        } else {
					            break;
					        }
					    } while (1);
					
					    char columnName[50];
					    switch (columnChoice) {
					        case 1:
					            strcpy(columnName, "Nama Barang");
					            break;
					        case 2:
					            strcpy(columnName, "Jenis");
					            break;
					        case 3:
					            strcpy(columnName, "Stok");
					            break;
					        case 4:
					            strcpy(columnName, "Harga");
					            break;
					        default:
					            break;
					    }
					
					    char order[10];
					    do {
					        printf("Sort in ascending (type ascend) or descending (type descend) order: ");
					        scanf("%9s", order);
					        if (strcmp(order, "ascend") != 0 && strcmp(order, "descend") != 0) {
					            printf("Invalid input. Please enter 'ascend' or 'descend'.\n");
					        } else {
					            break;
					        }
					    } while (1);
					
					    int displayNumber;
					    do {
					        printf("Enter the number of items to display: ");
					        if (scanf("%d", &displayNumber) != 1) {
					            printf("Invalid input. Please enter a number.\n");
					            while (getchar() != '\n');  
					        } else if (displayNumber <= 0 || displayNumber > totalRows) {
					            printf("Invalid input. Please enter a number between 1 and %d.\n", totalRows);
					        } else {
					            break;
					        }
					    } while (1);
					
					    sortBy(data, totalRows, columnName, order, displayNumber);
					    break;
					}
					
					case 4:
					{
						clearScreen();
						int choice4;
						printf("--------------\n");
						printf("Searching Data\n");
						printf("--------------\n");
						printf("What column do you want to search for?\n");
				        printf("1. Name\n");
				        printf("2. Type\n");
				        printf("3. Stock\n");
				        printf("4. Price\n");
				        printf("What do you want to find : ");
				        scanf("%d", &choice4);
				
				        switch (choice4) 
						{
					        case 1:
					        {
					            char data[100];
					            printf("What electronic do you want to find? ");
					            scanf(" %[^\n]", data);
					            clearScreen();
					            search(data, choice4);
					            break;
					        }
					        
					        case 2:
					        {
					            char data[15];
					            printf("What type of electronics do you want to find? ");
					            scanf(" %s", data);
					            clearScreen();
					            search(data, choice4);
					            break;
					        }
					        
					        case 3:
					        {
					            char data[10];
					            printf("How many stock do you want to find? ");
					            scanf(" %s", data);
					            clearScreen();
					            search(data, choice4);
					            break;
					        }
					        
					        case 4:
					        {
					            char data[20];
					            printf("What price do you want to find? ");
					            scanf(" %s", data);
					            clearScreen();
					            search(data, choice4);
					            break;
					        }
					        
							default:
							{
								printf("Invalid Choice!\n");
								break;
							}	
						}
						break;
					}
										
					default:
					{
						printf("Invalid Input!\n\n");
						break;	
					}
				}
			break;
			}
			
			case 2:
			{
				clearScreen();
				printf("------------\n");
				printf("MENU CHOICES\n");
				printf("------------\n");
				printf("1. Display Data\n");
				printf("2. Entry Data\n");
				printf("3. Sorting Data\n");
				printf("4. Searching Data\n");
				printf("Enter your choice: ");
				scanf("%d", &pilihan2);
				
				switch(pilihan2)
				{
					case 1:
					{
						tabel_penjualan data[150];
						clearScreen();
						int totalRows = readCSVFile_penjualan(data, "penjualan.txt");
						int choice1;
						printf("------------\n");
						printf("Display Data\n");
						printf("------------\n");
						
						while(1){
							printf("How many rows do you want to display: ");
							scanf("%d", &choice1);
							
							if(totalRows < choice1){
								printf("That's too many, you only have %d\n", totalRows);
							}else if(choice1 < 1){
								printf("Invalid Input, you should enter from 1 to %d\n", totalRows);
							}else 
								break;	
						}
						
						displayData_penjualan(data, choice1);
						break;
					}
					
					case 2:
					{
						srand(time(NULL));
					
					    struct Date transactionDate;
					    readDate(&transactionDate);
					
					    int totalPembayaran = 0, kembalian = 0, totalItems, numNamaBarangTypes, totalCost;
					
					    struct Product *allProducts;
					    int numAllProducts = readProductDetails(&allProducts);
					
					    if (numAllProducts == -1) {
					        printf("Error opening or reading product details from file.\n");
					        return 1;
					    }
					
					    shuffleProducts(allProducts, numAllProducts);
					
					    generateAndDisplaySales(allProducts, numAllProducts, &transactionDate);
					
					    free(allProducts);
					
						break;
					}
					
					case 3:
					{
						clearScreen();
					    printf("------------\n");
					    printf("Sorting Penjualan Data\n");
					    printf("------------\n");
					
					    tabel_penjualan data[Row];
					    int totalRows = readCSVFile_penjualan(data, "penjualan.txt");
					    if (totalRows == -1) {
					        printf("Error reading the CSV file.\n");
					        return 1;
					    }
					
					    printf("Available Columns for Sorting:\n");
					    printf("1. Nama Barang\n");
					    printf("2. Type\n");
					    printf("3. Sold\n");
					    printf("4. Price\n");
					    printf("5. Tanggal Transaksi\n");
					    printf("6. Stok\n");
					
					    int columnChoice;
					    do {
					        printf("Enter the number of the column to sort by: ");
					        if (scanf("%d", &columnChoice) != 1) {
					            printf("Invalid input. Please enter a number.\n");
					            while (getchar() != '\n');
					        } else if (columnChoice < 1 || columnChoice > 6) {
					            printf("Invalid choice. Please enter a number between 1 and 6.\n");
					        } else {
					            break;
					        }
					    } while (1);
					
					    char columnName[50];
					    switch (columnChoice) {
					        case 1:
					            strcpy(columnName, "Nama Barang");
					            break;
					        case 2:
					            strcpy(columnName, "Jenis");
					            break;
					        case 3:
					            strcpy(columnName, "Barang yang dibeli");
					            break;
					        case 4:
					            strcpy(columnName, "Harga");
					            break;
					        case 5:
					            strcpy(columnName, "Tanggal transaksi");
					            break;
					        case 6:
					        	strcpy(columnName, "Stok");
					        	break;	
					        default:
					            break;
					    }
					
					    char order[10];
					    do {
					        printf("Sort in ascending (type ascend) or descending (type descend) order: ");
					        scanf("%9s", order);
					        if (strcmp(order, "ascend") != 0 && strcmp(order, "descend") != 0) {
					            printf("Invalid input. Please enter 'ascend' or 'descend'.\n");
					        } else {
					            break;
					        }
					    } while (1);
					
					    int displayNumber;
					    do {
					        printf("Enter the number of items to display: ");
					        if (scanf("%d", &displayNumber) != 1) {
					            printf("Invalid input. Please enter a number.\n");
					            while (getchar() != '\n');
					        } else if (displayNumber <= 0 || displayNumber > totalRows) {
					            printf("Invalid input. Please enter a number between 1 and %d.\n", totalRows);
					        } else {
					            break;
					        }
					    } while (1);
					
					    sortBy_penjualan(data, totalRows, columnName, order, displayNumber);
					
					    printf("Choose an action:\n");
					    printf("1. Overwrite the existing file with sorted data\n");
					    printf("2. Update to a new file with sorted data\n");
					
					    int fileAction;
					    do {
					        printf("Enter your choice: ");
					        if (scanf("%d", &fileAction) != 1) {
					            printf("Invalid input. Please enter a number.\n");
					            while (getchar() != '\n');
					        } else if (fileAction != 1 && fileAction != 2) {
					            printf("Invalid choice. Please enter 1 or 2.\n");
					        } else {
					            break;
					        }
					    } while (1);
					
					    if (fileAction == 1) {
					        overwriteFile(data, totalRows, "penjualan.txt");
					    } else if (fileAction == 2) {
					        updateFile(data, totalRows, "penjualan.txt");
					    }
					    break;
					}
					
					case 4:
					{
						clearScreen();
						int choice4;
						printf("--------------\n");
						printf("Searching Data\n");
						printf("--------------\n");
						printf("What column do you want to search for?\n");
						printf("1. Name\n");
						printf("2. Type\n");
						printf("3. Stock\n");
						printf("4. Price\n");
						printf("5. Month\n");
						printf("6. Year\n");
						printf("7. Sold\n");
						printf("What do you want to find : ");
						scanf("%d", &choice4);
						
						switch (choice4) 
						{
							case 1:
							{
								char data[100];
								printf("What electronic do you want to find? ");
								scanf(" %[^\n]", data);
								clearScreen();
								search_penjualan(data, choice4);
								break;
							}		
								        
							case 2:
							{
								char data[15];
						        printf("What type of electronics do you want to find? ");
						        scanf(" %s", data);
						        clearScreen();
						        search_penjualan(data, choice4);
						        break;
					        }
					        
					        case 3:
					        {
					            char data[10];
					            printf("How many stock do you want to find? ");
					            scanf("%s", data);
					            clearScreen();
					            search_penjualan(data, choice4);
					            break;
					        }
					        
					        case 4:
					        {
					            char data[20];
					            printf("What price do you want to find? ");
					            scanf("%s", data);
					            clearScreen();
					            search_penjualan(data, choice4);
					            break;
					        }
					        
					        case 5:
							{
					        	char data[20];
					        	printf("What month do you want to search for: ");
					        	scanf("%s", data);
					        	clearScreen();
					        	search_penjualan(data, choice4);
								break;
							}
							
							case 6:
							{
					        	char data[20];
					        	printf("What year do you want to search for: ");
					        	scanf("%s", data);
					        	clearScreen();
					        	search_penjualan(data, choice4);
								break;
							}
							
							case 7:
							{
					        	char data[20];
					        	printf("How many items sold do you want to see: ");
					        	scanf("%s", data);
					        	clearScreen();
					        	search_penjualan(data, choice4);								
								break;
							}
							
							default:
							{
								printf("Invalid Choice!\n");
								break;
							}		
						}
					break; //case 2 4
					}
					
					default:
					{
						printf("Invalid Input\n");
						break;
					}	
				} //switch case end
				break;
			}//case 2 end
			
			case 3:
			{
				char fileName[MAX_CHAR];
    			char itemName[MAX_CHAR];
			    printf("Enter file name (file.txt or penjualan.txt): ");
				scanf("%s", fileName);
				
				if((strcmp("file.txt", fileName) == 0)){
					printf("What do you item do you want to see: ");
					char item[100];
					scanf(" %[^\n]", item);
						
					search(item, 1);
					printf("Enter the name of the item to delete: ");
				    scanf(" %[^\n]", itemName);
				
				    int deletionStatus = deleteEntry(fileName, itemName);
	
				    if (deletionStatus == 1) {
				        printf("Data deleted successfully.\n");
				    } else if (deletionStatus == 0) {
				        printf("No matching entry found in %s. Program will stop.\n", fileName);
				    } else {
				        printf("Error occurred during deletion. Program will stop.\n");
				    }
				    
				}else if((strcmp("penjualan.txt", fileName)) == 0){
					printf("What do you item do you want to see: ");
					char item[100];
					scanf(" %[^\n]", item);	
					
					search_penjualan(item, 1);
					printf("Enter the name of the item to delete: ");
				    scanf(" %[^\n]", itemName);
				
				    int deletionStatus = deleteEntry(fileName, itemName);
	
				    if (deletionStatus == 1) {
				        printf("Data deleted successfully.\n");
				    } else if (deletionStatus == 0) {
				        printf("No matching entry found in %s. Program will stop.\n", fileName);
				    } else {
				        printf("Error occurred during deletion. Program will stop.\n");
				    }
				    
				}else printf("No such file name.\n"); break;
				break;
			}
			
			case 4:
			{
				animateText("You have exited the program");
				animateText("Thank you for visiting Animatronics");
				animateText("Goodbye");
				break;
			}
			
			default:
			{
				printf("Invalid Input!\n\n");
				break;
			}
		}
				
		if(pilihan != 4){
			printf("Press Enter to continue...");
	        while (getchar() != '\n');  // Clear the input buffer
			getchar();  // Wait for Enter key press
			clearScreen();
		}
		
	}while(pilihan != 4);

	return 0;
}
