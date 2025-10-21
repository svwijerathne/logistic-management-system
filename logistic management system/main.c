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

#define MAX_CITIES 100

void cityManagement(char cities[MAX_CITIES][100],int *cityCount,int postalCode[MAX_CITIES]);
void addCity(char cities[MAX_CITIES][100],int *cityCount,int postalCode[MAX_CITIES]);
void renameCity(char cities[MAX_CITIES][100],int *cityCount,int postalCode[MAX_CITIES]);
void removeCity(char cities[MAX_CITIES][100],int *cityCount,int postalCode[MAX_CITIES]);
void distanceManagement(int distance[MAX_CITIES][MAX_CITIES],char cities[MAX_CITIES][100],int cityCount,int postalCodes[MAX_CITIES]);
void displayDistanceTable(int cityCount,char cities[MAX_CITIES][100],int distance[MAX_CITIES][MAX_CITIES]);
void inputDistance(int cityCount,char cities[MAX_CITIES][100],int distance[MAX_CITIES][MAX_CITIES],int postalCodes[MAX_CITIES]);
int findCityIndexByPostal(int code, int cityCount, int postalCodes[MAX_CITIES]);

int main(void) {
    char cities[MAX_CITIES][100];
    int distance[MAX_CITIES][MAX_CITIES];
    int cityCount=0;
    int postalCode[MAX_CITIES];
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
                distanceManagement(distance,cities,cityCount,postalCode);
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

void cityManagement(char cities[MAX_CITIES][100],int *cityCount,int postalCode[MAX_CITIES]) {
    int choice;
    do {
        printf("\n--- City Management ---\n");
        printf("1. Add City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Veiw cities\n");
        printf("5. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCity(cities, cityCount, postalCode);
                break;
            case 2:
                renameCity(cities, cityCount, postalCode);
                break;
            case 3:
                removeCity(cities, cityCount, postalCode);
                break;
            case 4:
                printf("\nCities List:\n");
                printf("Postal code \t\t city \n");
                for (int i = 0; i < *cityCount; i++){
                    printf("%-19d %-19s \n", postalCode[i],cities[i] );
                }
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);
}

void addCity(char cities[MAX_CITIES][100], int *cityCount, int postalCode[MAX_CITIES]) {
    if (*cityCount >= MAX_CITIES) {
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

void renameCity(char cities[MAX_CITIES][100], int *cityCount, int postalCode[MAX_CITIES]) {
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

void removeCity(char cities[MAX_CITIES][100], int *cityCount, int postalCode[MAX_CITIES]) {
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


int findCityIndexByPostal(int code, int cityCount, int postalCodes[MAX_CITIES]) {
    for (int i = 0; i < cityCount; i++) {
        if (postalCodes[i] == code)
            return i;
    }
    return -1;  // Not found
}

void distanceManagement(int distance[MAX_CITIES][MAX_CITIES],
                        char cities[MAX_CITIES][100],
                        int cityCount,
                        int postalCodes[MAX_CITIES]) {
    int choice;
    do {
        printf("\n--- Distance Management ---\n");
        printf("1. Enter Distance Between Cities\n");
        printf("2. View Distance Table\n");
        printf("3. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (cityCount < 2) {
                    printf("At least 2 cities required to add distances!\n");
                } else {
                    inputDistance(cityCount, cities, distance, postalCodes);
                }
                break;
            case 2:
                displayDistanceTable(cityCount, cities, distance);
                break;
            case 3:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 3);
}

void inputDistance(int cityCount, char cities[MAX_CITIES][100], int distance[MAX_CITIES][MAX_CITIES], int postalCodes[MAX_CITIES]) {
    int srcCode, destCode;
    printf("Enter source city postal code: ");
    scanf("%d", &srcCode);
    printf("Enter destination city postal code: ");
    scanf("%d", &destCode);

    // find the corresponding indices
    int srcIndex = findCityIndexByPostal(srcCode, cityCount, postalCodes);
    int destIndex = findCityIndexByPostal(destCode, cityCount, postalCodes);

    
    if (srcIndex == -1) {
        printf("source city postal codes not found!\n");
        return;
    }
    
    if ( destIndex == -1) {
        printf("destination city postal codes not found!\n");
        return;
    }
    
    if (srcIndex == destIndex) {
        printf("Source and destination cannot be the same city!\n");
        return;
    }

    int dist;
    printf("Enter distance (km): ");
    scanf("%d", &dist);

    distance[srcIndex][destIndex] = dist;
    distance[destIndex][srcIndex] = dist;
    printf("Distance successfully updated between %s and %s.\n", cities[srcIndex], cities[destIndex]);
}

void displayDistanceTable(int cityCount, char cities[MAX_CITIES][100], int distance[MAX_CITIES][MAX_CITIES]) {
    if (cityCount == 0) {
        printf("No cities available.\n");
        return;
    }

    printf("\n=========== Distance Table (km) ==================\n");
    printf("%-15s", "City");
    for (int i = 0; i < cityCount; i++)
        printf("%18s", cities[i]);
    printf("\n");

    for (int i = 0; i < cityCount; i++) {
        printf("%-18s", cities[i]);
        for (int j = 0; j < cityCount; j++) {
            printf("%18d", distance[i][j]);
        }
        printf("\n");
    }
    printf("====================================================\n");
}
