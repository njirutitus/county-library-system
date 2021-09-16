#include "header.h"

int main()
{
    int action;
    signal(SIGINT, INThandler);
    while(1) {
        if(!IS_LOGGED_IN) {
            login_user();
        }
        action = menu();
        execute_action(action);
        printf("\nPress any key to continue");
        getch();
        system("cls");
    }

    return 0;
}

int menu()
{
    // Navigation menu
    int action;
    do {
        system("cls");
        printf("\n\tCounty Library Management System!\n");
        str_capitalize(LOGGED_IN_USER.salutation);
        str_capitalize(LOGGED_IN_USER.name);
        printf("Welcome %s. %s\n",LOGGED_IN_USER.salutation,LOGGED_IN_USER.name);
        printf("1. Manage users\n");
        printf("2. Manage catalogue\n");
        printf("3. Log out\n");
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

void execute_action(int action) {
    switch(action) {
    case 1:
        users();
        break;
    case 2:
        catalogue();
        break;
    case 3:
        logout();
        break;
    case 4:
        close();
        break;
    default:
        printf("Unrecognized action. \n");

    }

}

void close() {
    printf("Thank you for using the system\n");
    printf("Created By Titus Njiru(titusnjiru.dev)\n");
    printf("Bye\n");
    Sleep(2000);
    exit(0);
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

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

void  INThandler(int sig)
{
     char  c;

     signal(sig, SIG_IGN);
     printf("\nOUCH, did you hit Ctrl-C?\n"
            "Do you really want to Cancel the operation? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y')
          main();
     else
          signal(SIGINT, INThandler);
     getchar(); // Get new line character
}
