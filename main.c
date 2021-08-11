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
#include <conio.h>

// Adding user:
// name
// id
// contact
// is_staff

struct user {
    char name[100];
    int id;
    char tel[13];
    int is_staff;
};



// Function prototype
void execute_action(int action);
void close();
int menu();
void add_user();
void view_users();
void delete_user(); //TODO
void update_user(); //TODO

int main()
{
    int action;
    while(1) {
        action = menu();
        execute_action(action);
        printf("\nPress any key to continue");
        getch();
        system("cls");
    }

    return 0;
}

void execute_action(int action) {
    switch(action) {
    case 1:
        add_user();
        break;
    case 2:
        view_users();
        break;
    case 3:
        printf("Adding a book\n");
        break;
    case 4:
        close();
        break;
    default:
        printf("Unknown action. \n");

    }

}

void close() {
    printf("Thank you for using the system\n");
    printf("Bye\n");
    Sleep(2000);
    exit(0);
}

int menu() {
    // Navigation menu
    int action;
    do {
        printf("\tCounty Library Management System!\n");
        printf("Welcome Titus\n");
        printf("1. Add user\n");
        printf("2. View users\n");
        printf("3. Add Book\n");
        printf("4. Exit\n");
        printf("Select action(1-4): ");
        scanf("%d",&action);
        // validate input
        if (action < 1 || action > 4) {
            printf("Invalid action. Try again\n");
            Sleep(2000);
            system("cls");
        }

    } while(action < 1 || action > 4);

    return action;
}

/*
    A function to add a new user and save to a file
    Doesn't return anything
    Requires no parameters
*/

void add_user() {
    struct user u;
    FILE *fp;
    if ((fp = fopen("users","ab"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("Name: ");
    getchar();
    gets(u.name);
    printf("ID number: ");
    scanf("%d",&u.id);
    printf("Phone Number: ");
    scanf("%s",&u.tel);
    printf("User type(1 for staff, 0 for ordinary user: ");
    scanf("%d",&u.is_staff);
    fwrite(&u, sizeof(struct user), 1, fp);
    fclose(fp);
    printf("User successfully added\n");
}

/*
    A function to print a list of all users from a file to screen
    Doesn't return anything
    Requires no parameters
*/

void view_users() {
    struct user u;
    FILE *fp;

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("\n\tLIST OF USERS\n\n");
    int count;
    for(count = 0;count<65;count++) printf("_"); // print 65 underscores/underline
    printf("\n");
    printf("|%8s|\t%20s|\t%10s|\t%8s|\n","ID","NAME","PHONE","IS STAFF");
    for(count = 0;count<65;count++) printf("_");
    printf("\n");

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        printf("|%8d|\t",u.id);
        printf("%20s|\t",u.name);
        printf("%8s|\t",u.tel);
        printf("%8d|\n",u.is_staff);
    }
    for(count = 0;count<65;count++) printf("_");
    printf("\n");
    fclose(fp); // close file

}
