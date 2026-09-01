#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook/*, int sortCriteria*/) 
{
    // Sort contacts based on the chosen criteria
    printf("================================ADDRESS BOOK================================\n");
    printf("                                 _SHREYAS_                \n");
    printf("============================================================================\n");
    printf("%-5s %-5s %-15s %-5s %-15s %-5s %-15s\n","No", "|","Name","|","Phone No","|","Email");
    printf("============================================================================\n");

    for(int i=0; i<addressBook->contactCount; i++)
    {
        printf("%-5d %-5c %-15s %-5c %-15s %-5c %-15s\n",i+1,'|',addressBook->contacts[i].name,'|',addressBook->contacts[i].phone,'|',addressBook->contacts[i].email);
    }
    printf("============================================================================\n");
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    char name[50];
    char phone[50];
    char mail[50];
    int i;
    int valid;

    while (1)   // for name 
    {
        valid = 1;
        printf("Enter name to create contact : ");
        getchar(); 
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = '\0';
        for (i = 0; name[i] != '\0'; i++)
        {
            if (!isalpha(name[i]) && name[i] != ' ')
            {
                valid = 0;
                break;
            }
        }

        if (valid == 1 && strlen(name) > 0)
        {
            break;   // valid name
        }
        printf("Invalid name! Please enter a valid name.\n");
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);


    while (1)    // for phone number
    {
        valid = 1;

        printf("Enter phone number to create contact : ");

        fgets(phone, 50, stdin);
        phone[strcspn(phone, "\n")] = '\0';

        if (strlen(phone) != 10) // checking digits has 10 digits / wt
        {
            valid = 0;
        }
        
        if (valid == 1)
        {
            for (i = 0; phone[i] != '\0'; i++)
            {
                if (!isdigit(phone[i]))
                {
                    valid = 0;
                    break;
                }
            }
        }

        if (valid == 1)
        {
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(phone,
                           addressBook->contacts[i].phone) == 0)
                {
                    valid = 0;
                    printf("Phone number already exists!\n");
                    break;
                }
            }
        }

        if (valid == 1)
        {
            break;  
        }
        printf("Invalid number! Please enter a valid number.\n");
    }

    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);


    while (1) //for mail
    {
        valid = 1;

        printf("Enter Email to create contact : ");

        fgets(mail, 50, stdin);
        mail[strcspn(mail, "\n")] = '\0';

        char *at = strchr(mail, '@');
        char *dot = strchr(mail, '.');

        if (at == NULL || dot == NULL)
        {
            valid = 0;
        }
        else if (at > dot)
        {
            valid = 0;
        }
        else if (at == mail)
        {
            valid = 0;
        }
        else if (dot == at + 1)
        {
            valid = 0;
        }
        else if (*(dot + 1) == '\0')
        {
            valid = 0;
        }

        if (valid == 1)
        {
            break;  
        }

        printf("Invalid email! Please enter a valid email.\n");
    }

    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);

    addressBook->contactCount++;

    printf("\n");
    printf("<== Contact Created Successfully ==>\n");


}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char namee[50];
    int index;
    printf("search contact By :\n 1.Name\n 2.Phone NO\n 3.Email\n");
    printf("Enter Your Choice : ");
    scanf("%d", &choice);
    getchar();
    switch(choice){
        case 1:
            printf("Enter Name To Search : ");
            fgets(namee, 50, stdin);
            namee[strcspn(namee, "\n")] = '\0';
            index = search_contact(addressBook, namee);
            break;

        case 2:
            printf("Enter phone number To Search : ");
            fgets(namee, 50, stdin);
            namee[strcspn(namee, "\n")] = '\0';
            index = search_contact(addressBook, namee);
            break;
            
        case 3:
            printf("Enter email To Search : ");
            fgets(namee, 50, stdin);
            namee[strcspn(namee, "\n")] = '\0';
            index = search_contact(addressBook, namee);
            break;

        default:
            printf("Invalid choice\n");
            return;
        }
    
        if(index != -1)
        {
            printf("\n");
            printf("%-5d %-15s %-15s %-15s\n",index + 1,addressBook->contacts[index].name,
               addressBook->contacts[index].phone,addressBook->contacts[index].email);
        }
        else
        {
            printf("Invalid User\n");
        }
}

