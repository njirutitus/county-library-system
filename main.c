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
int main()
{
    int action;
    printf("\tCounty Library Management System!\n");
    printf("Welcome Titus\n");
    // Navigation menu
    do {
        printf("1. Add user\n");
        printf("2. Add Book\n");
        printf("3. Exit\n");
        printf("Select action(1-3): ");
        scanf("%d",&action);
        // validate input
        if (action < 1 || action > 3)
            printf("Invalid action. Try again\n");
    } while(action < 1 || action > 3);

    return 0;
}
