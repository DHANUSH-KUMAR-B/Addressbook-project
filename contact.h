#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount; 
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void inputname(char *name);
void inputPhone(char *Phone); 
void inputemail(char *em);     
int validation(char str[]);   
int validate_Phone(AddressBook *addressBook,char *str1);    
int validate_email(AddressBook *addressBook,char *str2); 
int validate_name(char *str);
int unique_Phone(AddressBook *addressBook,char *phone);
int unique_email(AddressBook *addressBook,char *email);

#endif
