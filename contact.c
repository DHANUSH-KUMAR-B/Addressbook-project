#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"contact.h"
#include"file.h"
#include"populate.h"

int validation(char str[])
{
    for(int i=0;str[i];i++)
    {
        if(!((str[i]>='A' && str[i]<='Z') ||
             (str[i]>='a' && str[i]<='z') ||
             (str[i]==' ') || (str[i]==',') ))
        {
            printf("Invalid Name!\nRetype the Name\n");
            return 1;
        }
    }
    return 0;
}

int validate_Phone(AddressBook *addressBook,char *str1)
{
    int len=strlen(str1);

    if(len!=10)
    {
        return 1;
    }

    for(int i=0;i<len;i++)
    {
        if(str1[i]<'0' || str1[i]>'9')
        {
            return 2;
        }
    }

    return 0;
}

int validate_email(AddressBook *addressBook,char *str2)
{
    int i;
    int at_count=0;
    int dot_count=0;
    char *at=strchr(str2,'@');
    char *dot=strchr(str2,'.');

    if(str2[0]>='0' && str2[0]<='9')
    {
        return 1;
    }

    for(i=0;str2[i];i++)
    {
        if(str2[i]=='@')
            at_count++;

        if(str2[i]=='.')
            dot_count++;

        if(!((str2[i]>='a' && str2[i]<='z') ||
             (str2[i]>='0' && str2[i]<='9') ||
             str2[i]=='@' || str2[i]=='.'))
        {
            return 4;
        }
    }

    if(at_count!=1)
    {
        return 2;
    }

    if(dot_count!=1)
    {
        return 3;
    }

    if(at==NULL || dot==NULL)
    {
        return 2;
    }

    if(at==str2)
    {
        return 8;
    }

    if(at>dot)
    {
        return 7;
    }

    if(dot<=at+1)
    {
        return 5;
    }

    if(strcmp(dot,".com")!=0)
    {
        return 6;
    }

    return 0;
}

int search_phone(AddressBook *addressBook)
{
    char str1[20];

    printf("Enter the Phone number to search:\n");
    scanf("%19s",str1);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,str1)==0)
        {
            printf("-----------------------------------------------------------------------------\n");
            printf("| %-3s | %-25s | %-10s | %-25s |\n",
                   "S.No","Name","Phone","Email");
            printf("-----------------------------------------------------------------------------\n");

            printf("| %-3d | %-25s | %-10s | %-25s |\n",
                   i+1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            printf("-----------------------------------------------------------------------------\n");

            return i;
        }
    }

    printf("Number not found!!\n");
    return -1;
}

int search_name(AddressBook *addressBook)
{
    char str[50];
    int found=0;
    int index=-1;

    printf("Enter the name to search:\n");
    scanf(" %[^\n]",str);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].name,str)==0)
        {
            printf("-----------------------------------------------------------------------------\n");
            printf("| %-3s | %-25s | %-10s | %-25s |\n",
                   "S.No","Name","Phone","Email");
            printf("-----------------------------------------------------------------------------\n");

            printf("| %-3d | %-25s | %-10s | %-25s |\n",
                   i+1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            printf("-----------------------------------------------------------------------------\n");

            found++;
            index=i;
        }
    }

    if(found==0)
    {
        printf("Name not found!!\n");
        return -1;
    }

    if(found==1)
    {
        return index;
    }

    if(found>1)
    {
        char phone[20];

        printf("Multiple contact with the same name\n");
        printf("Enter the phone number to view the contact\n");
        scanf("%19s",phone);

        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].name,str)==0 &&
               strcmp(addressBook->contacts[i].phone,phone)==0)
            {
                return i;
            }
        }
    }

    return -1;
}

int unique_Phone(AddressBook *addressBook,char *phone)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone)==0)
        {
            return 0;
        }
    }

    return 1;
}

