/*-----------------------------------
 Project:  Library Management System
 Author:   Titus Njiru
 Date:     July, 2021
 Compiler: C99
 License:  MIT
-----------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

// Data structures

struct user {
    int id;
    char name[100];
    char tel[13];
    int is_staff;
};

// function prototypes
void execute_action(int action);
void close();
int menu();
void add_user();
void view_users();

int main()
{
    int action;
    while(1) {
        action = menu();
        execute_action(action);
        printf("Press any key to continue");
        getchar();
        getch();
        system("cls");
    }

    return 0;
}



void execute_action(int action) {
    switch (action) {
    case 1:
        add_user();
        break;
    case 2:
        view_users();
        break;
    case 3:
        printf("adding book\n");
        break;
    case 4:
        close();
        break;
    default:
        printf("Sorry. I don't know how to execute that\n");
    }

}

void close() {
    printf("Thank for you using the system.");
    Sleep(5000);
    exit(0);
}

int menu() {
    int action;

    do {
        printf("\tCommunity Library System\n");
        printf("Welcome Mr. Titus\n");
        printf("1. Add user\n");
        printf("2. View all users\n");
        printf("3. Add book\n");
        printf("4. Exit\n");
        printf("Action(1-4): ");
        scanf("%d",&action);
        // validate
        if (action < 1 || action > 4) {
            printf("Invalid action.Try again\n");
            Sleep(2000);
            system("cls");
        }
    } while(action < 1 || action > 4);

    return action;
}

void add_user() {
    struct user u;
    FILE *fp;

    fp = fopen("users","ab");
    if (!fp) {
        printf("Unable to open file");
        exit(0);
    }

    printf("Name: ");
    getchar();
    gets(u.name);
    printf("Phone number: ");
    scanf("%s",&u.tel);
    printf("ID: ");
    scanf("%d",&u.id);
    printf("User type(1 for staff, 0 for ordinary user:");
    scanf("%d",&u.is_staff);

    fwrite(&u, sizeof(struct user), 1, fp);
    printf("User added successfully\n");
    fclose(fp);

}

void view_users() {
    struct user u;
    FILE *fp;

    fp = fopen("users","rb");
    if (!fp) {
        printf("Unable to open file");
        exit(0);
    }
    printf("id\t\tName\t\t\t\tPhone Number Is Staff\n");
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        printf("%8d %20s %13s %1d\n",u.id,u.name,u.tel,u.is_staff);
    }
    fclose(fp);
}
