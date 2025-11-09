#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PILOTS 100

// Structure for Pilot
struct Pilot {
    int id;
    char name[50];
    int age;
    char license[30];
    char phone[20];
};

// Global variables
struct Pilot pilots[MAX_PILOTS];
int pilotCount = 0;

// Function declarations
void menu();
void addPilot();
void viewPilots();
void modifyPilot();
void deletePilot();
void searchPilot();
void saveToFile();
void loadFromFile();

int main() {
    loadFromFile();  // Load data from file if exists
    menu();          // Show main menu
    return 0;
}

// Display menu
void menu() {
    int choice;
    do {
        printf("\n====== PILOT MANAGEMENT SYSTEM ======\n");
        printf("1. Add Pilot\n");
        printf("2. View All Pilots\n");
        printf("3. Search Pilot by ID\n");
        printf("4. Modify Pilot\n");
        printf("5. Delete Pilot\n");
        printf("6. Save Data\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: addPilot(); break;
            case 2: viewPilots(); break;
            case 3: searchPilot(); break;
            case 4: modifyPilot(); break;
            case 5: deletePilot(); break;
            case 6: saveToFile(); break;
            case 7:
                saveToFile();
                printf("\nExiting... Data saved successfully!\n");
                break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);
}

// Add a new pilot
void addPilot() {
    if (pilotCount >= MAX_PILOTS) {
        printf("Database full! Cannot add more pilots.\n");
        return;
    }

    struct Pilot p;

    printf("\nEnter Pilot ID: ");
    scanf("%d", &p.id);
    getchar();

    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();

    printf("Enter License Number: ");
    fgets(p.license, sizeof(p.license), stdin);
    p.license[strcspn(p.license, "\n")] = 0;

    printf("Enter Phone Number: ");
    fgets(p.phone, sizeof(p.phone), stdin);
    p.phone[strcspn(p.phone, "\n")] = 0;

    pilots[pilotCount++] = p;
    printf("\nPilot added successfully!\n");
}

// View all pilots
void viewPilots() {
    if (pilotCount == 0) {
        printf("\nNo pilots found.\n");
        return;
    }

    printf("\n----- LIST OF PILOTS -----\n");
    for (int i = 0; i < pilotCount; i++) {
        printf("\nPilot #%d\n", i + 1);
        printf("ID: %d\n", pilots[i].id);
        printf("Name: %s\n", pilots[i].name);
        printf("Age: %d\n", pilots[i].age);
        printf("License: %s\n", pilots[i].license);
        printf("Phone: %s\n", pilots[i].phone);
    }
}

// Search for a pilot by ID
void searchPilot() {
    int id;
    printf("\nEnter Pilot ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < pilotCount; i++) {
        if (pilots[i].id == id) {
            printf("\nPilot Found!\n");
            printf("ID: %d\n", pilots[i].id);
            printf("Name: %s\n", pilots[i].name);
            printf("Age: %d\n", pilots[i].age);
            printf("License: %s\n", pilots[i].license);
            printf("Phone: %s\n", pilots[i].phone);
            return;
        }
    }
    printf("\nPilot not found!\n");
}

// Modify pilot details
void modifyPilot() {
    int id;
    printf("\nEnter Pilot ID to modify: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < pilotCount; i++) {
        if (pilots[i].id == id) {
            printf("\nEditing details for Pilot ID %d\n", id);

            printf("Enter new name (current: %s): ", pilots[i].name);
            fgets(pilots[i].name, sizeof(pilots[i].name), stdin);
            pilots[i].name[strcspn(pilots[i].name, "\n")] = 0;

            printf("Enter new age (current: %d): ", pilots[i].age);
            scanf("%d", &pilots[i].age);
            getchar();

            printf("Enter new license (current: %s): ", pilots[i].license);
            fgets(pilots[i].license, sizeof(pilots[i].license), stdin);
            pilots[i].license[strcspn(pilots[i].license, "\n")] = 0;

            printf("Enter new phone (current: %s): ", pilots[i].phone);
            fgets(pilots[i].phone, sizeof(pilots[i].phone), stdin);
            pilots[i].phone[strcspn(pilots[i].phone, "\n")] = 0;

            printf("\nPilot details updated successfully!\n");
            return;
        }
    }

    printf("Pilot with ID %d not found!\n", id);
}

// Delete pilot by ID
void deletePilot() {
    int id;
    printf("\nEnter Pilot ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < pilotCount; i++) {
        if (pilots[i].id == id) {
            for (int j = i; j < pilotCount - 1; j++) {
                pilots[j] = pilots[j + 1];
            }
            pilotCount--;
            printf("Pilot deleted successfully!\n");
            return;
        }
    }
    printf("Pilot not found!\n");
}

// Save data to file
void saveToFile() {
    FILE *file = fopen("pilots.txt", "w");
    if (file == NULL) {
        printf("Error saving to file.\n");
        return;
    }

    for (int i = 0; i < pilotCount; i++) {
        fprintf(file, "%d,%s,%d,%s,%s\n",
                pilots[i].id,
                pilots[i].name,
                pilots[i].age,
                pilots[i].license,
                pilots[i].phone);
    }

    fclose(file);
    printf("Data saved successfully!\n");
}

// Load data from file
void loadFromFile() {
    FILE *file = fopen("pilots.txt", "r");
    if (file == NULL) {
        printf("No existing data found.\n");
        return;
    }

    while (fscanf(file, "%d,%49[^,],%d,%29[^,],%19[^\n]\n",
                  &pilots[pilotCount].id,
                  pilots[pilotCount].name,
                  &pilots[pilotCount].age,
                  pilots[pilotCount].license,
                  pilots[pilotCount].phone) == 5) {
        pilotCount++;
    }

    fclose(file);
    printf("%d pilot records loaded successfully!\n", pilotCount);
}