int unique_email(AddressBook *addressBook,char *email)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,email)==0)
        {
            return 0;
        }
    }

    return 1;
}

int search_email(AddressBook *addressBook)
{
    char str2[50];

    printf("Enter the email ID to search:\n");
    scanf("%49s",str2);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,str2)==0)
        {
            printf("-----------------------------------------------------------------------------\n");
            printf("| %-3s | %-25s | %-10s | %-25s |\n",
                   "S.No","Name","Phone","Email");
            printf("-----------------------------------------------------------------------------\n");

            printf("| %-3d | %-25s | %-10s | %-25s |\n",
                   i+1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            printf("-----------------------------------------------------------------------------\n");

            return i;
        }
    }

    printf("Email ID not found!!\n");
    return -1;
}

void inputname(char *name)
{
    while(1)
    {
        printf("Enter the name: ");
        scanf(" %[^\n]",name);

        if(validation(name)==0)
            break;
    }
}

void inputPhone(char *Phone)
{
    printf("Enter the Phone Number : ");
    scanf("%19s",Phone);
}

void inputemail(char *em)
{
    printf("Enter the Email        : ");
    scanf("%49s",em);
}

void listContacts(AddressBook *addressBook)
{
    AddressBook *a=addressBook;

    for(int i=0;i<a->contactCount-1;i++)
    {
        for(int j=0;j<a->contactCount-i-1;j++)
        {
            if(strcmp(a->contacts[j].name,a->contacts[j+1].name)>0)
            {
                Contact temp=a->contacts[j];
                a->contacts[j]=a->contacts[j+1];
                a->contacts[j+1]=temp;
            }
        }
    }

    printf("\n+------+--------------------------+---------------+-------------------------------------+\n");
    printf("| %-4s | %-24s | %-13s | %-35s |\n",
           "No","Name","Phone","Email");
    printf("+------+--------------------------+---------------+-------------------------------------+\n");

    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("| %-4d | %-24s | %-13s | %-35s |\n",
               i+1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("+------+--------------------------+---------------+-------------------------------------+\n");
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount=0;

    populateAddressBook(addressBook);

    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}

void createContact(AddressBook *addressBook)
{
    char name[30],Phone[20],email[50];

    printf("\n");
    printf("================================================================\n");
    printf("                 CREATE NEW CONTACT                             \n");
    printf("================================================================\n");

    inputname(name);

    while(1)
    {
        inputPhone(Phone);

        int res=validate_Phone(addressBook,Phone);

        if(res==1)
        {
            printf("\nPhone number length must have 10 digit!\n");
            printf("Please Type the number again...\n\n");
            continue;
        }

        if(res==2)
        {
            printf("\nPhone number must in only digits (0 to 9)\n");
            printf("Please Type the number again...\n\n");
            continue;
        }

        if(!unique_Phone(addressBook,Phone))
        {
            printf("Phone number already exists!\n\n");
            continue;
        }

        break;
    }

    while(1)
    {
        inputemail(email);

        int res=validate_email(addressBook,email);

        if(res==0)
        {
            if(!unique_email(addressBook,email))
            {
                printf("\nEmail already exists!\n");
                printf("\nPlease enter a different email.\n\n");
                continue;
            }

            break;
        }

        switch(res)
        {
            case 1:
                printf("Email should not start with a digit\n");
                break;

            case 2:
                printf("Email must contain exactly one '@'\n");
                break;

            case 3:
                printf("Email must contain exactly one '.'\n");
                break;

            case 4:
                printf("Email should contain only lowercase letters, digits, '@', and '.'\n");
                break;

            case 5:
                printf("There must be at least one character between '@' and '.'\n");
                break;

            case 6:
                printf("Email must end with '.com'\n");
                break;

            case 7:
                printf("'@' must appear before '.'\n");
                break;

            case 8:
                printf("'@' cannot be the first character\n");
                break;
        }

        printf("Please re-enter the email.\n\n");
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,Phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);

    addressBook->contactCount++;

    printf("\n");
    printf("================================================================\n");
    printf("              CONTACT CREATED SUCCESSFULLY                      \n");
    printf("================================================================\n");
}

int searchContact(AddressBook *addressBook)
{
    int choice=0;
    int ind;

    while(1)
    {
        printf("\n");
        printf("================================================================\n");
        printf("                     SEARCH CONTACT                             \n");
        printf("================================================================\n");
        printf("\n");

        printf("              1. Search by Name\n");
        printf("              2. Search by Phone Number\n");
        printf("              3. Search by Email\n");
        printf("              4. Exit\n");

        printf("\nEnter your choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                ind=search_name(addressBook);
                return ind;

            case 2:
                ind=search_phone(addressBook);
                return ind;

            case 3:
                ind=search_email(addressBook);
                return ind;

            case 4:
                return -1;

            default:
                printf("Invalid choice!\nPlease try again!\n");
        }
    }
}

void editContact(AddressBook *addressBook)
{
    int ind;

    ind=searchContact(addressBook);

    if(ind==-1)
        return;

    char name[40],phone[20],email[50];
    int c;

    printf("\n");
    printf("================================================================\n");
    printf("                      EDIT CONTACT                              \n");
    printf("================================================================\n");

    printf("1. Edit Name\n");
    printf("2. Edit Phone Number\n");
    printf("3. Edit Email\n");
    printf("4. Exit\n");

    printf("Enter ur choice : ");
    scanf("%d",&c);

    switch(c)
    {
        case 1:

            inputname(name);

            strcpy(addressBook->contacts[ind].name,name);

            printf("CONTACT EDITED SUCCESSFULLY\n");
            return;

        case 2:

            while(1)
            {
                inputPhone(phone);

                int res=validate_Phone(addressBook,phone);

                if(res==1)
                {
                    printf("Phone number length must have 10 digit!\n");
                    continue;
                }

                if(res==2)
                {
                    printf("Phone number must in only digits (0 to 9)\n");
                    continue;
                }

                int flag=0;

                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(i!=ind &&
                       strcmp(addressBook->contacts[i].phone,phone)==0)
                    {
                        flag=1;
                        break;
                    }
                }

                if(flag)
                {
                    printf("Phone number already exists!\n");
                    continue;
                }

                break;
            }

            strcpy(addressBook->contacts[ind].phone,phone);

            printf("CONTACT EDITED SUCCESSFULLY\n");
            return;

        case 3:

            while(1)
            {
                inputemail(email);

                int res=validate_email(addressBook,email);

                if(res!=0)
                {
                    printf("Invalid Email! Please try again.\n");
                    continue;
                }

                int flag=0;

                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(i!=ind &&
                       strcmp(addressBook->contacts[i].email,email)==0)
                    {
                        flag=1;
                        break;
                    }
                }

                if(flag)
                {
                    printf("Email already exists!\n");
                    continue;
                }

                break;
            }

            strcpy(addressBook->contacts[ind].email,email);

            printf("CONTACT EDITED SUCCESSFULLY\n");
            return;

        case 4:
            return;

        default:
            printf("Invalid choice\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
    int ind;
    char choice;

    ind=searchContact(addressBook);

    if(ind==-1)
        return;

    printf("\nPlease confirm to delete the contact ( Y / N ): ");
    scanf(" %c",&choice);

    if(choice=='y' || choice=='Y')
    {
        for(int i=ind;i<addressBook->contactCount-1;i++)
        {
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }

        addressBook->contactCount--;

        printf("\n");
        printf("================================================================\n");
        printf("              CONTACT DELETED SUCCESSFULLY                     \n");
        printf("================================================================\n");
    }
    else
    {
        printf("\n");
        printf("================================================================\n");
        printf("                  DELETION CANCELLED                            \n");
        printf("================================================================\n");
    }
}