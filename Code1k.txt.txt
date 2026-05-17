#include<stdio.h>
#include<stdlib.h> // contains system("cls") command
#include<conio.h> // contains _getch() command
#include<string.h> //to search easier


/* KEYBOARD NUMBERS

1.Enter = 13
2.Left arrow = 75
3.Right arrow = 77
4.Up arrow = 72
5.Down arrow = 80
6.Q = 113,q = 81
7.Manager signup pin = 8909,login = 1221
*/



//++++++++++++ STRUCTURES ++++++++++++++++++
// accounts 
struct ManagerAccount {
	char username[999];
	char password[999];

};

struct CustomerAccount {
	char username[999];
	char password[999];

};

// items
struct InventoryItems {
	char ID[99];
	char name[99];
	double price;
	int quantity;
};

// weighted items
struct WeightedItems {
	char ID[99];
	char name[99];
	double price;
	double weight;
};

// ++++++++ SHORTCUT COMMANDS +++++++

// nextscreen is used to reset the values of input so it doesnt stay the same from the previous screen
void nextscreen(int *KeyPressed,int *position) {
	system("cls");
	*KeyPressed = 0;
	*position = 1;
}

// keyboard shortcuts
#define up 72
#define down 80
#define right 77
#define left 75
#define enter 13
#define q 81
#define Q 113
#define y 121
#define Y 89
#define n 110
#define N 78

// SAVE INVENTORY
void SaveInventory(struct InventoryItems products[], int *quantity_item_counter,int *weighted_item_counter,struct WeightedItems productsW[]) {
	FILE* fptr;
	*quantity_item_counter = 0;
	*weighted_item_counter = 0;
	if (fopen_s(&fptr, "inventory.txt", "r") == 0) {
		while (fscanf_s(fptr, "%s %s %lf %d", products[*quantity_item_counter].ID, (unsigned int)_countof(products[*quantity_item_counter].ID), products[*quantity_item_counter].name, (unsigned int)_countof(products[*quantity_item_counter].name), &products[*quantity_item_counter].price, &products[*quantity_item_counter].quantity) == 4) {
			if (*quantity_item_counter >= 2500) {
				break;
			}
			(*quantity_item_counter)++;
		}
		fclose(fptr);
	}

	if (fopen_s(&fptr, "weighteditems.txt", "r") == 0) {
		while (fscanf_s(fptr, "%s %s %lf %lf", productsW[*weighted_item_counter].ID, (unsigned int)_countof(productsW[*weighted_item_counter].ID), productsW[*weighted_item_counter].name, (unsigned int)_countof(productsW[*weighted_item_counter].name), &productsW[*weighted_item_counter].price, &productsW[*weighted_item_counter].weight) == 4) {
			if (*weighted_item_counter >= 2500) {
				break;
			}
			(*weighted_item_counter)++;
		}
		fclose(fptr);
	}

}

// movement is used to change between options easier and flexible (0.) is like y axis and (.0) is for x axis
/*void movement(float* position, int KeyPressed) {
	if (KeyPressed == 80) {
		*position += 1.0;
	}
	else if (KeyPressed == 72) {
		*position -= 1.0;
	}
	else if (KeyPressed == 77) {
		*position += 0.01;
	}
	else if (KeyPressed == 75) {
		*position -= 0.01;
	}

	if (*position == 0) {
		*position += 1.0;
	}
}
*/

// ++++++++ SCREENS ++++++++++
void startupmessage() {
	system("cls");

	printf("            -------------- Select mode to enter --------------\n\n\n            +-----------------+       +----------------+\n            |  Customer mode  |       |  Manager Mode  |\n            +-----------------+       +----------------+\n\n                               <<--->>");
	printf("\n\n\n\n\n(!)Use the arrow keys to navigate!");

	_getch();
	return;
}




// MENU STARTUP SCREEN
void MenuScreen(int position) {
	system("cls");
	printf("            -------------- Select mode to enter --------------\n\n\n");
	printf("            +-----------------+       +----------------+\n");
	
	if (position == 1) {
		printf("            |=>Customer mode  |       |  Manager Mode  |\n");
		printf("            +-----------------+       +----------------+");

	}
	else if (position == 2) {
		printf("            |  Customer mode  |       |=>Manager Mode  |\n");
		printf("            +-----------------+       +----------------+");
	}

}

// Create account or log in screen
void AccountAccess(int position,int ManagerMode,int CustomerMode,int KeyPressed) {
	system("cls");
	if (ManagerMode == 1) {
		printf("            -------------- Access Account to Manager mode --------------\n\n\n");
		printf("            +------------------+       +----------------+\n");

		if (position == 1) {
			printf("            |=>Create Account  |       |      Login     |\n");
			printf("            +------------------+       +----------------+");

		}
		else if (position == 2) {
			printf("            |  Create Account  |       |    =>Login     |\n");
			printf("            +------------------+       +----------------+");

		}

	}else if(CustomerMode == 1){
		printf("            -------------- Access Account to Customer mode --------------\n\n\n");
		printf("            +------------------+       +----------------+\n");

		if (position == 1) {
			printf("            |=>Create Account  |       |      Login     |\n");
			printf("            +------------------+       +----------------+");

		}
		else if (position == 2) {
			printf("            |  Create Account  |       |    =>Login     |\n");
			printf("            +------------------+       +----------------+");

		}
	}
	

}

