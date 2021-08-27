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
    char email[50];
    int is_staff;
    char added_on[80];
    char dob[12];
    char gender[20];
    char initials[10];
    char salutation[5];
    char password[20];
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

// Helper functions
char* get_timestamp();
void str_to_lower(char* str);
void str_to_upper(char* str);
void str_capitalize(char* str);
char* get_salutation();
char* get_gender();
char* set_password();
char* get_initial_password(char *name);

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
    strcpy(u.added_on,get_timestamp());

    if ((fp = fopen("users","ab"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("Name: ");
    getchar();
    gets(u.name);
    printf("Initials: ");
    gets(u.initials);
    p = get_salutation();
    strcpy(u.salutation,p);
    p = get_gender();
    strcpy(u.gender,p);
    printf("Phone Number: ");
    getchar();
    gets(u.tel);
    printf("Email: ");
    gets(u.email);
    printf("User type(1 for staff, 0 for ordinary user: ");
    scanf("%d",&u.is_staff);
    p = get_initial_password(u.name);
    strcpy(u.password,p);

    fwrite(&u, sizeof(struct user), 1, fp);
    fclose(fp);
    printf("User successfully added\n");
    printf("Initial Password (kindly write it down): %s\n",u.password);
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

    str_to_lower(term);

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("\n\tLIST OF USERS\n\n");
    int count;
    for(count = 0;count<150;count++) printf("_"); // print 65 underscores/underline
    printf("\n");
    printf("|%8s| %11s| %20s| %6s| %13s| %13s| %30s| %8s| %20s|\n","ID","SALUTATION","NAME","INITIALS","GENDER","PHONE","EMAIL","USER TYPE","ADDED ON");
    for(count = 0;count<150;count++) printf("_");
    printf("\n");

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id == uid ) continue;
        uid = u.id;
        char id[30],is[2];
        itoa(u.id,id,10);
        itoa(u.is_staff,is,10);
        str_to_lower(u.name);
        str_to_lower(u.initials);
        str_to_lower(u.email);
        if(!(strcmp(id,term) == 0 || strstr(u.salutation,term) || strstr(u.name,term) || strstr(u.initials,term) || strstr(u.tel,term) || strstr(u.email,term) || strcmp(is,term) == 0 || strcmp(u.gender,term) == 0)) continue;

        str_capitalize(u.salutation);
        str_capitalize(u.name);
        str_to_upper(u.initials);
        str_capitalize(u.gender);

        printf("|%8d| ",u.id);
        printf("%11s| ",u.salutation);
        printf("%20s|   ",u.name);
        printf("%6s| ",u.initials);
        printf("%13s| ",u.gender);
        printf("%13s| ",u.tel);
        printf("%30s| ",u.email);
        if(u.is_staff)
            printf("Staff    | ");
        else
            printf("Standard | ");
        printf("%20s|\n",u.added_on);
    }
    for(count = 0;count<150;count++) printf("_");
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
    char *p;
    while(1) {
            do{
                printf("Select attribute to edit: \n");
                printf("1. Salutation: %s\n",u.salutation);
                printf("2. Name: %s\n",u.name);
                printf("3. Initials: %s\n",u.initials);
                printf("4. Gender: %s\n",u.gender);
                printf("5. Phone: %s\n",u.tel);
                printf("6. Email: %s\n",u.email);
                printf("7. User type: ");
                if(u.is_staff)
                    printf("Staff\n");
                else
                    printf("Standard\n");

                printf("8. Reset Password\n");
                printf("9. Done\n");
                printf("Attribute: ");
                scanf("%d",&attr);
                if(attr < 1 || attr > 9) {
                    printf("Invalid attribute. Try again\n");
                    Sleep(1000);
                    system("cls");
                }
            } while(attr < 1 || attr > 9);
            getchar();
            switch(attr) {
            case 1:
                printf("New Salutation\n");
                p = get_salutation();
                strcpy(u.salutation,p);
                break;
            case 2:
                printf("New Name: ");
                gets(u.name);
                break;
            case 3:
                printf("New Initials: ");
                gets(u.initials);
                break;
            case 4:
                printf("New Gender\n");
                p = get_salutation();
                strcpy(u.gender,p);
                break;
            case 5:
                printf("New Phone no.: ");
                gets(u.tel);
                break;
            case 6:
                printf("New Email: ");
                gets(u.email);
                break;
            case 7:
                printf("New user status(1 for staff, 0 for standard): ");
                scanf("%d",&u.is_staff);
                break;
            case 8:
                p = get_initial_password(u.name);
                strcpy(u.password,p);
                printf("Password reset successful \n");
                printf("New Password(kindly write down): %s\n",u.password);
                break;
            case 9:
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

void str_to_lower(char* str) {
    int size = strlen(str);
    int i;

    for(i = 0; i < size; i++) {
        str[i] = tolower(str[i]);
    }
}

void str_to_upper(char* str) {
    int size = strlen(str);
    int i;

    for(i = 0; i < size; i++) {
        str[i] = toupper(str[i]);
    }
}

void str_capitalize(char* str) {
    int size = strlen(str);;
    int i;

    for(i = 0; i < size; i++) {
        if(i == 0) {
            str[i] = toupper(str[i]);
            continue;
        }
        if(str[i-1] == 32 ) {
            str[i] = toupper(str[i]);
            continue;
        }

        str[i] = tolower(str[i]);
    }
}

char* get_salutation() {
    int choice;
    char salutation[20];
    do {
        printf("Salutation:\n");
        printf("1. Mr.\n");
        printf("2. Mrs.\n");
        printf("3. Miss.\n");
        printf("4. Ms.\n");
        printf("Selection: ");
        scanf("%d",&choice);
        switch(choice) {
        case 1:
            strcpy(salutation,"mr");
            break;
        case 2:
            strcpy(salutation,"mrs");
            break;
        case 3:
            strcpy(salutation,"miss");
            break;
        case 4:
            strcpy(salutation,"ms");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }while(choice < 1 || choice > 4);

    return salutation;

}
char* get_gender(){
    int choice;
    char gender[20];
    do {
        printf("Gender:\n");
        printf("1. Male.\n");
        printf("2. Female.\n");
        printf("3. Other.\n");
        printf("4. Don't want to say.\n");
        printf("Selection: ");
        scanf("%d",&choice);
        switch(choice) {
        case 1:
            strcpy(gender,"male");
            break;
        case 2:
            strcpy(gender,"female");
            break;
        case 3:
            strcpy(gender,"other");
            break;
        case 4:
            strcpy(gender,"not specified");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }while(choice < 1 || choice > 4);

    return gender;
}

char* set_password()
{
    char pass[30],confirm_pass[30];
    char ch;
    int i = 0;

    do {
        printf("Enter password: ");
        while(1) {
            ch = getch();
            if(ch == '\r') break;
            if(ch == 32) continue;
            pass[i] = ch;
            printf("*");
            i++;
        }

        i = 0;
        printf("\nConfirm password: ");
        while(i < 30) {
            ch = getch();
            if(ch == '\r') break;
            if(ch == 32) continue;
            confirm_pass[i] = ch;
            printf("*");
            i++;
        }

        if(strcmp(pass,confirm_pass)) {
            printf("\nPasswords Do not match.\n");
            printf("Enter c to try again or x to exit. \n");
            ch = getch();
            system("cls");
            if(ch == 'x') break;
        }
        else {
            printf("\nPassword set Successfully");
        }
    } while(strcmp(pass,confirm_pass));

    return pass;

}

char* get_initial_password(char *name)
{
    char pass[30];
    int size = strlen(name);
    int i;
    for(i = 0; i < size ; i++) {
        if(name[size - i - 1] == 32) {
            pass[i] = tolower(name[size - i - 2]);
            break;
        }
        pass[i] = tolower(name[size - i - 1]);
    }
    return pass;
}
