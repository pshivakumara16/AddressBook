#include <stdio.h>
#include<string.h>
#include "file.h"
#include "contact.h"

void saveContactsToFile(AddressBook *addressBook)
 {
  
    FILE *fp = fopen("contacts.txt", "w");

    if(fp == NULL)
    {
        printf("doesnot oprn the file\n");
        return;
    }
    fprintf(fp, "contactCount %d\n",addressBook->contactCount);

    for(int i=0; i<addressBook->contactCount; i++)
    {
        fprintf(fp, "%s\n",addressBook->contacts[i].name);
        fprintf(fp, "%s\n",addressBook->contacts[i].phone);
        fprintf(fp, "%s\n",addressBook->contacts[i].email);
    }

    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
 
    FILE *fp = fopen("contacts.txt","r");

    if(fp == NULL)
    {
        return;
    }

    fscanf(fp, "contactCount %d\n",&addressBook->contactCount);

    if(addressBook->contactCount < 0 || addressBook->contactCount > MAX_CONTACTS)
    {
        addressBook->contactCount = 0;
        fclose(fp);
        return;
    }

    
       for(int i = 0; i < addressBook->contactCount; i++)
       {
        fgets(addressBook->contacts[i].name, sizeof(addressBook->contacts[i].name), fp);
        addressBook->contacts[i].name[strcspn(addressBook->contacts[i].name, "\n")] = '\0';

        fgets(addressBook->contacts[i].phone, sizeof(addressBook->contacts[i].phone), fp);
        addressBook->contacts[i].phone[strcspn(addressBook->contacts[i].phone, "\n")] = '\0';

        fgets(addressBook->contacts[i].email, sizeof(addressBook->contacts[i].email), fp);
        addressBook->contacts[i].email[strcspn(addressBook->contacts[i].email, "\n")] = '\0';
       }

    

    fclose(fp);
    

}
