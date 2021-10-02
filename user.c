#include "header.h"

void users() {
    int action;
    while(1) {
        if(!IS_LOGGED_IN) {
            login_user();
        }
        action = user_menu();
        execute_user_action(action);
        printf("\nPress any key to continue");
        getch();
        system("cls");
    }
}

int user_menu() {
    // Navigation menu
    int action;
    do {
        system("cls");
        printf("\n\tCounty Library Management System!\n");
        str_capitalize(LOGGED_IN_USER.salutation);
        str_capitalize(LOGGED_IN_USER.name);
        printf("Welcome %s. %s\n",LOGGED_IN_USER.salutation,LOGGED_IN_USER.name);
        printf("1. Add user\n");
        printf("2. View users\n");
        printf("3. Delete user\n");
        printf("4. Update user\n");
        printf("5. Search user\n");
        printf("6. Change Password\n");
        printf("7. Go back\n");
        printf("8. Log out\n");
        printf("9. Exit\n");
        printf("Select action(1-9): ");
        scanf("%d",&action);
        // validate input
        if (action < 1 || action > 9) {
            printf("Invalid action. Try again\n");
            Sleep(2000);
            system("cls");
        }

    } while(action < 1 || action > 9);

    return action;
}

void execute_user_action(int action) {
    switch(action) {
    case 1:
        if(LOGGED_IN_USER.is_staff)
            add_user(get_new_user());
        else printf("Permission Denied\n");
        break;
    case 2:
        view_users("");
        break;
    case 3:
        delete_user();
        break;
    case 4:
        update_user(get_updated_user());
        break;
    case 5:
        search_user();
        break;
    case 6:
        change_password();
        break;
    case 7:
        main();
        break;
    case 8:
        logout();
        break;
    case 9:
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

char* set_name() {
    char name[100];
    //int sig;
    //if(raise(SIGINT)) return;
    do {
        gets(name);
        strcpy(name,trimwhitespace(name));
        if(strcmp(name,"") == 0) {
                printf("Name cannot be blank. Try again\n");
        }
    }while(strcmp(name,"") == 0);

    str_to_lower(name);

    return name;
}

char* set_initials() {
    char initials[100];
    do {
        gets(initials);
        strcpy(initials,trimwhitespace(initials));
        if(strcmp(initials,"") == 0) printf("Initials cannot be blank. Try again\n");
    }while(strcmp(initials,"") == 0);

    str_to_lower(initials);

    return initials;
}

char* set_email()
{
    char email[50];
    do {
        gets(email);
        strcpy(email,trimwhitespace(email));
        if(strcmp(email,"") == 0) printf("Email cannot be blank. Try again\n");
    }while(strcmp(email,"") == 0);

    str_to_lower(email);

    return email;
}

int set_is_staff()
{
    int is_staff;
    do {
        printf("0. Standard user.\n");
        printf("1. Staff.\n");
        printf("2. Super Admin.\n");
        printf("Selection(0-2): ");
        scanf("%d",&is_staff);
        if(is_staff < 0 || is_staff > 2)
            printf("Invalid selection. Try again. \n");

    }while(is_staff < 0 || is_staff > 2);

    return is_staff;
}

char* set_tel()
{
    char tel[30],ch;
    int j,valid = 1;
    do {
        gets(tel);
        valid = 1;
        if(strlen(tel)>13) {
            printf("Phone number can only contain up to 13 digits. Try again\n");
            valid = 0;
        }
        for(j=0;j<strlen(tel);j++){
            if(!isdigit(tel[j])) {
                valid = 0;
                printf("Phone number can only contain digits. Try again\n");
                break;
            }
        }
    } while(!valid);
    return tel;

}

char* set_gender(){
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
        printf("\nEnter new password: ");
        strcpy(pass,read_password());
        printf("\nConfirm password: ");
        strcpy(confirm_pass,read_password());

        if(strcmp(pass,confirm_pass)) {
            printf("\nPasswords Do not match.\n");
            printf("Enter c to try again or x to exit. \n");
            ch = getch();
            system("cls");
            if(ch == 'x') {
                printf("\nOperation Canceled\n");
                break;
            }
        }
        else {
            printf("\nPassword set Successfully\n");
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

char* get_password(int id) {
    struct user u;
    FILE *fp;

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id == id) {
            fclose(fp);
            return u.password;
        }
    }

    fclose(fp); // close file
    return "";
}

char* set_salutation() {
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

// Getters
char* get_name(char *name)
{
    str_capitalize(name);
    return name;
}

char* get_initials(char *initials)
{
    str_to_upper(initials);
    return initials;
}

char* get_salutation(char *salutation)
{
    str_capitalize(salutation);
    return salutation;
}

char* get_gender(char *gender)
{
    str_capitalize(gender);
    return gender;
}

char* get_email(char *email)
{
    str_to_lower(email);
    return email;
}

char* get_tel(char *tel)
{
    return tel;
}

char* get_is_staff(int is_staff)
{
    char staff[12];
    switch(is_staff) {
        case 0:
            strcpy(staff, "Standard");
            break;
        case 1:
            strcpy(staff, "Staff");
            break;
        case 2:
            strcpy(staff, "Admin");
            break;
        default:
            strcpy(staff, "Undefined");
            break;
    }

    return staff;

}

void add_user(struct user u) {
    FILE *fp;
    char *p;

    u.id = user_id_auto_increment();
    strcpy(u.added_on,get_timestamp());

    if ((fp = fopen("users","ab"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    p = get_initial_password(u.name);
    strcpy(u.password,p);

    fwrite(&u, sizeof(struct user), 1, fp);
    fclose(fp);
    printf("User successfully added\n");
    printf("Initial Password (kindly write it down): %s\n",u.password);
    printf("Membership ID: %d\n",u.id);
}

int create_first_user() {
    char choice;
    printf("No users available. Would u like to create one? (Y/n): ");
    choice = getchar();
    if(choice == 'N' || choice == 'n') {
        return 0;
    }
    else {
        add_user(get_new_user());
    }
    return 1;
}

struct user get_new_user()
{
    struct user u;
    char *p;

    printf("Name: ");
    getchar();
    strcpy(u.name,set_name());
    printf("Initials: ");
    strcpy(u.initials,set_initials());
    p = set_salutation();
    strcpy(u.salutation,p);
    p = set_gender();
    strcpy(u.gender,p);
    printf("Phone Number: ");
    getchar();
    strcpy(u.tel,set_tel());
    printf("Email: ");
    strcpy(u.email,set_email());
    printf("User type: \n");
    u.is_staff = set_is_staff();

    return u;

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
    char staff[12];

    str_to_lower(term);

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    printf("\n\tLIST OF USERS\n\n");
    int count;
    for(count = 0;count<153;count++) printf("_"); // print 65 underscores/underline
    printf("\n");
    printf("|%8s| %11s| %20s| %6s| %13s| %13s| %30s| %12s| %20s|\n","ID","SALUTATION","NAME","INITIALS","GENDER","PHONE","EMAIL","USER TYPE","ADDED ON");
    for(count = 0;count<153;count++) printf("_");
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
        strcpy(staff,get_is_staff(u.is_staff));
        str_to_lower(staff);
        if(!(strcmp(id,term) == 0 || strstr(staff,term)|| strstr(u.salutation,term) || strstr(u.name,term) || strstr(u.initials,term) || strstr(u.tel,term) || strstr(u.email,term) || strcmp(is,term) == 0 || strcmp(u.gender,term) == 0)) continue;

        printf("|%8d| ",u.id);
        //printf("%11s| ",u.salutation);
        printf("%11s| ",get_salutation(u.salutation));
        printf("%20s|   ",get_name(u.name));
        printf("%6s| ",get_initials(u.initials));
        printf("%13s| ",get_gender(u.gender));
        printf("%13s| ",get_tel(u.tel));
        printf("%30s| ",get_email(u.email));
        strcpy(staff,get_is_staff(u.is_staff));
        printf("%12s| ",staff);
        printf("%20s|\n",u.added_on);
    }
    for(count = 0;count<153;count++) printf("_");
    printf("\n");
    fclose(fp); // close file

}

int get_no_of_users() {
    struct user u;
    FILE *fp;
    int uid=0,count=0;

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        if ((fp = fopen("users","wb"))==NULL) {
            printf("Cannot open file.\n");
            exit(1);
        }
        fclose(fp);
        return 0;
    }

    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id == uid ) continue;
        count++;
    }
    fclose(fp); // close file

    return count;
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

void update_user(struct user new_user)
{
    struct user u;
    FILE *fp,*fp1;
    int uid=0;

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



    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id == uid ) continue;
        uid = u.id;
        if(u.id == new_user.id ) u = new_user;
        fwrite(&u, sizeof(struct user), 1, fp1);
    }

    fclose(fp); // close file
    fclose(fp1);

    if(remove("users") == 0) {
        if(rename("users_tmp","users") == 0)
            printf("Update successful. \n");
        else
            printf("Could not rename temporary file\n");
    }
    else {
        printf("Could not delete old file. \n");
    }
}

struct user get_updated_user()
{
    int attr,id;
    char *p;
    struct user u;
    printf("\nSelect User to Update:\n");
    id = get_user_id();
    u = fetch_user(id);
    while(1) {
            do{
                printf("Select attribute to edit: \n");
                printf("1. Salutation: %s\n",get_salutation(u.salutation));
                printf("2. Name: %s\n",get_name(u.name));
                printf("3. Initials: %s\n",get_initials(u.initials));
                printf("4. Gender: %s\n",get_gender(u.gender));
                printf("5. Phone: %s\n",get_tel(u.tel));
                printf("6. Email: %s\n",get_email(u.email));
                char staff[12];
                strcpy(staff,get_is_staff(u.is_staff));
                printf("7. User type: %s\n",staff);
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
                p = set_salutation();
                strcpy(u.salutation,p);
                break;
            case 2:
                printf("New Name: ");
                strcpy(u.name,set_name());
                break;
            case 3:
                printf("New Initials: ");
                gets(u.initials);
                break;
            case 4:
                printf("New Gender\n");
                p = set_gender();
                strcpy(u.gender,p);
                break;
            case 5:
                printf("New Phone no.: ");
                strcpy(u.tel,set_tel());
                break;
            case 6:
                printf("New Email: ");
                strcpy(u.email,set_email());
                break;
            case 7:
                printf("New user status: \n");
                u.is_staff = set_is_staff();
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

struct user fetch_user(int id) {
    struct user u;
    FILE *fp;

    // check if file open is successful
    if ((fp = fopen("users","rb"))==NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    // read all records from a file until end of file
    while(!feof(fp)) {
        fread(&u, sizeof(struct user), 1, fp);
        if(u.id == id) break;
    }

    fclose(fp); // close file

    return u;
}


void set_logged_in_user(struct user u) {
    LOGGED_IN_USER = u;
}

void login_user()
{
    char ch,pass[30],password[30];
    int id,i;
    system("cls");
    printf("\n\tCounty Library Management System!\n");
    printf("U must be logged in to continue. Press x to exit or any other key to continue. \n");
    ch = getch();
    system("cls");
    if(ch == 'x') close();
    if(get_no_of_users() == 0 ) {
     if(!create_first_user()) {
        main();
     }
    }
    while(1) {
        printf("Log in to continue.\n");
        printf("Membership ID: ");
        scanf("%d",&id);
        strcpy(pass,get_password(id));
        if(!strcmp(pass,"")) {
            printf("User with that Membership ID does not exist. \nPress x to exit or any other key to continue. \n ");
            ch = getch();
            system("cls");
            if(ch == 'x') login_user();
            else continue;
        }
        while(1) {
            i = 0;
            system("cls");
            printf("Enter password: ");
            strcpy(password,read_password());
            if(strcmp(pass,password)) {
                printf("\nIncorrect Password.\n");
                printf("Enter c to try again or x to exit. \n");
                ch = getch();
                system("cls");
                if(ch == 'x') login_user();
            }
            else {
                IS_LOGGED_IN = 1;
                set_logged_in_user(fetch_user(id));
                printf("\nLogin Successful.\n");
                printf("Press any key to continue");
                getch();
                return;
            }
        }

    }

}

int is_password_set() {
    return strcmp(LOGGED_IN_USER.password,get_initial_password(LOGGED_IN_USER.name));
}

void change_password() {
    char old_pass[30],new_pass[30];
    printf("Enter old password: ");
    strcpy(old_pass,read_password());
    if(strcmp(old_pass,LOGGED_IN_USER.password) == 0) {
        strcpy(new_pass,set_password());
        strcpy(LOGGED_IN_USER.password,new_pass);
        update_user(LOGGED_IN_USER);
    }
    else {
        printf("\nIncorrect Old Password\n");
    }

}

void logout() {
    IS_LOGGED_IN = 0;
    printf("\n You have been logged out. \n");
}

char* read_password()
{
    char password[30],ch;
    int i = 0;
    while(1) {
            ch = getch();
            if(ch == '\r') break;
            if(!isgraph(ch) || iscntrl(ch)) continue;
            password[i] = ch;
            printf("*");
            i++;
    }
    return password;
}
