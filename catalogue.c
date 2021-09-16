#include "header.h"
struct catalogue {
    int id;
    char type[50];
    char ISBN[100];
    char ISSN[100];
    char title[100];
    char author[100];
    char sub_heading[100];
    char keyword[50];
    char call_number[20];
};

void catalogue() {
    int action;
    while(1) {
        if(!IS_LOGGED_IN) {
            login_user();
        }
        action = catalogue_menu();
        execute_catalogue_action(action);
        printf("\nPress any key to continue");
        getch();
        system("cls");
    }
}

int catalogue_menu() {
    // Navigation menu
    int action;
    do {
        system("cls");
        printf("\n\tCounty Library Management System!\n");
        str_capitalize(LOGGED_IN_USER.salutation);
        str_capitalize(LOGGED_IN_USER.name);
        printf("Welcome %s. %s\n",LOGGED_IN_USER.salutation,LOGGED_IN_USER.name);
        printf("1. Add Item\n");
        printf("2. View items\n");
        printf("3. Delete item\n");
        printf("4. Update item\n");
        printf("5. Search item\n");
        printf("6. Go back\n");
        printf("7. Log out\n");
        printf("8. Exit\n");
        printf("Select action(1-8): ");
        scanf("%d",&action);
        // validate input
        if (action < 1 || action > 8) {
            printf("Invalid action. Try again\n");
            Sleep(2000);
            system("cls");
        }

    } while(action < 1 || action > 8);

    return action;
}

void execute_catalogue_action(int action) {
    switch(action) {
    case 1:
        add_item();
        break;
    case 2:
        view_items();
        break;
    case 3:
        delete_item();
        break;
    case 4:
        update_item();
        break;
    case 5:
        search_item();
        break;
    case 6:
        main();
        break;
    case 7:
        logout();
        break;
    case 8:
        close();
        break;
    default:
        printf("Unrecognized action. \n");

    }

}

void add_item()
{
    printf("adding book now...");
}

void view_items()
{
    printf("\t LIST OF ITEMS\n");
}

void delete_item()
{
    printf("Deleting item...");
}

void update_item()
{
    printf("updating item..");
}

void search_item()
{
    printf("Searching item...");
}

