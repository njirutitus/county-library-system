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
    char added_on[80];
};

// function prototypes
int item_id_auto_increment();
void add_item(struct catalogue u);
struct catalogue get_new_item();
void view_items();
void delete_item();
void update_item();
void search_item();
// setters
char* set_type();
char* set_ISBN();
char* set_ISSN();
char* set_title();
char* set_author();
char* set_subheading();
char* set_keyword();
char* set_call_number();
// getters
char* get_type(char *type);
char* get_ISBN(char *ISBN);
char* get_ISSN(char *ISSN);
char* get_title(char *title);
char* get_author(char *author);
char* get_subheading(char *subheading);
char* get_keyword(char *keyword);
char* get_call_number(char *call_number);

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
        add_item(get_new_item());
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

int item_id_auto_increment()
{
    struct catalogue u;
    FILE *fp;
    int id, max = 1000;

    // check if file open is successful
    if ((fp = fopen("catalogue","rb"))==NULL) {
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

// SETTERS

char* set_type(){
    int choice;
    char type[20];
    do {
        printf("Record Type:\n");
        printf("1. Audio casettes, CDs.\n");
        printf("2. Binders.\n");
        printf("3. Books, Booklets, Workbooks.\n");
        printf("4. CD-ROMS, DVD-ROMS, General online resources.\n");
        printf("5. DVDS, VHS.\n");
        printf("6. Fast Add Framework.\n");
        printf("7. Kits.\n");
        printf("8. Models.\n");
        printf("9. Serials.\n");
        printf("Selection: ");
        scanf("%d",&choice);
        switch(choice) {
        case 1:
            strcpy(type,"Audio casettes, CDs");
            break;
        case 2:
            strcpy(type,"Binders");
            break;
        case 3:
            strcpy(type,"Books, Booklets, Workbooks");
            break;
        case 4:
            strcpy(type,"CD-ROMS, DVD-ROMS, General online resources");
            break;
        case 5:
            strcpy(type,"DVDS, VHS");
            break;
        case 6:
            strcpy(type,"Fast Add Framework");
            break;
        case 7:
            strcpy(type,"Kits");
            break;
        case 8:
            strcpy(type,"Models");
            break;
        case 9:
            strcpy(type,"Serials");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }while(choice < 1 || choice > 4);

    str_to_lower(type);

    return type;
}

char* set_ISBN() {
    char ISBN[100];
    //int sig;
    //if(raise(SIGINT)) return;
    do {
        gets(ISBN);
        strcpy(ISBN,trimwhitespace(ISBN));
        if(strcmp(ISBN,"") == 0) {
                printf("ISBN cannot be blank. Try again\n");
        }
    }while(strcmp(ISBN,"") == 0);

    str_to_lower(ISBN);

    return ISBN;
}

char* set_ISSN() {
    char ISSN[100];
    gets(ISSN);
    strcpy(ISSN,trimwhitespace(ISSN));

    str_to_lower(ISSN);

    return ISSN;
}

char* set_title() {
    char title[100];
    //int sig;
    //if(raise(SIGINT)) return;
    do {
        gets(title);
        strcpy(title,trimwhitespace(title));
        if(strcmp(title,"") == 0) {
                printf("Title cannot be blank. Try again\n");
        }
    }while(strcmp(title,"") == 0);

    str_to_lower(title);

    return title;
}

char* set_author() {
    char author[100];
    //int sig;
    //if(raise(SIGINT)) return;
    do {
        gets(author);
        strcpy(author,trimwhitespace(author));
        if(strcmp(author,"") == 0) {
                printf("Author cannot be blank. Try again\n");
        }
    }while(strcmp(author,"") == 0);

    str_to_lower(author);

    return author;
}

char* set_subheading() {
    char subheading[100];
    gets(subheading);
    strcpy(subheading,trimwhitespace(subheading));

    str_to_lower(subheading);

    return subheading;
}

char* set_keyword() {
    char keyword[100];
    gets(keyword);
    strcpy(keyword,trimwhitespace(keyword));

    str_to_lower(keyword);

    return keyword;
}

char* set_call_number() {
    char call_number[100];
    gets(call_number);
    strcpy(call_number,trimwhitespace(call_number));

    str_to_lower(call_number);

    return call_number;
}

// Getters
char* get_type(char *type)
{
    str_capitalize(type);
    return type;
}

char* get_ISBN(char *ISBN)
{
    str_to_upper(ISBN);
    return ISBN;
}

char* get_ISSN(char *ISSN)
{
    str_to_upper(ISSN);
    return ISSN;
}

char* get_title(char *title)
{
    str_capitalize(title);
    return title;
}

char* get_author(char *author)
{
    str_capitalize(author);
    return author;
}

char* get_subheading(char *subheading)
{
    str_capitalize(subheading);
    return subheading;
}

char* get_keyword(char *keyword)
{
    str_to_lower(keyword);
    return keyword;
}

char* get_call_number(char *call_number)
{
    str_to_upper(call_number);
    return call_number;
}

void add_item(struct catalogue u)
{
    FILE *fp;
    char *p;

    u.id = catalogue_id_auto_increment();
    strcpy(u.added_on,get_timestamp());

    if ((fp = fopen("catalogue","ab"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    fwrite(&u, sizeof(struct user), 1, fp);
    fclose(fp);
    printf("Item successfully added\n");
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

