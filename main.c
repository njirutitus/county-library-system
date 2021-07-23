/*-----------------------------
* Version: C99                *
* Project: Library management *
* Author:  Titus Njiru        *
* Date:    June,2021          *
* License: MIT                *
******************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>

// Function prototype
void execute_action(int action);
void close();
int menu();

int main()
{
    int action;
    action = menu();
    execute_action(action);

    return 0;
}

void execute_action(int action) {
    switch(action) {
    case 1:
        printf("Adding a user\n");
        break;
    case 2:
        printf("Adding a book\n");
        break;
    case 3:
        close();
        break;
    default:
        printf("Unknown action. \n");

    }

}

void close() {
    printf("Thank you for using the system\n");
    printf("Bye\n");
    Sleep(5000);
    exit(0);
}

int menu() {
    // Navigation menu
    int action;
    do {
        printf("\tCounty Library Management System!\n");
        printf("Welcome Titus\n");
        printf("1. Add user\n");
        printf("2. Add Book\n");
        printf("3. Exit\n");
        printf("Select action(1-3): ");
        scanf("%d",&action);
        // validate input
        if (action < 1 || action > 3) {
            printf("Invalid action. Try again\n");
            Sleep(2000);
            system("cls");
        }

    } while(action < 1 || action > 3);

    return action;
}