// SIGNUP SCREEN
void signup(int position, int ManagerMode, int CustomerMode, int KeyPressed, struct ManagerAccount* accountM, int* nameisput, int* passisput, struct CustomerAccount* accountC) {
	system("cls");
	FILE* fptr;
	const int managersignupPin = 8909;
	int pin;
	char storedName[100];
	char storedPass[100];
	int found = 0;

	if (ManagerMode == 1) {
		printf("            ------------- Create a Manager account  --------------\n\n\n");
		printf("            +----------------------------------------+\n");

		printf("            |               Enter Username           |\n            +----------------------------------------+\n\n            >");
		scanf_s("%s", accountM->username, sizeof(accountM->username));
		*nameisput = 1;
		printf("\n            +----------------------------------------+\n");
		printf("            |               Enter Password           |\n");
		printf("            +----------------------------------------+\n\n            >");
		scanf_s("%s", accountM->password, sizeof(accountM->password));
		*passisput = 1;
		printf("\n            +----------------------------------------+\n");
		printf("            |              Enter signup pin          |\n");
		printf("            +----------------------------------------+\n            Test pin: 8909\n\n            >");
		if (scanf_s("%d", &pin) != 1) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF);

			pin = -1;
		}

		if (pin == managersignupPin) {
			nextscreen(&KeyPressed, &position);
			printf("            ------------- Create a Manager account  --------------\n\n\n");

			printf("                               Username              \n");
			printf("            +----------------------------------------+\n");

			printf("                            ( %s )            \n            +----------------------------------------+\n\n", accountM->username);
			printf("                              Password              \n");
			printf("            +----------------------------------------+\n");
			printf("                            ( %s )      \n", accountM->password);
			printf("            +----------------------------------------+\n\n");

			printf("            +----------------------------------------+\n");

			printf("            |                 =>SUBMIT?              |\n            +----------------------------------------+\n\n\n\n");
			printf("Press Q to re-enter information.");

			KeyPressed = _getch();
			if (KeyPressed == 81 || KeyPressed == 113) {
				*nameisput = 0, * passisput = 0;
				return;
			}
			else {
				fopen_s(&fptr, "managers_accounts.txt", "r");

				if (fptr == NULL) {
					printf("Error: Could not open database.\n");
					fopen_s(&fptr, "managers_accounts.txt", "a");
					fclose(fptr);
				}
				else {
					while (fscanf_s(fptr, "%s %s", storedName, (unsigned)_countof(storedName),storedPass,(unsigned)_countof(storedPass)) == 2) {
						if (strcmp(accountM->username, storedName) == 0) {
							found = 1;
							break;
						}
					}
					fclose(fptr);
				}

				if (found) {
					printf("\nAccount with the same name already exists! press ANY to try again...");
					KeyPressed = _getch();
						*passisput = 0, * nameisput = 0;
						return;
				}
				else {
					fopen_s(&fptr, "managers_accounts.txt", "a");
					fprintf(fptr, "%s %s\n", accountM->username, accountM->password);
					fclose(fptr);
				}
			}
		}else {
			printf("    Error: the pin is incorrect.Press ANY key to try again...");
			KeyPressed = _getch();
				*passisput = 0, * nameisput = 0;
				return;
		}

	}
	else if (CustomerMode == 1) {
		printf("            ------------- Create a Customer account  --------------\n\n\n");
		printf("            +----------------------------------------+\n");

		printf("            |               Enter Username           |\n            +----------------------------------------+\n\n            >");
		scanf_s("%s", accountC->username, sizeof(accountC->username));
		*nameisput = 1;
		printf("\n            +----------------------------------------+\n");
		printf("            |               Enter Password           |\n");
		printf("            +----------------------------------------+\n\n            >");
		scanf_s("%s", accountC->password, sizeof(accountC->password));
		*passisput = 1;

		nextscreen(&KeyPressed, &position);
		printf("            ------------- Confirm customer account creation  --------------\n\n\n");

		printf("                               Username              \n");
		printf("            +----------------------------------------+\n");

		printf("                            ( %s )            \n            +----------------------------------------+\n\n", accountC->username);
		printf("                              Password              \n");
		printf("            +----------------------------------------+\n");
		printf("                            ( %s )      \n", accountC->password);
		printf("            +----------------------------------------+\n\n");

		printf("            +----------------------------------------+\n");

		printf("            |                 =>SUBMIT?              |\n            +----------------------------------------+\n\n\n\n");
		printf("Press Q to re-enter information.");

		KeyPressed = _getch();
		if (KeyPressed == 81 || KeyPressed == 113) {
			*passisput = 0, * nameisput = 0;
			return;
		}
		else {
			fopen_s(&fptr, "customer_accounts.txt", "r");

			if (fptr == NULL) {
				printf("Error: Could not open database.\n");
				fopen_s(&fptr, "customer_accounts.txt", "a");
				fclose(fptr);
			}
			else {
				while (fscanf_s(fptr, "%s %s", storedName, (unsigned)_countof(storedName),storedPass,(unsigned)_countof(storedPass)) == 2) {
					if (strcmp(accountC->username, storedName) == 0) {
						found = 1;
						break;
					}
				}
				fclose(fptr);
			}

			if (found) {
				printf("\nAccount with the same name already exists! press ANY to try again...");
				KeyPressed = _getch();
					*passisput = 0, * nameisput = 0;
					return;
			}
			else {
				fopen_s(&fptr, "customer_accounts.txt", "a");
				fprintf(fptr, "%s %s\n", accountC->username, accountC->password);
				fclose(fptr);
			}
		}

	}

}

 

