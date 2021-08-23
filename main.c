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
void view_users(); // users table view
int get_user_id(); // Get id of user to delete
int user_id_auto_increment();
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
        printf("3. Delete user\n");
        printf("4. Add Book\n");
        printf("5. Exit\n");
        printf("Select action(1-5): ");
        scanf("%d",&action);
        // validate input
        if (action < 1 || action > 5) {
            printf("Invalid action. Try again\n");
            Sleep(2000);
            system("cls");
        }

    } while(action < 1 || action > 5);

    return action;
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
        delete_user();
        break;
    case 4:
        printf("Adding a book\n");
        break;
    case 5:
        close();
        break;
    default:
        printf("Unknown action. \n");

    }

}

int user_id_auto_increment()
{
    struct user u;
    FILE *fp;
    int id, max = 1000;

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("\nSelect User to delete:\n");

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id > max)
            max = u.id;
    }
    fclose(fp);
    id = ++max;
    return id;

}

/*
    A function to add a new user and save to a file
    Doesn't return anything
    Requires no parameters
*/

void add_user() {
    struct user u;
    FILE *fp;

    u.id = user_id_auto_increment();
    if ((fp = fopen("users","ab"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("Name: ");
    getchar();
    gets(u.name);
    printf("Phone Number: ");
    gets(u.tel);
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

int get_user_id()
{
    struct user u;
    FILE *fp;
    int id;

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("\nSelect User to delete:\n");

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        printf("%8d.\t%s\n",u.id,u.name);
    }
    fclose(fp); // close file
    printf("Enter user id: ");
    scanf("%d",&id);

    return id;
}

void delete_user()
{
    struct user u;
    FILE *fp,*fp1;
    int id;

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    // check if file open is successful
    if ((fp1 = fopen("users_tmp","ab"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    id = get_user_id();

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id == id) continue;
        fwrite(&u, sizeof(struct user), 1, fp1);
    }

    fclose(fp); // close file
    fclose(fp1);

    if(remove("users") == 0) {
        if(rename("users_tmp","users") == 0)
            printf("User Deleted successfully. \n");
        else
            printf("Could not rename temporary file\n");
    }
    else {
        printf("Could not delete old file. \n");
    }
}