void editContact(AddressBook *addressBook)
{
    char name[50];
    char phone[50];
    char mail[50];
    int choice, i, valid;
    int index;

    printf("Enter name : ");
    getchar();
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';
    index = search_contact(addressBook, name);

    if(index == -1)
    {
        printf("Invalid User\n");
        return;
    }

    printf("Edit Contact By :\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter Your Choice : ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            valid = 1;

            printf("Enter name to edit : ");
            getchar();
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = '\0';

            for(i = 0; name[i] != '\0'; i++)
            {
                if(!isalpha(name[i]) && name[i] != ' ')
                {
                    valid = 0;
                    break;
                }
            }

            if(valid == 1)
            {
                strcpy(addressBook->contacts[index].name, name);
                printf("\n");
                printf("Name Edited Successfully\n");
                printf("\n");
            }
            else
            {
                printf("\n");
                printf("Invalid name : Please enter valid name\n");
                printf("\n");
                return;
            }
            break;


        case 2:
            valid = 1;

            printf("Enter Phone number to edit : ");
            getchar();
            fgets(phone, 50, stdin);
            phone[strcspn(phone, "\n")] = '\0';

            if(strlen(phone) != 10)
            {
                valid = 0;
            }

            if(valid == 1)
            {
                for(i = 0; phone[i] != '\0'; i++)
                {
                    if(!isdigit(phone[i]))
                    {
                        valid = 0;
                        break;
                    }
                }
            }

            if(valid == 1)
            {
                for(i = 0; i < addressBook->contactCount; i++)
                {
                    if(i != index &&
                       strcmp(phone, addressBook->contacts[i].phone) == 0)
                    {
                        valid = 0;
                        break;
                    }
                }
            }

            if(valid == 1)
            {
                strcpy(addressBook->contacts[index].phone, phone);
                printf("\n");
                printf("Phone number edited Successfully\n");
                printf("\n");
            }
            else
            {
                printf("\n");
                printf("Invalid number : Please enter valid number\n");
                printf("\n");
                return;
            }
            break;


        case 3:
            valid = 1;

            printf("Enter Email to edit : ");
            getchar();
            fgets(mail, 50, stdin);
            mail[strcspn(mail, "\n")] = '\0';

            if(strchr(mail, '@') != NULL &&
               strchr(mail, '.') != NULL)
            {
                valid = 1;
            }
            else
            {
                valid = 0;
            }

            if(valid == 1)
            {
                strcpy(addressBook->contacts[index].email, mail);
                printf("\n");
                printf("Email edited Successfully\n");
                printf("\n");
            }
            else
            {
                printf("\n");
                printf("Invalid email : Please enter valid email\n");
                printf("\n");
                return;
            }
            break;


        default:
            printf("Invalid choice\n");
            return;
    }

    saveContactsToFile(addressBook);
}
void deleteContact(AddressBook *addressBook)
{
    int choice;
    int index;
    char namee[50];

    while(1)
    {
        printf("Delete Contact By :\n");
        printf("1.Name\n");
        printf("2.Phone\n");
        printf("3.Email\n");
        printf("Enter your Choice : ");
        scanf("%d", &choice);
        getchar();

        if(choice < 1 || choice > 3)
        {
            printf("Invalid choice : Please enter valid choice\n");
            continue;
        }

        if(choice == 1)
        {
            printf("Enter name to delete : ");
            fgets(namee, 50, stdin);
            namee[strcspn(namee, "\n")] = '\0';
        }
        else if(choice == 2)
        {
            printf("Enter phone number To Search : ");
            fgets(namee, 50, stdin);
            namee[strcspn(namee, "\n")] = '\0';
        }
        else if(choice == 3)
        {
            printf("Enter email To Search : ");
            fgets(namee, 50, stdin);
            namee[strcspn(namee, "\n")] = '\0';
        }

        index = search_contact(addressBook, namee);

        if(index == -1)
        {
            printf("Contact Not Found : Cannot Delete\n");
            return;
        }

        for(int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("\n");
        printf("<== Contact deleted Successfully ==>\n");
        printf("\n");

        saveContactsToFile(addressBook);

        return;
    }
}



int search_contact(AddressBook *addressBook, char namee[])
{
    int i;

    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(namee, addressBook->contacts[i].name) == 0 ||
           strcmp(namee, addressBook->contacts[i].phone) == 0 ||
           strcmp(namee, addressBook->contacts[i].email) == 0)
        {
            return i;
        }
    }

    return -1;
}