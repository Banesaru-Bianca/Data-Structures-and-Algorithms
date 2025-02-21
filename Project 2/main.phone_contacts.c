#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structure for a phone contact
struct Contact {
    char name[30];
    char number[15];
    struct Contact *prev;
    struct Contact *next;
};

//Structure for the phone book
struct PhoneBook {
    struct Contact *head;
};

//Ensuring that the correct number and types of arguments are provided
void displayPhoneBook(struct PhoneBook *phoneBook);
void insertContact(struct PhoneBook *phoneBook);
void updateContact(struct PhoneBook *phoneBook, char name[]);
void deleteContact(struct PhoneBook *phoneBook, char name[]);
void searchByName(struct PhoneBook *phoneBook, char name[]);


//Function to insert a new contact
void insertContact(struct PhoneBook *phoneBook) {
    //Allocate memory for a new contact
    struct Contact *newContact = (struct Contact *)malloc(sizeof(struct Contact));

    //Ask user to enter contact details
    printf("Enter the name: ");
    scanf("%s", newContact->name);

    printf("Enter the number: ");
    scanf("%s", newContact->number);

    newContact->prev = NULL;
    newContact->next = phoneBook->head;

    if (phoneBook->head != NULL) {
        phoneBook->head->prev = newContact;
    }

    phoneBook->head = newContact;
    
    printf("Contact added successfully!\n");
}

//Function to update contact details
void updateContact(struct PhoneBook *phoneBook, char name[]) {
//Start with the first contact in the list
struct Contact *current = phoneBook->head;

//Traverse the list to find the contact to update
while (current != NULL) {
    //Check if the current contact's name matches the specified name
    if (strcmp(name, current->name) == 0) {
        //Ask user to enter new contact details
        printf("Enter the new name: ");
        scanf("%s", current->name);

        printf("Enter the new number: ");
        scanf("%s", current->number);

        //Display success message and return from the function
        printf("Contact updated successfully!\n");
        return;
    }

//Move to the next contact in the list
current = current->next;
}

    printf("Contact not found.\n");
}

//Function to delete a contact
void deleteContact(struct PhoneBook *phoneBook, char name[]) {
struct Contact *current = phoneBook->head;
    
//Traverse the list to find the contact to delete
while (current != NULL) {
    //Check if the current contact's name matches the specified name
    if (strcmp(name, current->name) == 0) {
        if (current->prev != NULL) {
            current->prev->next = current->next;
        } else {
            phoneBook->head = current->next;
        }

        if (current->next != NULL) {
            current->next->prev = current->prev;
        }

        free(current);
        printf("Contact deleted successfully!\n");
        return;
    }
current = current->next;
}

printf("Contact not found.\n");

}


//Function to search contacts by name
void searchByName(struct PhoneBook *phoneBook, char name[]) {
    struct Contact *current = phoneBook->head;
    int found = 0;

while (current != NULL) {
    if (strcmp(name, current->name) == 0) {
        printf("Contact found!\n");
        printf("Name: %s, Number: %s\n", current->name, current->number);
        found = 1;
    }
    current = current->next;
}

if (!found) {
    printf("Contact not found.\n");
}
}

// Function to sort alphabetically
void sortPhoneBook(struct PhoneBook *phoneBook) {
    struct Contact *current, *index;
    char tempName[30], tempNumber[15];

    if (phoneBook->head == NULL) {
        // Empty phone book, nothing to sort
        return;
    }

for (current = phoneBook->head; current->next != NULL; current = current->next) {
    for (index = current->next; index != NULL; index = index->next) {
        if (strcmp(current->name, index->name) > 0) {
            // Swap names
            strcpy(tempName, current->name);
            strcpy(current->name, index->name);
            strcpy(index->name, tempName);

            // Swap numbers
            strcpy(tempNumber, current->number);
            strcpy(current->number, index->number);
            strcpy(index->number, tempNumber);
        }
      }
   }
}

int main() {
    struct PhoneBook phoneBook;
    phoneBook.head = NULL;

    int choice;
    char name[30];

    do {
        printf("\nPhone Contacts Tracking System Menu:\n");
        printf("--------------------------------------\n");
        printf("|1. Display Phone Book               |\n");
        printf("--------------------------------------\n");
        printf("|2. Insert New Contact               |\n");
        printf("--------------------------------------\n");
        printf("|3. Update Contact                   |\n");
        printf("--------------------------------------\n");
        printf("|4. Delete Contact                   |\n");
        printf("--------------------------------------\n");
        printf("|5. Search by Name                   |\n");
        printf("--------------------------------------\n");
        printf("|6. Sort alphabetically              |\n");
        printf("--------------------------------------\n");
        printf("|0. Exit                             |\n");
        printf("--------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayPhoneBook(&phoneBook);
                break;
            case 2:
                insertContact(&phoneBook);
                break;
            case 3:
                printf("Enter the name of the contact to update: ");
                scanf("%s", name);
                updateContact(&phoneBook, name);
                break;
            case 4:
                printf("Enter the name of the contact to delete: ");
                scanf("%s", name);
                deleteContact(&phoneBook, name);
                break;
            case 5:
                printf("Enter the name to search: ");
                scanf("%s", name);
                searchByName(&phoneBook, name);
                break;
            case 6:
                sortPhoneBook(&phoneBook);
                printf("Phone book sorted alphabetically.\n");
                break;
            case 0:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

// Function to display the phone book
void displayPhoneBook(struct PhoneBook *phoneBook) {
    struct Contact *current = phoneBook->head;

    if (current == NULL) {
        printf("Phone book is empty.\n");
        return;
    }

    printf("Phone Book:\n");
    while (current != NULL) {
        printf("Name: %s, Number: %s\n", current->name, current->number);
        current = current->next;
    }
    
}
