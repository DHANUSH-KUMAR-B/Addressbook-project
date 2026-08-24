#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) // Save all contacts into CSV file
{
    FILE *fp = fopen("contacts.csv", "w");

    if(fp == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }

    fprintf(fp, "%d\n", addressBook->contactCount);   // Store total number of contacts in the first line
    
    // Store each contact in CSV format
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fp);

    printf("Contacts saved successfully!\n");

}

void loadContactsFromFile(AddressBook *addressBook)   // Load contacts from CSV file
{
    FILE *fp = fopen("contacts.csv", "r");

    if(fp == NULL)
    {
        printf("No contacts file found.\n");
        return;
    }

    fscanf(fp, "%d\n", &addressBook->contactCount);  // Read total contact count from first line

    // Read each contact from the CSV file
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fp);

}