// LOGIN SCREEN
void login(int position, int ManagerMode, int CustomerMode, int KeyPressed, struct ManagerAccount* accountM, int* nameisput, int* passisput, struct CustomerAccount* accountC) {
	system("cls");
	const int managerloginpin = 1221;
	int pin;
	if (ManagerMode == 1) {
		printf("            ------------- login to a manager account --------------\n\n\n");
		printf("            +----------------------------------------+\n");

		printf("            |               Enter Username           |\n            +----------------------------------------+\n\n            >");
		scanf_s("%s", accountM->username, sizeof(accountM->username));
		*nameisput = 1;
		printf("\n            +----------------------------------------+\n");
		printf("            |               Enter Password           |\n");
		printf("            +----------------------------------------+\n\n            >");
		scanf_s("%s", accountM->password, sizeof(accountM->password));
		*passisput = 1;
		printf("\n            +----------------------------------------+\n");
		printf("            |              Enter login pin          |\n");
		printf("            +----------------------------------------+\n            Test pin: 1221\n\n           >");
		
		if (scanf_s("%d", &pin) != 1) {
			int c;
			while ((c = getchar()) != '\n' && c != EOF);

			pin = -1;
		}

		if (pin == managerloginpin) {
			nextscreen(&KeyPressed, &position);
			printf("            ------------- Confirm manager account login --------------\n\n\n");

			printf("                               Username              \n");
			printf("            +----------------------------------------+\n");

			printf("                            ( %s )            \n            +----------------------------------------+\n\n", accountM->username);
			printf("                              Password              \n");
			printf("            +----------------------------------------+\n");
			printf("                            ( %s )      \n", accountM->password);
			printf("            +----------------------------------------+\n\n");

			printf("            +----------------------------------------+\n");

			printf("            |                 =>SUBMIT?              |\n            +----------------------------------------+\n\n\n\n");
			printf("Press Q to re-enter information.");

			KeyPressed = _getch();
			if (KeyPressed == 'q' || KeyPressed == 'Q') {
				*passisput = 0,*nameisput=0;
				return;
			}
			else {
				FILE* fptr;
				char storedName[100];
				char storedPass[100];
				int found = 0;

				fopen_s(&fptr, "managers_accounts.txt", "r");

				if (fptr == NULL) {
					printf("Error: Could not open database.\n");
				}
				else {
					while (fscanf_s(fptr, "%s %s", storedName, (unsigned)_countof(storedName), storedPass, (unsigned)_countof(storedPass)) == 2) {
						if (strcmp(accountM->username, storedName) == 0 && strcmp(accountM->password, storedPass) == 0) {
							found = 1;
							break;
						}
					}
					fclose(fptr);
				}

				if (found) {
					printf("\nLogin Successful! Press any key to continue...");
					_getch();
					return;
				}
				else {
					printf("\nInvalid Username or Password. Press ANY key to try again...");
					KeyPressed =_getch();
					*nameisput = 0;
					*passisput = 0;
					return;
				}
			}
		}
		else {
			printf("    Error: the pin is incorrect.Press ANY key to try again");
			KeyPressed = _getch();

			strcpy_s(accountM->password, sizeof(accountM->password), "");
			strcpy_s(accountM->username, sizeof(accountM->username), "");
				*passisput = 0, * nameisput = 0;
				return;
		}
	}
	else if (CustomerMode == 1) {
		printf("            ------------- Login to a customer account --------------\n\n\n");
		printf("            +----------------------------------------+\n");

		printf("            |               Enter Username           |\n            +----------------------------------------+\n\n            >");
		scanf_s("%s", accountC->username, sizeof(accountC->username));
		*nameisput = 1;
		printf("\n            +----------------------------------------+\n");
		printf("            |               Enter Password           |\n");
		printf("            +----------------------------------------+\n\n            >");
		scanf_s("%s", accountC->password, sizeof(accountC->password));
		*passisput = 1;

		nextscreen(&KeyPressed, &position);
		printf("            ------------- Confirm customer account login --------------\n\n\n");

		printf("                               Username              \n");
		printf("            +----------------------------------------+\n");

		printf("                            ( %s )            \n            +----------------------------------------+\n\n", accountC->username);
		printf("                              Password              \n");
		printf("            +----------------------------------------+\n");
		printf("                            ( %s )      \n", accountC->password);
		printf("            +----------------------------------------+\n\n");

		printf("            +----------------------------------------+\n");

		printf("            |                 =>SUBMIT?              |\n            +----------------------------------------+\n\n\n\n");
		printf("Press Q to re-enter information.");

		KeyPressed = _getch();
		if (KeyPressed == 81 || KeyPressed == 113) {
			*nameisput = 0, * passisput = 0;
			return;
		}
		else {
			FILE* fptr;
			char storedName[100];
			char storedPass[100];
			int found = 0;

			fopen_s(&fptr, "customer_accounts.txt", "r");

			if (fptr == NULL) {
				printf("Error: Could not open database.\n");
			}
			else {
				while (fscanf_s(fptr, "%s %s", storedName, (unsigned)_countof(storedName), storedPass, (unsigned)_countof(storedPass)) == 2) {
					if (strcmp(accountC->username, storedName) == 0 && strcmp(accountC->password, storedPass) == 0) {
						found = 1;
						break;
					}
				}
				fclose(fptr);
			}

			if (found) {
				printf("\nLogin Successful! Press ANY key to continue...");
				_getch();
				return;
			}
			else {
				printf("\nInvalid Username or Password. Press ANY key to try again....");
				KeyPressed = _getch();
				*nameisput = 0;
				*passisput = 0;
				return;
			}
		}

	}
}

// CUSTOMER DASHBOARD
void CustomerDashboard(int position, struct CustomerAccount* accountC) {
	system("cls");
	
	printf("       ---------- CUSTOMER DASHBOARD ----------\nWelcome,%s!\n\n\n\n\nPress Q to end demo", accountC->username);
}

