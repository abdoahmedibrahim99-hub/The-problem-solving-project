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
// Manager account 
struct ManagerAccount {
	char username[999];
	char password[999];

};

struct CustomerAccount {
	char username[999];
	char password[999];

};


// ++++++++ SHORTCUT COMMANDS +++++++

// nextscreen is used to reset the values of input so it doesnt stay the same from the previous screen
void nextscreen(int *KeyPressed,int *position) {
	system("cls");
	*KeyPressed = 0;
	*position = 1;
}


// ++++++++ SCREENS ++++++++++
// MENU STARTUP SCREEN
void MenuScreen(int position) {
	system("cls");
	printf("            -------------- Select mode to enter --------------\n\n\n");
	printf("            +-----------------+       +----------------+\n");
	
	if (position == 1) {
		printf("            | =>Customer mode |       |  Manager Mode  |\n");
		printf("            +-----------------+       +----------------+");

	}
	else if (position == 2) {
		printf("            |  Customer mode  |       | =>Manager Mode |\n");
		printf("            +-----------------+       +----------------+");
	}

}

// Create account or log in screen
void AccountAccess(int position,int ManagerMode,int CustomerMode) {
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
	char storedName[999];
	char storedPass[999];
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
		printf("            +----------------------------------------+\n\n            >");
		scanf_s("%d", &pin);

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
					printf("\nAccount with the same name already exists! press R to try again");
					KeyPressed = _getch();
					if (KeyPressed == 'r' || KeyPressed == 'R') {
						*passisput = 0, * nameisput = 0;
						return;
					}
				}
				else {
					fopen_s(&fptr, "managers_accounts.txt", "a");
					fprintf(fptr, "\n%s %s", accountM->username, accountM->password);
					fclose(fptr);
				}
			}
		}else {
			printf("    Error: the pin is incorrect.Press R key to try again...");
			KeyPressed = _getch();
			if (KeyPressed == 'r' || KeyPressed == 'R') {
				*passisput = 0, * nameisput = 0;
				return;
			}
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
				printf("\nAccount with the same name already exists! press R to try again...");
				KeyPressed = _getch();
				if (KeyPressed == 'r' || KeyPressed == 'R') {
					*passisput = 0, * nameisput = 0;
					return;
				}
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
		printf("            |              Enter signup pin          |\n");
		printf("            +----------------------------------------+\n\n            >");
		scanf_s("%d", &pin);

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
				return;
			}
			else {
				FILE* fptr;
				char storedName[999];
				char storedPass[999];
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
					printf("\nInvalid Username or Password. Press R key to try again...");
					KeyPressed =_getch();
					if (KeyPressed == 'r' || KeyPressed == 'R') {
					*nameisput = 0;
					*passisput = 0;
					return;
					}
					
				}
			}
		}
		else {
			printf("    Error: the pin is incorrect.Press R key to try again");
			KeyPressed = _getch();
			if (KeyPressed == 'r' || KeyPressed == 'R') {
				*passisput = 0, * nameisput = 0;
				return;
			}
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
			char storedName[999];
			char storedPass[999];
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
				printf("\nLogin Successful! Press any key to continue...");
				_getch();
				return;
			}
			else {
				printf("\nInvalid Username or Password. Press R key to try again....");
				KeyPressed = _getch();
				if (KeyPressed == 'R' || KeyPressed == 'r') {
				*nameisput = 0;
				*passisput = 0;
				return;
				}
				
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
void ManagerDashboard(int position, struct ManagerAccount* accountM) {
	system("cls");

	printf("       ---------- MANAGER DASHBOARD ----------\nWelcome,%s!\n\n\n\n\nPress Q to end demo", accountM->username);
}

int main() {
	int position = 1, KeyPressed = 0, CustomerMode = 1, ManagerMode = 0, nameisput = 0, passisput = 0;
	struct ManagerAccount accountM[99];
	struct CustomerAccount accountC[99];

	while (KeyPressed != 13) {
		MenuScreen(position);
		KeyPressed = _getch();
		if (KeyPressed == 0|| KeyPressed == 224) {
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
	
	nextscreen(&KeyPressed,&position);

	if (ManagerMode) {
		while (KeyPressed != 13) {
			AccountAccess(position, ManagerMode, CustomerMode);
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
			AccountAccess(position, ManagerMode, CustomerMode);
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
		while (nameisput ==0 && passisput == 0 && KeyPressed != 13) {
			signup(position, ManagerMode, CustomerMode,KeyPressed,&accountM[0],&nameisput,&passisput,&accountC[0]);
		}
	}

	if (position == 2) {
		while (nameisput == 0 && passisput == 0 && KeyPressed != 13) {
			login(position, ManagerMode, CustomerMode, KeyPressed, &accountM[0], &nameisput, &passisput, &accountC[0]);
		}
	}

	nextscreen(&KeyPressed, &position);

	if (CustomerMode) {
		while (1) {
			CustomerDashboard(position, &accountC[0]);
			KeyPressed = _getch();
			if (KeyPressed == 'q' || KeyPressed == 'Q');
			break;
		}
	}
	else if (ManagerMode) {
		while (1) {
			ManagerDashboard(position, &accountM[0]);
			KeyPressed = _getch();
			if (KeyPressed == 'q' || KeyPressed == 'Q');
			break;
		}
	}
	printf("Demo end last position %d", position);

	return 0;
}