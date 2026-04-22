#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

int validate_name(char *name)
{
    int i=0;
    int found=0;

    while(name[i] !='\0' && name[i] !='\n')
    {
        if((name[i] >='A' && name[i] <='Z') || (name[i] >='a' && name[i] <='z') || name[i]==' ')
        {
            found=1;
        }
        else
        {
            found=0;
            break;
        }
        i++;
    }

    return found;
}

int validate_phone(char *phone)
{
    int i=0;
    int found=0;

    if( phone[0] >='6' && phone[0] <='9' )
    {

    while(phone[i] !='\0' && phone[i] !='\n')
    {
        if(phone[i] >='0' && phone[i] <='9'  )
        {
            found=1;
        }
        else
        {
            found=0;
            break;
        }
        i++;
    }
    }
    else
    {
        return 0;
    }

    if(i != 10)
    {
        found=0;
    }


    return found;

}

int validate_Email(char *Email)
{
    int i=0;
    int at_count=0;
    
    if(Email[0] >= 'a' && Email[0] <= 'z')
    {
    while(Email[i] !='\0' && Email[i] !='\n')
    {
        if(Email[i]== '@' )
        {
            at_count++;
        }    
        i++;
    }

    char *res = strstr(Email,".com");
    
    if(at_count > 1 || at_count ==0 )
    {
        return 0;
    }

    if(res != NULL)
    {
        return 1;
    }

    if(res == NULL)
    {
        return 0;
    }
    }
    else
    {
        return 0;
    }

    return 0;

}

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria

    printf("-----------------------------------------------------\n");
    printf("  %-15s %-15s %-20s\n","NAME","PHONE","E-MAIL");
    printf("-----------------------------------------------------\n");

    for(int i=0; i<(addressBook->contactCount); i++)
    {
        printf("%d",i+1);
        printf(" %-15s",addressBook->contacts[i].name);
        printf(" %-15s",addressBook->contacts[i].phone);
        printf(" %-20s\n",addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("AdressBook is Full\n");
        return;
    }

    getchar();
    
    char name[30];
    char phone[15];
    char Email[20];

    for(int i=0; i<3; i++)
    {
        printf("Attempt %d, Enter the name: ", i+1);
        fgets(name,sizeof(name),stdin);
        name[strcspn(name, "\n")] = '\0';

        int res_name = validate_name(name);

        if(res_name == 1 )
        {
            break;
        }
        else
        {
            printf("Invalid name! only alphabtes are allowed\n");
        }
        
        if(i == 2)
        {
            printf("You complted 3 attempts!\n");
            return;
        }
    }

    for(int i=0; i<3; i++)
    {
        printf("Attempt %d, Enter the Phone number: ", i+1);
        fgets(phone,sizeof(phone),stdin);
        phone[strcspn(phone, "\n")] = '\0';

        int res_phone = validate_phone(phone);

        if(res_phone == 1 )
        {
            break;
        }
         else
        {
            printf("Invalid number! the number must be 10 digits and start with 6-9\n");
        }
        
        if(i == 2)
        {
            printf("3 attempts\n");
            return;
        }
    }

    for(int i=0; i<3; i++)
    {
        printf("Attempt %d, Enter the Email: ", i+1);
        fgets(Email,sizeof(Email),stdin);
        Email[strcspn(Email, "\n")] = '\0';

        int res_Email = validate_Email(Email);

        if(res_Email == 1)
        {
             break;
        }
         else
        {
            printf("Invalid Email! Enter the valid Email\n");
        }

        if( i == 2)
        {
            printf(" 3 attempts\n");
            return;
        }
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, Email);
    addressBook->contactCount++;

   /* printf("\n Name = %s\n",addressBook->contacts[addressBook->contactCount-1].name);
    printf(" Phone = %s\n",addressBook->contacts[addressBook->contactCount-1].phone);
    printf(" Email = %s\n",addressBook->contacts[addressBook->contactCount-1].email); */
    
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */

    int option;
    char name[30];
    char phone[15];
    char Email[30];
    printf(" 1.Search by name\n 2.Search by Phone\n 3.Search by Email\n");
    scanf("%d",&option);
    getchar();

    switch(option)
    {
        case 1:
         {
            printf("Enter the Name: ");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")]='\0';
            int res = validate_name(name);
            
            if(res == 1)
            {
                int found=0;
                for(int i=0; i<(addressBook->contactCount);i++)
                {
                    int str = strcmp(name, (addressBook->contacts[i].name));
                    
                        if(str==0)
                        {
                        found=1;
                        printf("Name: %s\n",addressBook->contacts[i].name);
                        printf("Phone: %s\n",addressBook->contacts[i].phone);
                        printf("Email: %s\n",addressBook->contacts[i].email);
                        break;
                        }
                    
                }

                if(found==0)
                {
                    printf("Contact not found\n");
                    return;
                }
            }
            else
            {
                printf("Invalid name\n");
            }
            break;
         }
        case 2: 
        {
            printf("Enter the Phone: ");
            fgets(phone,sizeof(phone),stdin);
            phone[strcspn(phone, "\n")]='\0';
            int res = validate_phone(phone);

            
             if(res == 1)
            {
                int found=0;
                for(int i=0; i<(addressBook->contactCount);i++)
                {
                    int str = strcmp(phone, (addressBook->contacts[i].phone));
                    
                        if(str==0)
                        {
                        found=1;
                        printf("Name: %s\n",addressBook->contacts[i].name);
                        printf("Phone: %s\n",addressBook->contacts[i].phone);
                        printf("Email: %s\n",addressBook->contacts[i].email);
                        break;
                        }
                    
                }

                if(found==0)
                {
                    printf("Contact not found\n");
                    return;
                }
            }
            else
            {
                printf("Invalid phone number\n");
            }
            break;
        }

        case 3:
        {
            printf("Enter the Email: ");
            fgets(Email,sizeof(Email),stdin);
            Email[strcspn(Email, "\n")]='\0';
            int res = validate_Email(Email);
            if(res == 1)
            {
                int found=0;
                for(int i=0; i<(addressBook->contactCount);i++)
                {
                   int str = strcmp(Email, (addressBook->contacts[i].email));
                       
                   if(str==0)
                        {
                        found=1;
                        printf("Name: %s\n",addressBook->contacts[i].name);
                        printf("Phone: %s\n",addressBook->contacts[i].phone);
                        printf("Email: %s\n",addressBook->contacts[i].email);
                        break;
                        }
                    
                }

                if(found==0)
                {
                    printf("Contact not found\n");
                    return;
                }
            }
            else
            {
                printf("Invalid Email\n");
            }
            break;
        }

        default:
        {
            printf("Invalid Input!\n");
        }

    }
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    int option;
    char name[30];
    char phone[15];
    char Email[30];
    int index[20];
    int j=0;
    int serial_num;
    printf(" 1.Search by name\n 2.Search by Phone\n 3.Search by Email\n");
    scanf("%d",&option);
    getchar();

    switch(option)
    {
        case 1:
         {
            printf("Enter the Name: \n");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")]='\0';

            int count=1;
                for(int i=0; i<(addressBook->contactCount);i++)
                {
                    int str = strcmp(name, (addressBook->contacts[i].name));
                    
                        if(str==0)
                        {
                            index[j++]=i;
                            printf("%d.",count++);
                        printf("Name: %s\n",addressBook->contacts[i].name);
                        printf("Phone: %s\n",addressBook->contacts[i].phone);
                        printf("Email: %s\n",addressBook->contacts[i].email);
                        printf("\n");
                        }
                }
        }

                break;
        case 2: 
        {
            printf("Enter the Phone: ");
            fgets(phone,sizeof(phone),stdin);
            phone[strcspn(phone, "\n")]='\0';
            int count=1;

                for(int i=0; i<(addressBook->contactCount);i++)
                {
                    int str = strcmp(phone, (addressBook->contacts[i].phone));
                    
                        if(str==0)
                        {
                            index[j++]=i;
                            printf("%d.",count++);
                        printf("Name: %s\n",addressBook->contacts[i].name);
                        printf("Phone: %s\n",addressBook->contacts[i].phone);
                        printf("Email: %s\n",addressBook->contacts[i].email);
                        printf("\n");
                        }
                }
        } 
            break;
    
        case 3:
        {
            printf("Enter the Email: ");
            fgets(Email,sizeof(Email),stdin);
            Email[strcspn(Email, "\n")]='\0';
            int count=1;
    
                for(int i=0; i<(addressBook->contactCount);i++)
                {
                   int str = strcmp(Email, (addressBook->contacts[i].email));
                       
                   if(str==0)
                   {
                        index[j++]=i;
                        printf("%d.",count++);
                        printf("Name: %s\n",addressBook->contacts[i].name);
                        printf("Phone: %s\n",addressBook->contacts[i].phone);
                        printf("Email: %s\n",addressBook->contacts[i].email);
                        printf("\n");
                   }
                }
        }
            break;

        default:
        {
            printf("Invalid Input!\n");
        }
    }

    printf("Enter the Serial number: \n");
    scanf("%d",&serial_num);

    printf(" 1.Edit by name\n 2.Edit by phone\n 3.Edit by Email\n");
    scanf("%d",&option);
    getchar();

    
    switch(option)
    {
        case 1:
         {
            printf("Enter the Name: \n");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")]='\0';

            int res = validate_name(name);

            if(res == 1)
            {
                strcpy(addressBook->contacts[index[serial_num - 1]].name, name);
                printf("Update successfully\n");
            }
            else
            {
                printf("Enter the valid name!\n");
            }
        }

                break;
        case 2: 
        {
            printf("Enter the Phone: ");
            fgets(phone,sizeof(phone),stdin);
            phone[strcspn(phone, "\n")]='\0';

            int res = validate_phone(phone);

            
            if(res == 1)
            {
                strcpy(addressBook->contacts[index[serial_num - 1]].phone, phone);
                printf("Update successfully\n");
            }
            else
            {
                printf("Enter the valid Phone number!\n");
            }
            
        } 
            break;
    
        case 3:
        {
            printf("Enter the Email: ");
            fgets(Email,sizeof(Email),stdin);
            Email[strcspn(Email, "\n")]='\0';

            int res = validate_Email(Email);

            
            if(res == 1)
            {
                strcpy(addressBook->contacts[index[serial_num - 1]].email, Email);
                printf("Update successfully\n");
            }
            else
            {
                printf("Enter the valid Email!\n");
            }
           
        }
            break;

        default:
        {
            printf("Invalid Input!\n");
        }
    }

 
}
    

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

    
    int option;
    char name[30];
    char phone[15];
    char Email[30];
    int index[20];
    int j=0;
    int serial_num;
    printf(" 1.Search by name\n 2.Search by Phone\n 3.Search by Email\n");
    scanf("%d",&option);
    getchar();

    switch(option)
    {
        case 1:
         {
            printf("Enter the Name: \n");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")]='\0';

            int count=1;
                for(int i=0; i<(addressBook->contactCount);i++)
                {
                    int str = strcmp(name, (addressBook->contacts[i].name));
                    
                        if(str==0)
                        {
                            index[j++]=i;
                            printf("%d.",count++);
                        printf("Name: %s\n",addressBook->contacts[i].name);
                        printf("Phone: %s\n",addressBook->contacts[i].phone);
                        printf("Email: %s\n",addressBook->contacts[i].email);
                        printf("\n");
                        }
                }
        }

                break;
        case 2: 
        {
            printf("Enter the Phone: ");
            fgets(phone,sizeof(phone),stdin);
            phone[strcspn(phone, "\n")]='\0';
            int count=1;

                for(int i=0; i<(addressBook->contactCount);i++)
                {
                    int str = strcmp(phone, (addressBook->contacts[i].phone));
                    
                        if(str==0)
                        {
                            index[j++]=i;
                            printf("%d.",count++);
                        printf("Name: %s\n",addressBook->contacts[i].name);
                        printf("Phone: %s\n",addressBook->contacts[i].phone);
                        printf("Email: %s\n",addressBook->contacts[i].email);
                        printf("\n");
                        }
                }
        } 
            break;
    
        case 3:
        {
            printf("Enter the Email: ");
            fgets(Email,sizeof(Email),stdin);
            Email[strcspn(Email, "\n")]='\0';
            int count=1;
    
                for(int i=0; i<(addressBook->contactCount);i++)
                {
                   int str = strcmp(Email, (addressBook->contacts[i].email));
                       
                   if(str==0)
                   {
                        index[j++]=i;
                        printf("%d.",count++);
                        printf("Name: %s\n",addressBook->contacts[i].name);
                        printf("Phone: %s\n",addressBook->contacts[i].phone);
                        printf("Email: %s\n",addressBook->contacts[i].email);
                        printf("\n");
                   }
                }
        }
            break;

        default:
        {
            printf("Invalid Input!\n");
        }
    }

    printf("Enter the Serial number: \n");
    scanf("%d",&serial_num);

   for(int i = index[serial_num-1]; i<(addressBook->contactCount)-1; i++)
   {
    int j=i+1;

    strcpy(addressBook->contacts[i].name, addressBook->contacts[j].name);
    strcpy(addressBook->contacts[i].phone, addressBook->contacts[j].phone);
    strcpy(addressBook->contacts[i].email, addressBook->contacts[j].email);
   }

   addressBook->contactCount--;
}