// MANAGER DASHBOARD
void ManagerDashboard(int *position, struct ManagerAccount* accountM, int KeyPressed) {
	system("cls");
	
	if (*position > 4) {
		*position = 1;
	}
	else if (*position < 1) {
		*position = 4;
	}
	printf("       ---------- MANAGER DASHBOARD ----------\nWelcome,%s!\n\n\n\n", accountM->username);
	if (*position == 1) {
		printf("=>(Inventory)\nCreate item\nEdit item\nSignout");
	}
	else if (*position == 2) {
		printf("Inventory\n=>(Create item)\nEdit item\nSignout");
	}
	else if (*position == 3) {
		printf("Inventory\nCreate item\n=>(Edit item)\nSignout");
	}
	else if (*position == 4) {
		printf("Inventory\nCreate item\nEdit item\n=>(Signout)");
	}
}


// Add Item Screen
void createitem(int position, int KeyPressed, int* created) {
	char id[50] = "", itemname[100] = "";
	double itemPrice = 0.0, weight = 0.0;
	int quantity = 0,found = 0;

	printf("            ------------- Add item to inventory --------------\n\n\n");
	printf("            +----------------------------------------+\n");

	printf("            |            Enter item ID               |\n            +----------------------------------------+\n\n            >");
	scanf_s("%s", id, (unsigned int)sizeof(id));

	printf("\n            +----------------------------------------+\n");
	printf("            |            Enter item name             |\n");
	printf("            +----------------------------------------+\n\n            >");
	scanf_s("%s", itemname, (unsigned int)sizeof(itemname));

	printf("\n            +----------------------------------------+\n");
	printf("            |            Enter item price            |\n");
	printf("            +----------------------------------------+\n\n            >");
	scanf_s("%lf", &itemPrice);

	if (itemPrice <= 0) {
		printf("\n\nPrice must be a real number above zero! Press ANY key to continue...");
		_getch();
		return;
	}

	printf("\nIs the item weighted?(Y/N)");
	KeyPressed = _getch();
	if (KeyPressed == Y || KeyPressed == y) {
		printf("\n            +----------------------------------------+\n");
		printf("            |     Enter current available weight     |\n");
		printf("            +----------------------------------------+\n\n            >");
		scanf_s("%lf", &weight);
		if (weight < 0) {
			printf("\n\nquantity must be an integer above zero! Press ANY key to continue...");
			_getch();
			return;
		}
	}
	else if (KeyPressed = n || KeyPressed == N) {
		printf("\n            +----------------------------------------+\n");
		printf("            |      Enter current item quantity       |\n");
		printf("            +----------------------------------------+\n\n            >");
		scanf_s("%d", &quantity);

		if (quantity < 0 || quantity >= 'a' || quantity <= 'z' || quantity >= 'A' || quantity <= 'z') {
			printf("\n\nquantity must be an integer above zero! Press ANY key to continue...");
			_getch();
			return;
		}
	}

	

	nextscreen(&KeyPressed, &position);
	printf("            ------------- CONFIRM ITEM --------------\n\n\n");

	printf("                               Item name              \n");
	printf("            +----------------------------------------+\n");
	printf("                                 ( %s )               \n            +----------------------------------------+\n\n", itemname);
	printf("                                Item ID              \n");
	printf("            +----------------------------------------+\n");
	printf("                                 ( %s )         \n", id);
	printf("            +----------------------------------------+\n\n");
	printf("                              Item price              \n");
	printf("            +----------------------------------------+\n");
	printf("                                 ( %.2lf ) EGP      \n", itemPrice);
	printf("            +----------------------------------------+\n\n");
	if (weight > 0) {
		printf("                           Current Weight              \n");
		printf("            +----------------------------------------+\n");
		if (weight > 1000) {
			printf("                                 ( %.2lf ) KG   \n", weight / 1000.0);
		}
		else {
			printf("                                 ( %.2lf ) g   \n", weight);
		}
		
		printf("            +----------------------------------------+\n\n");
	}
	else if (quantity > 0) {
		printf("                           Current Quantity              \n");
		printf("            +----------------------------------------+\n");
		printf("                                 ( %d )x      \n", quantity);
		printf("            +----------------------------------------+\n\n");
	}
	printf("            +----------------------------------------+\n");
	printf("            |                 =>SUBMIT?              |\n            +----------------------------------------+\n\n\n\n");
	printf("Press Q to re-enter information.");

	KeyPressed = _getch();
	if (KeyPressed == 'q' || KeyPressed == 'Q') {
		return;
	}
	else if (KeyPressed == enter) {
		FILE* fptr = NULL;
		char storedid[50] = { 0 }, storedname[50] = { 0 };
		double storedprice = 0.0,storedweight = 0.0;
		int storedquantity = 0;

		if (weight > 0) {
			if (fopen_s(&fptr, "weighteditems.txt", "r") == 0 && fptr != NULL) {
				while (fscanf_s(fptr, "%s %s %lf %lf", storedid, (unsigned int)_countof(storedid), storedname, (unsigned int)_countof(storedname), &storedprice, &storedweight) == 4) {
					if (strcmp(id, storedid) == 0 || strcmp(itemname, storedname) == 0) {
						found = 1;
						break;
					}
				}
				fclose(fptr);
			}
		}
		else if (quantity > 0) {
			if (fopen_s(&fptr, "inventory.txt", "r") == 0 && fptr != NULL) {
				while (fscanf_s(fptr, "%s %s %lf %d", storedid, (unsigned int)_countof(storedid), storedname, (unsigned int)_countof(storedname), &storedprice, &storedquantity) == 4) {
					if (strcmp(id, storedid) == 0 || strcmp(itemname, storedname) == 0) {
						found = 1;
						break;
					}
				}
				fclose(fptr);
			}
		}

		if (found == 1) {
			printf("\nItem with the same name/ID already exists. Press any key to try again...");
			_getch();
			return;
		}
		else {
			if (weight > 0) {
				if (fopen_s(&fptr, "weighteditems.txt", "a") == 0 && fptr != NULL) {
					fprintf(fptr, "%s %s %.2lf %.2lf\n", id, itemname, itemPrice, weight);
					fclose(fptr);
					*created = 1;
				}
				else {
					printf("\nError: Could not save to file (Check folder permissions)! Press ANY key to exit...");
					_getch();
					*created = -1;
					return;
				}
			}
			else if (quantity > 0) {
				if (fopen_s(&fptr, "inventory.txt", "a") == 0 && fptr != NULL) {
					fprintf(fptr, "%s %s %.3lf %d\n", id, itemname, itemPrice, quantity);
					fclose(fptr);
					*created = 1;
				}
				else {
					printf("\nError: Could not save to file (Check folder permissions)! Press ANY key to exit...");
					_getch();
					*created = -1;
					return;
				}
			}
			
		}
	}
}

