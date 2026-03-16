/*
---------------------------------------------------------------------------------------------------------------------------
 File Name        : contact.c
 File Description : Contains function definitions for main operations in the Address Book:
                    create, edit, delete, search, list, save, and load contacts.
                    Provides logic for all menu operations as called from main.c.
 Name             : Vishal Jagatap
 Date             : 28/01/2026
---------------------------------------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include "contact.h"
// Function Definitions
int create_contact(AddressBook *addressbook)   //create function definition
{
    char name[35];
    char number[12];
    char email[35];
    int ret=0,res=0;
    printf("\033[0;35m");
    printf("Enter the name : ");
    printf("\033[0m");
    do
    {
        scanf(" %34[^\n]",name);         //read the name
        ret = validate_name(name);       // validate name function call
        if(ret==1)
        {
            printf("Created name sucessfully\n");  // if name is valid 
        }
        else
        {
            printf("\033[0;35m");
             printf("Enter name again \n");   //name is not currect read again
             printf("\033[0m");
        }
    } while (ret!=1);
    printf("\033[0;35m");
    printf("Enter the number : ");    
    printf("\033[0m");
    do
    {
        scanf(" %11s",number);        //read the number
        ret = validate_number(number);   // validate number function call
        res=unique_number(number,addressbook);  //unique number function call
        if(ret==1&&res==1)
        {
            printf("Created number sucessfully\n");    // if number is valid form and unique
        }
        else
        {
            printf("\033[0;35m");
             printf("Enter number again\n");     // number is not valid read again
             printf("\033[0m");  
        }
    }while(ret!=1 || res!=1);
    printf("\033[0;35m");
    printf("Enter the email : ");
    printf("\033[0m");
    do
    {
        scanf(" %34s",email);      // read the email id
        ret = validate_email(email);  //validate email function call
        res = unique_email(email,addressbook); // unique email function call
        if(ret==1&&res==1)
        {
            printf("Created email sucessfully\n"); // if Email ID is unique and valid
        }
        else
        {
            printf("\033[0;35m");
            printf("Enter email again :"); //Email ID is not unique and not valid read again
            printf("\033[0m"); 
        }
    } while (ret!=1|| res!=1);

    int idx = addressbook->contact_count;
    strcpy(addressbook->contact_details[idx].Name, name);
    strcpy(addressbook->contact_details[idx].Mobile_number, number);
    strcpy(addressbook->contact_details[idx].Mail_ID, email);
    addressbook->contact_count++;
    printf("Contact details Uploaded Successfully\n");  // to store the contact details
    return 0;
}
void list_contacts(AddressBook *addressbook)    //list contacts function definition
{
    if (addressbook->contact_count == 0)    //if file is empty
    {
        printf("\033[0;31m");
        printf("No contacts found\n");    
        printf("\033[0m"); 
        return;
    }
    printf("\033[0;34m");
    printf("Idx    Name                 Phone        Email\n");     //print all the contacts
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        printf("%-4d %-20s %-12s %s\n",i + 1,addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
    }
    printf("\033[0m");
}
int search_contacts(AddressBook *addressbook)     //search contacts function definition
{
    int option, found=0;
    char search[35];
    int index[addressbook->contact_count];
    while (1)
    {
        printf("\033[0;32m"); // GREEN COLOR
        printf("+-----------------------------+\n");
        printf("|     Search Contact Menu     |\n");
        printf("+-----------------------------+\n");
        printf("| 1. Name                     |\n");
        printf("| 2. Mobile number            |\n");
        printf("| 3. Mail ID                  |\n");
        printf("| 4. Exit                     |\n");
        printf("+-----------------------------+\n");
        printf("\033[0m");
        printf("\033[0;35m");
        printf("Enter the option : ");  //read the option
        printf("\033[0m");
        if(scanf("%d",&option)!=1)    // if invalid input
        {
            printf("\033[0;31m");
            printf("Invalid Input, Enter the option again.\n\n");
            printf("\033[0m");
            while(getchar()!='\n');
            continue;
        }
        switch(option)
        {
            case 1:                // search by name
            {
                printf("\033[0;35m");
                printf("Search by name : ");
                printf("\033[0m");
                scanf(" %[^\n]",search);
                break;
            }
            case 2:            //search by number
            {
                printf("\033[0;35m");
                printf("Search by Number : ");
                printf("\033[0m");
                scanf(" %[^\n]",search);
                break;
            }
            case 3:             // search by Email ID
            {
                printf("\033[0;35m");
                printf("Search by email : ");
                printf("\033[0m");
                scanf(" %[^\n]",search);
                break;
            }
            case 4:               // to exit
            {
                return 0;
            }
            default :        // if invalid option
            {
                printf("\033[0;31m");
                printf("Invalid option! Plese enter 1,2 or 3.\n\n");
                printf("\033[0m");
                continue;
            }
        }
        break;
    }
    
    for (int i = 0; i < addressbook->contact_count; i++)     // to search the details if found
    {
        if ((option == 1 && strstr(addressbook->contact_details[i].Name, search) != NULL) ||
            (option == 2 && strstr(addressbook->contact_details[i].Mobile_number, search) != NULL) ||
            (option == 3 && strstr(addressbook->contact_details[i].Mail_ID, search) != NULL))
        {
            index[found]=i;
            printf("\033[0;34m");
            printf("%d) %s | %s | %s\n",++found,addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
            printf("\033[0m");
        }
    } 
    if (found == 0)   // if contact not found
    {
        printf("\033[0;31m");
        printf("No contact found\n\n");
        printf("\033[0m");
        return 0;
    }

    printf("\033[0;34m");
    printf("--------------------------------------------------\n\n");
    printf("%d contact(s) found\n", found);   // number of contacts found
    printf("\033[0m"); 
    return found;
}
int edit_contact(AddressBook *addressbook)   //edit contact function definition
{
    int found=0,select,option,ret,idx,index[addressbook->contact_count];
    char edit[35],name[35],number[12],email[35];
    while(1)
    {
        printf("\033[0;32m"); // GREEN COLOR
        printf("+-----------------------------+\n");
        printf("|      Edit Contact Menu      |\n");
        printf("+-----------------------------+\n");
        printf("| 1. Name                     |\n");
        printf("| 2. Mobile number            |\n");
        printf("| 3. Mail ID                  |\n");
        printf("| 4. Exit                     |\n");
        printf("+-----------------------------+\n");
        printf("\033[0m");
        printf("\033[0;35m");  //purple
        printf("Enter the option : ");   // read the option
        printf("\033[0m");
        if(scanf("%d",&option)!=1)   // if invalid option
        {
            printf("\033[0;31m");
            printf("Invalid Input, Enter the option again.\n\n");
            printf("\033[0m");
            while(getchar()!='\n');
            continue;
        }
        if(option>=1&&option<=4)
        {
            break;
        }
        printf("\033[0;31m");
        printf("Invalid option. Enter 1 to 4.\n");
        printf("\033[0m");
    }
    if(option==1)
    {
        printf("\033[0;35m");;
        printf("Edit by Name :");  //edit by name
        printf("\033[0m");
    }
    else if(option==2)
    {
        printf("\033[0;35m");
        printf("Edit by Mobile Number:");  //edit by number
        printf("\033[0m");
    }
    else if(option==3)
    {
        printf("\033[0;35m");
        printf("Edit by Email ID :");   // edit by Email ID
        printf("\033[0m");
    }
    if(option==4)
    {
        return 0;            // exit
    }
    scanf(" %34[^\n]", edit);
    for (int i = 0; i < addressbook->contact_count; i++)   // search contact and check if multiple contacts are present
    {
        if ((option == 1 && strstr(addressbook->contact_details[i].Name, edit) != NULL) ||
            (option == 2 && strstr(addressbook->contact_details[i].Mobile_number, edit) != NULL) ||
            (option == 3 && strstr(addressbook->contact_details[i].Mail_ID, edit) != NULL))
        {
            index[found]=i;
            printf("\033[0;34m");
            printf("%d) %s | %s | %s\n",++found,addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
            printf("\033[0m");
        }
    }
    if (found == 0)  // if no contacts found
    {
        printf("\033[0;31m");
        printf("No contact found\n\n");
        printf("\033[0m");
        return 0;
    }
    printf("\033[0;34m");
    printf("--------------------------------------------------\n");
    printf("%d contact(s) found\n\n", found);  //number of contacts found
    printf("\033[0m");
    if (found == 1)    // if only one contact found
    {
        idx = index[0];
        printf("\033[0;34m");
        printf("Only one contact found. Editing this contact...\n");
        printf("\033[0m");
    }
    else             // if multiple contacts found then edit by index value
    {
        printf("\033[0;35m");
        printf("Enter the index to edit: ");
        printf("\033[0m");
        if (scanf("%d", &select) != 1)
        {
            printf("\033[0;31m");
            printf("Invalid input\n");
            printf("\033[0m");
            while (getchar() != '\n');
            return 0;
        }

        if (select < 1 || select > found)
        {
            printf("\033[0;31m");
            printf("Invalid index\n");
            printf("\033[0m");
            return 0;
        }
        idx = index[select - 1];
    }
    switch(option)
    {
        case 1:
        do
        {
            printf("\033[0;35m");
            printf("Enter new name : ");   // read nuw name
            printf("\033[0m");
            scanf(" %34[^\n]", name);
            ret = validate_name(name);    //validate new name
            if(ret != 1)
            {
            printf("\033[0;35m");
            printf("Enter name again \n");  //if name is invalid read again
            printf("\033[0m");
            }
        } while(ret != 1);
        strcpy(addressbook->contact_details[idx].Name, name);
        printf("Name updated successfully\n");   // if name is valid update the new name
        break;

        case 2:
            do
        {
            printf("\033[0;35m");
            printf("Enter new Number : ");   // read the new number
            printf("\033[0m");
            scanf(" %11[^\n]", number);
            ret = validate_number(number);   //validate the number
            if(ret == 1 && !unique_number(number, addressbook))  //if the number is not unique
            ret = 0;
            if(ret != 1)
            {
                printf("\033[0;35m");
                printf("Enter number again \n ");  //if number is not valid read number again
                printf("\033[0m");
            }
        } while(ret != 1);
        strcpy(addressbook->contact_details[idx].Mobile_number, number);
        printf("Number updated successfully\n");   //if number is unique and valid
        break;

        case 3:
            do
        {
            printf("\033[0;35m");
            printf("Enter new email : ");   // read nem Email ID
            printf("\033[0m");
            scanf(" %34[^\n]", email);
            ret = validate_email(email);    // vaildate the Email ID
            if(ret == 1 && !unique_email(email, addressbook))  //if Email ID is valid but not unique
            ret = 0;
            if(ret != 1)
            {
                printf("\033[0;35m");
                printf("Enter email again \n ");  //Email ID is invalid read again
                printf("\033[0m");
            }
        } while(ret != 1);
        strcpy(addressbook->contact_details[idx].Mail_ID, email);
        printf("Email updated successfully\n");  //Email ID is valid and unique
        break; 

        default:
        {
            printf("\033[0;31m");
            printf("Invalid option\n");    //  invalid option 
            printf("\033[0m");
        }
            return 0;
    } 
    return 1;
}

int delete_contact(AddressBook *addressbook)   //delete contact function definition
{
    int option, found, select, idx;
    int index[addressbook->contact_count];
    char del[35], confirm;
    if (addressbook->contact_count == 0)
    {
        printf("No contacts to delete.\n");  //if no contacts
        return 0;
    }
    while(1)
    {
        found=0;
        while (1)
        {
            printf("\033[0;32m"); // GREEN COLOR
            printf("+-----------------------------+\n");
            printf("|    Delete Contact Menu      |\n");
            printf("+-----------------------------+\n");
            printf("| 1. Name                     |\n");
            printf("| 2. Mobile Number            |\n");
            printf("| 3. Email ID                 |\n");
            printf("| 4. Exit                     |\n");
            printf("+-----------------------------+\n");
            printf("\033[0m");
            printf("\033[0;35m");  //purple
            printf("Enter the option : ");
            printf("\033[0m");
            if (scanf("%d", &option) != 1)  //read option
            {
                printf("\033[0;31m");
                printf("Invalid Input\n");  //invalid option
                printf("\033[0m");
                while (getchar() != '\n');
                continue;
            }

            if (option >= 1 && option <= 4)
                break;
            printf("\033[0;31m");
            printf("Invalid option. Enter 1 to 4.\n");
            printf("\033[0m");
        }

        if (option == 4)
            return 0;

        printf("\033[0;35m");
        switch (option)
        {
            case 1: printf("Delete by Name: "); break;   //delete by name
            case 2: printf("Delete by Mobile Number: "); break;//delete by number
            case 3: printf("Delete by Email ID: "); break;//delete by Email ID
        }
        printf("\033[0m");
        scanf(" %34[^\n]", del);
        for (int i = 0; i < addressbook->contact_count; i++)  // search contact details
        {
            if ((option == 1 && strstr(addressbook->contact_details[i].Name, del) != NULL) ||
                (option == 2 && strstr(addressbook->contact_details[i].Mobile_number, del) != NULL) ||
                (option == 3 && strstr(addressbook->contact_details[i].Mail_ID, del) != NULL))
            {
                index[found] = i;
                printf("\033[0;34m");
                printf("%d) %s | %s | %s\n",found + 1,addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
                    printf("\033[0m");
                found++;
            }
        }

        if (found == 0)   //if contact not found
        {
            printf("\033[0;31m");
            printf("Contact not found. Please enter again.\n");
            printf("\033[0m");
            continue;
        }
        printf("\033[0;34m");
        printf("\n%d contact(s) found\n", found);  //number ofd contacts found
        printf("\033[0m");

        if (found == 1)
        {
            idx = index[0];
        }
        else
        {
            printf("\033[0;35m");
            printf("Enter the index to delete: ");  //if multiple contacts found
            printf("\033[0m");
            if (scanf("%d", &select) != 1 || select < 1 || select > found)
            {
                printf("\033[0;31m");
                printf("Invalid index\n");
                printf("\033[0m");
                return 0;
            }
            idx = index[select - 1];
        }
        printf("\033[0;35m");
        printf("Are you sure you want to delete this contact? (Y/N): ");  //ask user to delete or not
        printf("\033[0m");
        scanf(" %c", &confirm);

        if (confirm != 'Y' && confirm != 'y')
        {
            printf("Delete cancelled\n");
            return 0;
        }
        // delete contact
        for (int i = idx; i < addressbook->contact_count - 1; i++)
        {
            addressbook->contact_details[i] = addressbook->contact_details[i + 1];
        }

        addressbook->contact_count--;

        printf("Contact deleted successfully\n");
        return 1;
    }
}
int save_contacts(AddressBook *addressbook)  //save contact function definition
{
    for (int i = 0; i < addressbook->contact_count - 1; i++)
    {
        for (int j = 0; j < addressbook->contact_count - 1 - i; j++)
        {
            if (strcmp(addressbook->contact_details[j].Name,
                       addressbook->contact_details[j + 1].Name) > 0)
            {
                // Swap the two contacts
                Contacts temp = addressbook->contact_details[j];
                addressbook->contact_details[j] = addressbook->contact_details[j + 1];
                addressbook->contact_details[j + 1] = temp;
            }
        }
    }
    FILE *fp = fopen("contacts.txt", "w");  //create file in write mode
    if (fp == NULL)    //if file is not created
    {
        printf("\033[0;31m");
        printf("Error in creating file\n");  //fi
        printf("\033[0m");
        return 0;
    }
    fprintf(fp, "#%d\n", addressbook->contact_count);  //number odf contacts
    for (int i = 0; i < addressbook->contact_count; i++)// save contacts one by one
    {
        fprintf(fp, "%s,%s,%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
    }

    fclose(fp);
    return 1;
}


int validate_name(char *name )   // validate name function definition
{
    int i=0,space_count=0;
    if (name[0] == ' ' || name[strlen(name)-1] == ' ')//check is there any space at start or end 
        {
            printf("\033[0;31m");
            printf("Name should not start or end with space\n");
            printf("\033[0m");
            return 0;
        }
    while(name[i]!='\0')
    {
       if (!(isalpha(name[i]) || name[i] == ' '))   //checks name has only alphabates or not
        {
            printf("\033[0;31m");
            printf("Invalid Input, Name should be only in alphabates.\n");
            printf("\033[0m");return 0;

        }
        if (name[i] == ' ')
        {
            space_count++;
            if (space_count > 1)   // name should contain only 1 space
            {
                printf("\033[0;31m");
                printf("Invalid Input, Name should contain only one space.\n");
                printf("\033[0m");
                return 0;
            }

        }
        i++;
    }
    return 1;
}
int validate_number(char *number)  //validate number function definition
{
    int i=0;
    int length=strlen(number);
    if(length!=10)   // Mobile Number should be of 10 digits
    {
        printf("\033[0;31m");
        printf("Invalid Input, Number should contain only 10 digits.\n");
        printf("\033[0m");
        return 0;
    }
    if(number[0]<'6'||number[0]>'9')  // First Digit of the Number should be in range of 6 to 9
        {
            printf("\033[0;31m");
            printf("Invalid Input, First Digit of the Number should be in range of 6 to 9.\n");
            printf("\033[0m");
            return 0;
        }
    while(number[i]!='\0')
    {
        if(!isdigit(number[i]))  //Number should contain only digits
        {
            printf("\033[0;31m");
            printf("Invalid Input, Number should contain only digits.\n");
            printf("\033[0m");
            return 0;
        }
        i++;
    }
    return 1;
}
int validate_email(char *email)  //validate email function definition
{
    int count=0;
    int length=strlen(email);
    int i=0;
    if(length < 5)  //check the email ID length
    {
        printf("\033[0;31m");
        printf("Invalid Input, Email ID length is too short\n");
        printf("\033[0m");
        return 0;
    }
    if(!isalnum(email[0])) //Email ID should contain only alphabates and numbers before @
    { 
        printf("\033[0;31m");
        printf("Invalid Input, Email ID should contain only alphabates and numbers before @ ");
        printf("\033[0m");
        return 0;
    }
    
    if(strcmp(&email[length-4],".com")!=0)//Email ID must end with .com
    {
        printf("\033[0;31m");
        printf("Invalid Input, Email ID must end with .com\n");
        printf("\033[0m");
        return 0;
    }
    while(email[i]!='\0'&&email[i]!='@')
    {
        if(!isalnum(email[i]))//Only alphabets and numbers allowed before @
        {
            printf("\033[0;31m");
            printf("Invalid Input, Only alphabets and numbers allowed before @\n");
            printf("\033[0m");
            return 0;
        }
        i++;
    }
    if(email[i]!='@')//Email ID must contain @ symbol
    {
        printf("\033[0;31m");
        printf("Invalid Input, Email ID must contain @ symbol\n");
        printf("\033[0m");
        return 0;
    }
    i=0;
    while(email[i]!='\0')
    {
        if(isupper(email[i]))//Email ID should not contain capital letters
        {
            printf("\033[0;31m");
            printf("Invalid Input, Email ID should not contain capital letters\n");
            printf("\033[0m");
            return 0;
        }
        if(email[i]=='@')
        {
            count++;
        }
        i++;
    }
    if(count!=1)//Email ID should contain only one @ symbol
    {
        printf("\033[0;31m");
        printf("Invalid Input, Email ID should contain only one @ symbol\n");
        printf("\033[0m");
        return 0;
    }
    i=0;
    while(email[i]!='@')
    {
        i++;
    }i++;
    if(!isalpha(email[i]))  //Domain name should start with an alphabet
    {
        printf("\033[0;31m");
        printf("Invalid Input, Domain name should start with an alphabet\n");
        
        printf("\033[0m");
        return 0;
    }
    while(email[i]!='\0'&& email[i]!='.')
    {
        if(!isalpha(email[i]))//Domain name should contain only alphabets
        {
            printf("\033[0;31m");
            printf("Invalid Input, Domain name should contain only alphabets\n");
            printf("\033[0m");
            return 0;
        }
        i++;
    }
    if (strcmp(&email[i], ".com") != 0)
    {
        printf("\033[0;31m");
        printf("Invalid Input, Email ID must contain only one .com\n");
        printf("\033[0m");
        return 0;
    }
    return 1;
}
int load_contacts(AddressBook *addressbook)  //load function definition
{
    FILE *fp = fopen("contacts.txt", "r"); // open file in red mode

    if (fp == NULL)  // if file is empty
    {
        printf("No contact file found.\n");
        addressbook->contact_count = 0;
        return 0;
    }

    fscanf(fp, "#%d\n", &addressbook->contact_count);  // rad number of contacts

    for (int i = 0; i < addressbook->contact_count; i++)  //read the  contact details 1 by 1
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
    }

    fclose(fp);
    printf("Contacts loaded successfully.\n");
    return 1;
}
int unique_number(char *number, AddressBook *addressbook)  //unique number function definition
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(number, addressbook->contact_details[i].Mobile_number) == 0)//compate with all contacts
        {
            printf("\033[0;31m");
            printf("Mobile Number already exists, please enter a unique Mobile Number.\n");
            printf("\033[0m");
            return 0; //if alrady exists
        }
    }
    return 1;   // if number is unique
}
int unique_email(char *email, AddressBook *addressbook)  //unique email function definition
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(email, addressbook->contact_details[i].Mail_ID) == 0) //compare with all contacts
        {
            printf("\033[0;31m");
            printf("Email ID already exists, please enter a unique Email ID.\n");
            printf("\033[0m");
            return 0;// if alrady exist
        }
    }
    return 1;  // if unique
}