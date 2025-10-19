//
//  main.c
//  logistic management system
//
//  Created by Vimansa Wijerathna  on 2025-10-15.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 100
void cityManagement(char cities[MAX][100],int *cityCount,int postalCode[MAX]);
void addCity(char cities[MAX][100],int *cityCount,int postalCode[MAX]);
void renameCity(char cities[MAX][100],int *cityCount,int postalCode[MAX]);
void removeCity(char cities[MAX][100],int *cityCount,int postalCode[MAX]);

int main(void) {
    char cities[MAX][100];
    int cityCount=0;
    int postalCode[MAX];
    int choice=0;
    
    do{
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. Vehicle Management\n");
        printf("4. Delivery Request Handling\n");
        printf("5. Cost, Time, and Fuel Calculations\n");
        printf("6. Delivery Records\n");
        printf("7. Finding The Least-Cost Route\n"); //(Least-Distance)
        printf("8. Performance Reports\n");
        printf("9. File Handling\n");
        printf("10.Exit..\n");
        printf("Enter your choice :");
        scanf("%d", &choice);
        
        switch (choice){
            case 1:
                //city management
                cityManagement(cities,&cityCount,postalCode);
                break;
            case 2:
                //distance management
                break;
            case 3:
                //vehicle management
                break;
            case 4:
                //delivery request handling
                break;
            case 5:
                //Cost, Time, and Fuel Calculations
                break;
            case 6:
                //Delivery records
                break;
            case 7:
                //finding the Least-Cost route
                break;
            case 8:
                //performing reports
                break;
            case 9:
                //file handling
                break;
            case 10:
                printf("Exiting the program ....\n");
                return 0;
            default:
                printf("Invalid choice.. ! \nTry again !\n");
                
        }
    }while(choice !=10);
    
    return 0;
}

void cityManagement(char cities[MAX][100], int *cityCount, int postalCode[MAX]) {//insert a veiw funtion
    int choice;
    do {
        printf("\n--- City Management ---\n");
        printf("1. Add City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCity(cities, cityCount, postalCode); break;
            case 2: renameCity(cities, cityCount, postalCode); break;
            case 3: removeCity(cities, cityCount, postalCode); break;
            case 4:
                printf("\nCities List:\n");
                for (int i = 0; i < *cityCount; i++)
                    printf("%d. %s (Postal Code: %d)\n", i + 1, cities[i], postalCode[i]);
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);
}

void addCity(char cities[MAX][100], int *cityCount, int postalCode[MAX]) {
    if (*cityCount >= MAX) {
        printf("City limit reached!\n");
        return;
    }

    printf("Enter city name: ");
    scanf(" %[^\n]", cities[*cityCount]);

    // Check duplicate name
    for (int i = 0; i < *cityCount; i++) {
        if (strcmp(cities[i], cities[*cityCount]) == 0) {
            printf("City already exists!\n");
            return;
        }
    }

    printf("Enter postal code: ");
    scanf("%d", &postalCode[*cityCount]);

    // Check duplicate postal code
    for (int i = 0; i < *cityCount; i++) {
        if (postalCode[i] == postalCode[*cityCount]) {
            printf("Postal code already exists!\n");
            return;
        }
    }

    (*cityCount)++;
    printf("City added successfully.\n");
}

void renameCity(char cities[MAX][100], int *cityCount, int postalCode[MAX]) {
    int code, found = 0;
    printf("Enter postal code to rename: ");
    scanf("%d", &code);

    for (int i = 0; i < *cityCount; i++) {
        if (postalCode[i] == code) {
            printf("Enter new city name: ");
            scanf(" %[^\n]", cities[i]);
            printf("City renamed successfully.\n");
            found = 1;
            break;
        }
    }

    if (found==0){
        printf("Postal code not found!\n");
    }
}

void removeCity(char cities[MAX][100], int *cityCount, int postalCode[MAX]) {
    int code, found = 0;
    printf("Enter postal code to remove: ");
    scanf("%d", &code);

    for (int i = 0; i < *cityCount; i++) {
        if (postalCode[i] == code) {
            // Shift arrays left
            for (int j = i; j < *cityCount - 1; j++) {
                strcpy(cities[j], cities[j + 1]);
                postalCode[j] = postalCode[j + 1];
            }
            (*cityCount)--;
            printf("City removed successfully.\n");
            found = 1;
            break;
        }
    }

    if (found==0){
        printf("Postal code not found!\n");
    }
}