// VIEW ITEMS
void inventory(int *KeyPressed,int quantity_item_counter,int weighted_item_counter, struct InventoryItems products[],struct WeightedItems productsW[],int *position) {
	char id[50] = { 0 }, itemname[100] = { 0 };
	double price = 0.0;
	int quantity = 0, counter = 0;

	system("cls");
	printf("       ---------- INVENTORY ----------");
	
	if (*KeyPressed == right) {
		*position += 1;
	}
	else if (*KeyPressed == left) {
		*position -= 1;
	}
	if (*position > 2) {
		*position = 1;
	}
	else if (*position < 1) {
		*position = 2;
	}
	if (*position == 1) {
		printf("\n\n        =>(QUANTITY ITEMS)        WEIGHTED ITEMS ");

		printf("\n\n\n\n%-15s|%-30s|%-15s|%-15s\n", "ID", "NAME", "PRICE(EGP)", "QUANTITY");
		printf("---------------------------------------------------------------------\n");
		if (counter < quantity_item_counter) {
			for (counter = 0; counter < quantity_item_counter; counter++) {
				printf("%-15s|%-30s|%-15.2lf|x%-15d\n", products[counter].ID, products[counter].name, products[counter].price, products[counter].quantity);
			}
		}
		else {
			printf("\n\n\nThere is no inventory currently..");
		}

		printf("\n\npress Q to return to dashboard.....");
	}
	
	else if (*position == 2) {
		printf("\n\n           QUANTITY ITEMS      =>(WEIGHTED ITEMS)");
		printf("\n\n\n\n%-15s|%-30s|%-15s|%-15s\n", "ID", "NAME", "PRICE(per gram)", "WEIGHT");
		printf("---------------------------------------------------------------------\n");
		if (counter < weighted_item_counter) {
			for (counter = 0; counter < weighted_item_counter; counter++) {
				if (productsW[counter].weight > 1000) {
					printf("%-15s|%-30s|%-15.2lf|%-5.2lfKG\n", productsW[counter].ID, productsW[counter].name, productsW[counter].price, productsW[counter].weight / 1000);
				}
				else {
					printf("%-15s|%-30s|%-15.2lf|%-15.2lf g\n", productsW[counter].ID, productsW[counter].name, productsW[counter].price, productsW[counter].weight);
				}

			}
		}
		else {
			printf("\n\n\nThere is no inventory currently..");
		}
		printf("\n\npress Q to return to dashboard.....");
	}

	*KeyPressed = _getch();
	if (*KeyPressed == 0 || *KeyPressed == 224) {
		*KeyPressed = _getch(); 
	}
}

