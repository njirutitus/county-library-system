/*-----------------------------
* Version: C99                *
* Project: Library Management *
* Author:  Lewis Njenga       *
* Date:    Aug, 2022          *
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
#include <signal.h>

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

int IS_LOGGED_IN;
struct user LOGGED_IN_USER;
struct user *all_users;

// Main objects

void users();
void catalogue();

// Function prototype
void execute_action(int action);
void execute_user_action(int action);
void execute_catalogue_action(int action);
void close();
int menu();
int user_menu();
int catalogue_menu();
void  INThandler(int sig);

// User object functions
void add_user(struct user u);
struct user get_new_user();
void view_users(); // users table view
int get_user_id(); // Get id of user to delete
int user_id_auto_increment();
void delete_user();
struct user get_updated_user();
void update_user();
void search_user();
char* get_password(int id);
void login_user();
void set_logged_in_user(struct user u);
struct user fetch_user(int id);
void change_password();
void logout();
int is_password_set();
int get_no_of_users();
int create_first_user();

// Setters
char* set_name();
char* set_initials();
char* set_salutation();
char* set_gender();
char* set_email();
char* set_tel();
int set_is_staff();

// Getters
char* get_name(char *name);
char* get_initials(char *initials);
char* get_salutation(char *salutation);
char* get_gender(char *gender);
char* get_email(char *email);
char* get_tel(char *tel);
char* get_is_staff(int is_staff);

// Catalogue object functions
void add_item();
void view_items();
void delete_item();
void update_item();
void search_item();

// Helper functions
char* get_timestamp();
void str_to_lower(char* str);
void str_to_upper(char* str);
void str_capitalize(char* str);
char* set_password();
int is_password_set();
char* get_initial_password(char *name);
char* read_password();
char *trimwhitespace(char *str);
