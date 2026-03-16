/*
---------------------------------------------------------------------------------------------------------------
 File Name        : contact.h
 File Description : Header file for the Address Book application.
                    This file contains structure definitions to store contact details
                    such as name, mobile number, and email ID.
                    It also provides function declarations for creating, listing,
                    searching, editing, deleting, loading, and saving contacts.
                    Additionally, it includes validation and uniqueness check
                    function declarations for contact data.
 Name             : Vishal Jagatap
 Date             : 28/01/2026
---------------------------------------------------------------------------------------------------------------
*/

#ifndef CONTACT_H
#define CONTACT_H

typedef struct Contact_data    //contacts structure declaration 
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
} Contacts;

typedef struct AddressBook_Data     //addressBook structure declaration 
{
    Contacts contact_details[100];
    int contact_count;
} AddressBook;

/* Function declarations */
int create_contact(AddressBook *); // create function declaration
void list_contacts(AddressBook *);//list function declaration
int search_contacts(AddressBook *);//search function declaration
int edit_contact(AddressBook *);//edit function declaration
int delete_contact(AddressBook *);//delete function declaration
int load_contacts(AddressBook *);//load function declaration
int save_contacts(AddressBook *);//save function declaration

int validate_name(char *name);//validate_name function declaration
int validate_number(char *number);//validate_number function declaration
int validate_email(char *email);//validate_email function declaration

int unique_number(char *number,AddressBook *addressbook);//unique_number function declaration
int unique_email(char *email,AddressBook *addressbook);//unique_email function declaration


#endif // CONTACT_H
       // CONTACT_H