// Edit items
void EditItem(int *position, int *KeyPressed,struct InventoryItems products[],struct WeightedItems productsW[],int quantity_item_counter,int weighted_item_counter) {
	FILE* fptr;
	int counter = 0,quantity = 0,newname=0,newprice=0,newquantity=0,newid = 0,foundquantity=0,foundweight=0,newweight =0;
	char id[20] = "", name[50] = "";
	double price = 0.0,weight = 0.0;
	system("cls");

	printf("       ---------- EDIT ITEMS ----------");

	if (*KeyPressed == right) {
		*position += 1;
	}
	else if (*KeyPressed == left) {
		*position -= 1;
	}
	if (*position > 2) {
		*position = 1;
	}
	else if (*position < 1) {
		*position = 2;
	}

	if (*position == 1) {
		printf("\n\n        =>(QUANTITY ITEMS)        WEIGHTED ITEMS ");
		printf("\n\n\n\n%-15s|%-30s|%-15s|%-15s\n", "ID", "NAME", "PRICE", "QUANTITY");
		if (counter < quantity_item_counter) {
			while (counter < quantity_item_counter) {
				printf("%-15s|%-30s|%-15.2lf|x%-15d\n", products[counter].ID, products[counter].name, products[counter].price, products[counter].quantity);
				counter++;
			}
		}
		else {
			printf("\n\n\nThere is no inventory currently..");
		}
		printf("\n\nIntiate editing?(Y/N)");
		*KeyPressed = _getch();
		if (*KeyPressed == 0 || *KeyPressed == 224) {
			*KeyPressed = _getch();
		}
		if (*KeyPressed == Y || *KeyPressed == y) {
			printf("\nEnter item ID > ");
			scanf_s("%s", id, (unsigned int)sizeof(id));
			for (counter = 0; counter < quantity_item_counter; counter++) {
				if (strcmp(id, products[counter].ID) == 0) {
					foundquantity = 1;
					break;
				}
			}

			if (!foundquantity) {
				printf("ID does not exist! Press ANY key to continue...");
				_getch();
				return;
			}
		}
		else if (*KeyPressed == n || *KeyPressed == N) {
			return;
		}
		else {
			return;
		}
	}
	else if (*position == 2) {
		printf("\n\n           QUANTITY ITEMS      =>(WEIGHTED ITEMS)");
		printf("\n\n\n\n%-15s|%-30s|%-15s|%-15s\n", "ID", "NAME", "PRICE(per gram)", "WEIGHT");
		if (counter < weighted_item_counter) {
			while (counter < weighted_item_counter) {
				if (productsW[counter].weight > 1000) {
					printf("%-15s|%-30s|%-15.2lf|%-5.2lfKG\n", productsW[counter].ID, productsW[counter].name, productsW[counter].price, productsW[counter].weight/1000.0);
				}
				else {
					printf("%-15s|%-30s|%-15.2lf|%-5.2lfg\n", productsW[counter].ID, productsW[counter].name, productsW[counter].price, productsW[counter].weight);
				}
				counter++;
			}
		}
		else {
			printf("\n\n\nThere is no inventory currently..");
		}
		printf("\n\nIntiate editing?(Y/N)");
		*KeyPressed = _getch();
		if (*KeyPressed == 0 || *KeyPressed == 224) {
			*KeyPressed = _getch();
		}
		if (*KeyPressed == Y || *KeyPressed == y) {
			printf("\nEnter item ID > ");
			scanf_s("%s", id, (unsigned int)sizeof(id));
			for (counter = 0; counter < weighted_item_counter; counter++) {
				if (strcmp(id, productsW[counter].ID) == 0) {
					foundweight = 1;
					break;
				}
			}

			if (!foundweight) {
				printf("ID does not exist! Press ANY key to continue...");
				_getch();
				return;
			}
		}
		else if (*KeyPressed == n || *KeyPressed == N) {
			return;
		}
		else {
			return;
		}
	}

		if (foundquantity) {
			foundquantity = 0;
			nextscreen(KeyPressed, position);
			while (1) {
				system("cls");

				printf("       ---------- EDIT ITEMS ----------\n\n%-15s|%-30s|%-15s|%-15s\n-------------------------------------------------------------------------------\n%-15s|%-30s|%-15.2lf|%-15d\n\n\n", "ID", "NAME", "PRICE", "QUANTITY", products[counter].ID, products[counter].name, products[counter].price, products[counter].quantity);

				if (*position > 5) {
					*position = 1;
				}
				else if (*position < 1) {
					*position = 5;
				}
				if (*position == 1) {
					printf("\n\n\n=>(ID)       NAME       PRICE       QUANTITY       RETURN");
				}
				else if (*position == 2) {
					printf("\n\n\n  ID     =>(NAME)       PRICE       QUANTITY       RETURN");
				}
				else if (*position == 3) {
					printf("\n\n\n  ID       NAME     =>(PRICE)       QUANTITY       RETURN");
				}
				else if (*position == 4) {
					printf("\n\n\n  ID       NAME       PRICE     =>(QUANTITY)       RETURN");
				}
				else if (*position == 5) {
					printf("\n\n\n  ID       NAME       PRICE       QUANTITY     =>(RETURN)");
				}

				*KeyPressed = _getch();
				if(*KeyPressed == 0 || *KeyPressed == 224){
					*KeyPressed = _getch();
					if (*KeyPressed == right) {
						*position += 1;
					}
					else if (*KeyPressed == left) {
						*position -= 1;
					}
				}
				
				int found = 0;

				if (*KeyPressed == enter && *position == 1) {
					printf("\n\nEnter a new ID for the item > ");
					scanf_s("%s", id, (unsigned int)sizeof(id));
					for (int j = 0; j < quantity_item_counter; j++) {
						if (strcmp(id, products[j].ID) == 0 && j != counter) {
							found = 1;
							break;
						}
					}

					if (found) {
						printf("\n\nitem with the same ID exists! Press ANY key to continue...");
						_getch();
						continue;
					}
					newid = 1;
					continue;
				}
				else if (*KeyPressed == enter && *position == 2) {
					printf("\n\nEnter new name for the item > ");
					scanf_s("%s", name, (unsigned int)sizeof(name));
					for (int j = 0; j < quantity_item_counter; j++) {
						if (strcmp(name, products[j].name) == 0 && j!=counter) {
							found = 1;
							break;
						}
					}

					if (found) {
						printf("\n\nitem with the same name exists! Press ANY key to continue...");
						_getch();
						continue;
					}
					newname = 1;
					continue;
				}
				else if (*KeyPressed == enter && *position == 3) {
					printf("\n\nEnter new price for the item > ");
					scanf_s("%lf", &price);
					if (price <= 0) {
						printf("\nPrice cannot be under or equal zero! Press ANY key to continue...");
						_getch();
						continue;
					}
					newprice = 1;
					continue;
				}
				else if (*KeyPressed == enter && *position == 4) {
					printf("\n\nEdit the quantity for the item > ");
					scanf_s("%d", &quantity);
					if (quantity < 0) {
						printf("Quantity cannot be under zero! Press ANY key to continue...");
						_getch();
						continue;
					}
					newquantity = 1;
					continue;
				}
				else if (*KeyPressed == enter && *position == 5) {
					if (newid || newname || newprice || newquantity) {
						printf("\n       --------------------------------------------\n       |               EDITS SUMMARY              |\n       --------------------------------------------");
						if (newid) {
							printf("\n       |%-10s%-12s---> %-15s|", "ID:", products[counter].ID, id);
						}
						if (newname) {
							printf("\n       |%-10s%-12s---> %-15s|", "Name:", products[counter].name, name);
						}
						if (newprice) {
							printf("\n       |%-10s%-12.2lf---> %-15.2lf|", "Price:", products[counter].price, price);
						}
						if (newquantity) {
							printf("\n       |%-10s%-12d---> %-15d|", "Quantity:", products[counter].quantity, quantity);
						}

						printf("\n       --------------------------------------------\n       |               SUBMIT?(Y/N)               |\n       --------------------------------------------");
					}
					else {
						return;
					}
					*KeyPressed = _getch();
					if (*KeyPressed == y || *KeyPressed == Y) {
						if (newname) {
							strcpy_s(products[counter].name, (unsigned int)sizeof(products[counter].name), name);
						}
						if (newprice) {
							products[counter].price = price;
						}
						if (newquantity) {
							products[counter].quantity = quantity;
						}
						if (newid) {
							strcpy_s(products[counter].ID, (unsigned int)sizeof(products[counter].ID), id);
						}

						printf("\n\nSuccessfully saved changes.press ANY key to continue...");

						_getch();
						newname = 0, newprice = 0, newquantity = 0, newid = 0;
						break;
					}

				}
			}
		}
		else if (foundweight) {
			foundweight = 0;
			nextscreen(KeyPressed, position);
			while (1) {
				system("cls");
				if (productsW[counter].weight >= 1000) {
					printf("       ---------- EDIT ITEMS ----------\n\n%-15s|%-30s|%-15s|%-15s\n-------------------------------------------------------------------------------\n%-15s|%-30s|%-15.2lf|%-5.2lf\n\n\n", "ID", "NAME", "PRICE", "WEIGHT", productsW[counter].ID, productsW[counter].name, productsW[counter].price, productsW[counter].weight / 1000);
				}
				else {
					printf("       ---------- EDIT ITEMS ----------\n\n%-15s|%-30s|%-15s|%-15s\n-------------------------------------------------------------------------------\n%-15s|%-30s|%-15.2lf|%-5.2lf\n\n\n", "ID", "NAME", "PRICE", "WEIGHT", productsW[counter].ID, productsW[counter].name, productsW[counter].price, productsW[counter].weight);
				}


				if (*position > 5) {
					*position = 1;
				}
				else if (*position < 1) {
					*position = 5;
				}
				if (*position == 1) {
					printf("\n\n\n=>(ID)       NAME       PRICE       WEIGHT       RETURN ");
				}
				else if (*position == 2) {
					printf("\n\n\n  ID     =>(NAME)       PRICE       WEIGHT       RETURN ");
				}
				else if (*position == 3) {
					printf("\n\n\n  ID       NAME     =>(PRICE)       WEIGHT       RETURN ");
				}
				else if (*position == 4) {
					printf("\n\n\n  ID       NAME       PRICE     =>(WEIGHT)       RETURN ");
				}
				else if (*position == 5) {
					printf("\n\n\n  ID       NAME       PRICE       WEIGHT     =>(RETURN)");
				}
				*KeyPressed = _getch();
				if (*KeyPressed == 0 || *KeyPressed == 224) {
					*KeyPressed = _getch();
					if (*KeyPressed == right) {
						*position += 1;
					}
					else if (*KeyPressed == left) {
						*position -= 1;
					}
				}
				

				int found = 0;
				if (*KeyPressed == enter && *position == 1) {
					printf("\n\nEnter a new ID for the item > ");
					scanf_s("%s", id, (unsigned int)sizeof(id));
					for (int j = 0; j < weighted_item_counter; j++) {
						if (strcmp(id, productsW[j].ID) == 0 && j!=counter) {
							found = 1;
							break;
						}
					}

					if (found) {
						printf("\n\nitem with the same ID exists! Press ANY key to continue...");
						_getch();
						continue;
					}
					newid = 1;
					continue;
				}
				else if (*KeyPressed == enter && *position == 2) {
					printf("\n\nEnter new name for the item > ");
					scanf_s("%s", name, (unsigned int)sizeof(name));
					for (int j = 0; j < weighted_item_counter; j++) {
						if (strcmp(name, productsW[j].name) == 0&&j!=counter) {
							found = 1;
							break;
						}
					}

					if (found) {
						printf("\n\nitem with the same name exists! Press ANY key to continue...");
						_getch();
						continue;
					}
					newname = 1;
					continue;
				}
				else if (*KeyPressed == enter && *position == 3) {
					printf("\n\nEnter new price for the item > ");
					scanf_s("%lf", &price);
					if (price <= 0) {
						printf("\nPrice cannot be under or equal zero! Press ANY key to continue...");
						_getch();
						continue;
					}
					newprice = 1;
					continue;
				}
				else if (*KeyPressed == enter && *position == 4) {
					printf("\n\nEdit the available weight for the item > ");
					scanf_s("%lf", &weight);
					if (weight < 0) {
						printf("Weight cannot be under zero! Press ANY key to continue...");
						_getch();
						continue;
					}
					newweight = 1;
					continue;
				}
				else if (*KeyPressed == enter && *position == 5) {
					if (newname || newprice || newweight||newid) {
						printf("\n       --------------------------------------------\n       |               EDITS SUMMARY              |\n       --------------------------------------------");
						if (newid) {
							printf("\n       |%-10s%-12s---> %-15s|", "ID:", productsW[counter].ID, id);
						}
						if (newname) {
							printf("\n       |%-10s%-12s---> %-15s|", "Name:", productsW[counter].name, name);
						}
						if (newprice) {
							printf("\n       |%-10s%-12.2lf---> %-15.2lf|", "Price:", productsW[counter].price, price);
						}
						if (newweight) {
							if (weight > 1000) {
								printf("\n       |%-10s%-12.2lf---> %-13.2lf%-2s|", "Weight:", productsW[counter].weight, weight / 1000, "KG");
							}
							else {
								printf("\n       |%-10s%-12.2lf---> %-13.2lf%-2s|", "Weight:", productsW[counter].weight, weight, "g");
							}

						}

						printf("\n       --------------------------------------------\n       |               SUBMIT?(Y/N)               |\n       --------------------------------------------");
					}
					else {
						return;
					}
					*KeyPressed = _getch();
					if (*KeyPressed == y || *KeyPressed == Y) {
						if (newname) {
							strcpy_s(productsW[counter].name, (unsigned int)sizeof(productsW[counter].name), name);
						}
						if (newprice) {
							productsW[counter].price = price;
						}
						if (newweight) {
							productsW[counter].weight = weight;
						}
						if (newid) {
							strcpy_s(productsW[counter].ID, (unsigned int)sizeof(productsW[counter].ID), id);
						}

						printf("\n\nSuccessfully saved changes.press ANY key to continue...");

						_getch();
						newname = 0, newprice = 0, newweight = 0, newid = 0;
						break;
					}

				}
			}
		}
}



