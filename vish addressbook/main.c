/*
---------------------------------------------------------------------------------------------------------------
 Project Name        : Address Book Using C Programming
 Project Description : A terminal-based application to create,
                       search, edit, delete, list,
                       save contacts, and load contacts using a txt file.
---------------------------------------------------------------------------------------------------------------
 File Name           : main.c
 File Description    : Entry point of the Address Book application.
                       Provides menu options to create, search,
                       edit, delete, list, and save contacts and function calls.
 Name                : Vishal Jagatap
 Date                : 28/01/2026
---------------------------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include "contact.h"
/* Structure declaration */

int main()
{
    /* Variable and structre defintion */
    int option;
    AddressBook addressbook;
    addressbook.contact_count = 0;
    load_contacts(&addressbook);   //load contacts function call

    while (1)
    {
        printf("\033[0;32m");
        printf("\n+---------------------------+\n");   //menu of addressvook
        printf("|     Address Book Menu     |\n");
        printf("+---------------------------+\n");
        printf("| 1. Add contact            |\n");
        printf("| 2. Search contact         |\n");
        printf("| 3. Edit contact           |\n");
        printf("| 4. Delete contact         |\n");
        printf("| 5. Display contact        |\n");
        printf("| 6. Save contact           |\n");
        printf("| 7. Exit                   |\n");
        printf("+---------------------------+\n");
        printf("\033[0m");
        printf("\033[0;35m");
        printf("Enter the option : ");
        printf("\033[0m");
        if(scanf("%d",&option)!=1)
    {
        printf("Invalid Input\n ");
        return 0;
    }

        switch (option) /* Based on choosed option */
        {
        case 1:
        {
            create_contact(&addressbook);  //create function call
            break;
        }

        case 2:
        {
            search_contacts(&addressbook);   //search function call
            break;
        }
        case 3:
        {
            edit_contact(&addressbook);   //edit function call
            break;
        }
        case 4:
        {
            delete_contact(&addressbook);   // delete function call
            break;
        }
        case 5:
        {
            printf("\033[0;34m");  //blue
            printf("List Contacts:\n");
            printf("\033[0m"); 
            list_contacts(&addressbook);   //list function call
            break;
        }

        case 6:
            printf("\033[0;34m");   //blue
            printf("Saving contacts\n");
            printf("\033[0m");
            save_contacts(&addressbook);   //save function call
            break;

        case 7:
            printf("\033[0;34m");
            printf("INFO : Save and Exit...\n");
            printf("\033[0m");
            save_contacts(&addressbook);  // save function call and exit
            return 0;

        default:
            printf("\033[0;31m"); //red
            printf("Invalid option \n");  // if invalid option
            printf("\033[0m"); 
            break;
        }
    }
    return 0;
}
