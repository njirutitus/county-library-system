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
#include <time.h>
#include <locale.h>

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
    char added_on[80];
};



// Function prototype
void execute_action(int action);
void close();
int menu();

void add_user();
void view_users(); // users table view
int get_user_id(); // Get id of user to delete
int user_id_auto_increment();
void delete_user();
struct user get_updated_user(struct user u);
void update_user();
void search_user();
char* get_timestamp();

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
        printf("4. Update user\n");
        printf("5. Search user\n");
        printf("6. Add Book\n");
        printf("7. Exit\n");
        printf("Select action(1-7): ");
        scanf("%d",&action);
        // validate input
        if (action < 1 || action > 7) {
            printf("Invalid action. Try again\n");
            Sleep(2000);
            system("cls");
        }

    } while(action < 1 || action > 7);

    return action;
}

void execute_action(int action) {
    switch(action) {
    case 1:
        add_user();
        break;
    case 2:
        view_users("");
        break;
    case 3:
        delete_user();
        break;
    case 4:
        update_user();
        break;
    case 5:
        search_user();
        break;
    case 6:
        printf("Adding a book\n");
        break;
    case 7:
        close();
        break;
    default:
        printf("Unrecognized action. \n");

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
    char *p;

    u.id = user_id_auto_increment();
    p = get_timestamp();
    strcpy(u.added_on,p);
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

void view_users(char term[100]) {
    struct user u;
    FILE *fp;
    int uid=0;

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("\n\tLIST OF USERS\n\n");
    int count;
    for(count = 0;count<93;count++) printf("_"); // print 65 underscores/underline
    printf("\n");
    printf("|%8s|\t%20s|\t%13s|\t%8s|\t%20s|\n","ID","NAME","PHONE","USER TYPE","ADDED ON");
    for(count = 0;count<93;count++) printf("_");
    printf("\n");

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id == uid ) continue;
        uid = u.id;
        char id[30],is[2];
        itoa(u.id,id,10);
        itoa(u.is_staff,is,10);
        if(!(strcmp(id,term) == 0 || strstr(u.name,term) || strstr(u.tel,term) || strcmp(is,term) == 0)) continue;
        printf("|%8d|\t",u.id);
        printf("%20s|\t",u.name);
        printf("%13s|\t",u.tel);
        if(u.is_staff)
            printf("Staff    |\t");
        else
            printf("Standard |\t");
        printf("%20s|\n",u.added_on);
    }
    for(count = 0;count<93;count++) printf("_");
    printf("\n");
    fclose(fp); // close file

}

int get_user_id()
{
    struct user u;
    FILE *fp;
    int id,uid=0;

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id == uid ) continue;
        uid = u.id;
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

    printf("\nSelect User to delete:\n");
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

void update_user()
{
    struct user u;
    FILE *fp,*fp1;
    int id,uid=0;

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

    printf("\nSelect User to Update:\n");
    id = get_user_id();

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id == uid ) continue;
        uid = u.id;
        if(u.id == id) u = get_updated_user(u);
        fwrite(&u, sizeof(struct user), 1, fp1);
    }

    fclose(fp); // close file
    fclose(fp1);

    if(remove("users") == 0) {
        if(rename("users_tmp","users") == 0)
            printf("User Updated successfully. \n");
        else
            printf("Could not rename temporary file\n");
    }
    else {
        printf("Could not delete old file. \n");
    }
}

struct user get_updated_user(struct user u)
{
    int attr;
    while(1) {
            do{
                printf("Select attribute to edit: \n");
                printf("1. Name: %s\n",u.name);
                printf("2. Phone: %s\n",u.tel);
                printf("3. User type: ");
                if(u.is_staff)
                    printf("Staff\n");
                else
                    printf("Standard\n");

                printf("4. Done\n");
                printf("Attribute: ");
                scanf("%d",&attr);
                if(attr < 1 || attr > 4) {
                    printf("Invalid attribute. Try again\n");
                    Sleep(1000);
                    system("cls");
                }
            } while(attr < 1 || attr > 4);
            getchar();
            switch(attr) {
            case 1:
                printf("New Name: ");
                gets(u.name);
                break;
            case 2:
                printf("New Phone no.: ");
                gets(u.tel);
                break;
            case 3:
                printf("New user status(1 for staff, 0 for standard): ");
                scanf("%d",&u.is_staff);
                break;
            case 4:
                return u;
            default:
                printf("Invalid attribute.\n");
                break;
            }
    }

    return u;


}

void search_user()
{
    char term[100];
    printf("SEARCH USER\n");
    printf("Value: ");
    getchar();
    gets(term);
    view_users(term);
}

char* get_timestamp()
{
    time_t rawtime;
    struct tm * timeinfo;
    char *buffer;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strftime(buffer,80,"%d/%m/%Y %H:%Mh", timeinfo);

    return (buffer);
}