int main() {
	FILE* fptr;
	int quantity_item_counter = 0,weighted_item_counter = 0, position = 1, KeyPressed = 0, CustomerMode = 1, ManagerMode = 0, nameisput = 0, passisput = 0, created = 0;
	struct ManagerAccount accountM[99] = { 0 };
	struct CustomerAccount accountC[99] = { 0 };
	struct InventoryItems products[1000] = { 0 };
	struct WeightedItems productsW[1000] = { 0 };

	SaveInventory(products, &quantity_item_counter,&weighted_item_counter,productsW);
	startupmessage();

	while (1) {

			while (KeyPressed != enter) {
				MenuScreen(position);
				KeyPressed = _getch();
				if (KeyPressed == 0 || KeyPressed == 224) {
					KeyPressed = _getch();
					if (KeyPressed == 75) {
						position = 1;
						CustomerMode = 1;
						ManagerMode = 0;
					}
					else if (KeyPressed == 77) {
						position = 2;
						CustomerMode = 0;
						ManagerMode = 1;

					}
				}
			}


			nextscreen(&KeyPressed, &position);

			if (ManagerMode) {
				while (KeyPressed != 13) {
					AccountAccess(position, ManagerMode, CustomerMode, KeyPressed);
					KeyPressed = _getch();
					
					if (KeyPressed == 0 || KeyPressed == 224) {
						KeyPressed = _getch();
						if (KeyPressed == 75) {
							position = 1;
						}
						else if (KeyPressed == 77) {
							position = 2;
						}
						
					}
				}

			}
			else if (CustomerMode) {
				while (KeyPressed != 13) {
					AccountAccess(position, ManagerMode, CustomerMode, KeyPressed);
					KeyPressed = _getch();

					

					if (KeyPressed == 0 || KeyPressed == 224) {
						KeyPressed = _getch();
						if (KeyPressed == 75) {
							position = 1;
						}
						else if (KeyPressed == 77) {
							position = 2;
						}
					}
				}
			}

			system("cls");
			KeyPressed = 0;

			if (position == 1) {
				while (nameisput == 0 && passisput == 0 && KeyPressed != 13) {
					signup(position, ManagerMode, CustomerMode, KeyPressed, &accountM[0], &nameisput, &passisput, &accountC[0]);
				}
			}

			if (position == 2) {
				while (nameisput == 0 && passisput == 0 && KeyPressed != 13) {
					login(position, ManagerMode, CustomerMode, KeyPressed, &accountM[0], &nameisput, &passisput, &accountC[0]);
				}
			}
	
	

	nextscreen(&KeyPressed, &position);

	
	if (ManagerMode) {
		while (1) {
			ManagerDashboard(&position, &accountM[0],KeyPressed);
			KeyPressed = _getch();

			if (KeyPressed == 0 || KeyPressed == 224) {
				KeyPressed = _getch();
				if (KeyPressed == down) {
					position += 1;
				}
				else if (KeyPressed == up) {
					position -= 1;
				}
			}
			else if (KeyPressed == enter && position == 1){
				while (KeyPressed != q && KeyPressed != Q) {
					inventory(&KeyPressed, quantity_item_counter, weighted_item_counter, products, productsW, &position);
				}
					
			}
			else if (KeyPressed == enter && position == 2) {

				nextscreen(&KeyPressed, &position);
				createitem(position, KeyPressed,&created);
				if (created) {
					created = 0;
					SaveInventory(products, &quantity_item_counter,&weighted_item_counter,productsW);
					while (KeyPressed != q && KeyPressed != Q) {
						inventory(&KeyPressed, quantity_item_counter, weighted_item_counter, products, productsW, &position);
					}
				}
				
				
			}
			else if (KeyPressed == enter && position == 3) {
				while (1) {
					EditItem(&position, &KeyPressed, products, productsW,quantity_item_counter,weighted_item_counter);
					if (KeyPressed == n || KeyPressed == N) {
						if (fopen_s(&fptr, "inventory.txt", "w") == 0) {
							for (int counter = 0; counter < quantity_item_counter; counter++) {
								fprintf(fptr, "%s %s %.2lf %d\n", products[counter].ID, products[counter].name, products[counter].price, products[counter].quantity);
							}
							fclose(fptr);
						}
						
						if (fopen_s(&fptr, "weighteditems.txt", "w") == 0) {
							for (int counter = 0; counter < weighted_item_counter; counter++) {
								fprintf(fptr, "%s %s %.2lf %.2lf\n", productsW[counter].ID, productsW[counter].name, productsW[counter].price, productsW[counter].weight);
							}
							fclose(fptr);
						}
						break;
					}
				}
			}
			else if (KeyPressed == enter && position == 4) {
				printf("  Are you sure?(Y/N)");
				KeyPressed = _getch();
				if (KeyPressed == Y || KeyPressed == y) {
					nextscreen(&KeyPressed, &position);
					ManagerMode = 0;
					nameisput = 0;
					passisput = 0;
					break;
				}
				else {
					continue;
				}
				
			}
		}
	}
















}// the while loop that holds the whole program together
	printf("Demo end last position %d", position);

	return 0;
}