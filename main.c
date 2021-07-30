/**********************************
Project : Library Management System
Author  : Njenga Lewis Kirori
Date    : July, 2021
Compiler: C99
License : MIT
***********************************/


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


//function prototype
void execute_action (int action);
void exit();

int main()
{
    int action;
    printf("\tCommunity library system\n");
    printf("\tWelcome Mr Lewis\n");

    //navigation menu
    do{
        printf("1. Add user\n");
        printf("2. Add book\n");
        printf("3. Exit\n");
        printf("Action(1-3): ");
        scanf("%d", &action);

        //validate
        if (action < 1 || action > 3){
            printf("Invalid action.Try again\n");
            Sleep(2000);
            system("cls");
        }
    }
     while (action < 1 || action > 3);

     execute_action(action);

     return 0;
    }

    void execute_action(int action){
       switch(action){

       case 1:
           printf("Adding user\n");
           break;
       case 2:
           printf("Adding book\n");
           break;
       case 3:
           Exit();
           break;
          default:
           printf("Sorry. I don't know how to execute that\n");

       }
       }


    void Exit() {
     printf("Thank You for using the system");
     Sleep(5000);
     exit(0);
    }









