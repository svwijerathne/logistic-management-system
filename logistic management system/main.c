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
#define INF 999999
#define MAX_CITIES 100

void cityManagement(char cities[MAX_CITIES][100],int *cityCount,int postalCode[MAX_CITIES],int distance[MAX_CITIES][MAX_CITIES]);
void addCity(char cities[MAX_CITIES][100],int *cityCount,int postalCode[MAX_CITIES]);
void renameCity(char cities[MAX_CITIES][100],int *cityCount,int postalCode[MAX_CITIES]);
void removeCity(char cities[MAX_CITIES][100], int *cityCount, int postalCode[MAX_CITIES], int distance[MAX_CITIES][MAX_CITIES]);
void distanceManagement(int distance[MAX_CITIES][MAX_CITIES],char cities[MAX_CITIES][100],int cityCount,int postalCodes[MAX_CITIES]);
void displayDistanceTable(int cityCount,char cities[MAX_CITIES][100],int distance[MAX_CITIES][MAX_CITIES]);
void inputDistance(int cityCount,char cities[MAX_CITIES][100],int distance[MAX_CITIES][MAX_CITIES],int postalCodes[MAX_CITIES]);
int findCityIndexByPostal(int code, int cityCount, int postalCodes[MAX_CITIES]);

void deliveryRequestHandling(char cities[MAX_CITIES][100], int cityCount, int postalCodes[MAX_CITIES],int distance[MAX_CITIES][MAX_CITIES]);
void calculateCost(float distance, float weight, int vehicleType);
void dfsLeastDistance(int current, int dest, int visited[MAX_CITIES],int cityCount, int distance[MAX_CITIES][MAX_CITIES],int path[], int pathIndex, int *minDist, int bestPath[]);
int findLeastDistance(int cityCount, int distance[MAX_CITIES][MAX_CITIES], char cities[MAX_CITIES][100],int srcIndex, int destIndex);




int main(void) {
    char cities[MAX_CITIES][100];
    int distance[MAX_CITIES][MAX_CITIES];
    //to avoid garbage values in distance matrix
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            if (i == j)
                distance[i][j] = 0;       // same city
            else
                distance[i][j] = INF;     // not connected yet
        }
    }
    
    int cityCount=0;
    int postalCode[MAX_CITIES];
    int choice=0;
    
    do{
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. Delivery Request Handling\n");
        printf("4. Delivery Records\n");
        printf("5. Performance Reports\n");
        printf("6.Exit..\n");
        printf("Enter your choice :");
        scanf("%d", &choice);
        
        switch (choice){
            case 1:
                //city management
                cityManagement(cities,&cityCount,postalCode,distance);
                break;
            case 2:
                //distance management
                distanceManagement(distance,cities,cityCount,postalCode);
                break;
            case 3:
                //delivery request handling
                deliveryRequestHandling(cities,cityCount,postalCode,distance);
                break;
            case 4:
                //Delivery records
                break;
            case 5:
                //performing reports
                break;
            case 6:
                printf("Exiting the program ....\n");
                return 0;
            default:
                printf("Invalid choice.. ! \nTry again !\n");
                
        }
    }while(choice !=6);
    
    return 0;
}

void cityManagement(char cities[MAX_CITIES][100],int *cityCount,int postalCode[MAX_CITIES],int distance[MAX_CITIES][MAX_CITIES]) {
    int choice;
    do {
        printf("\n--- City Management ---\n");
        printf("1. Add City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. View cities\n");
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
                removeCity(cities, cityCount, postalCode,distance);
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


void removeCity(char cities[MAX_CITIES][100], int *cityCount, int postalCode[MAX_CITIES], int distance[MAX_CITIES][MAX_CITIES]) {
    int code, found = 0;
    printf("Enter postal code to remove: ");
    scanf("%d", &code);

    for (int i = 0; i < *cityCount; i++) {
        if (postalCode[i] == code) {
            // Shift cities and postal codes left
            for (int j = i; j < *cityCount - 1; j++) {
                strcpy(cities[j], cities[j + 1]);
                postalCode[j] = postalCode[j + 1];
            }

            // Shift distance matrix rows up (from row i)
            for (int r = i; r < *cityCount - 1; r++) {
                for (int c = 0; c < *cityCount; c++) {
                    distance[r][c] = distance[r + 1][c];
                }
            }
            // Shift distance matrix columns left (from col i)
            for (int r = 0; r < *cityCount - 1; r++) {
                for (int c = i; c < *cityCount - 1; c++) {
                    distance[r][c] = distance[r][c + 1];
                }
            }

            // Clear last row/col
            int last = *cityCount - 1;
            for (int k = 0; k < *cityCount; k++) {
                distance[last][k] = INF;
                distance[k][last] = INF;
            }
            distance[last][last] = 0;

            (*cityCount)--;
            printf("City removed successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
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
    //to avoid re-enters a distance for the same two cities
    if (distance[srcIndex][destIndex] != INF && distance[srcIndex][destIndex] != 0) {
        printf("Warning: Existing distance between %s and %s is %d km. Overwrite? (1=Yes, 0=No): ",
               cities[srcIndex], cities[destIndex], distance[srcIndex][destIndex]);
        int overwrite;
        printf("Overwrite? (1=Yes, 0=No): ");
        scanf("%d", &overwrite);
        if (overwrite==0) {
            return;
        }
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
    printf("%-18s", "City");
    for (int i = 0; i < cityCount; i++)
        printf("%18s", cities[i]);
    printf("\n");

    for (int i = 0; i < cityCount; i++) {
        printf("%-18s", cities[i]);
        for (int j = 0; j < cityCount; j++) {
            if (distance[i][j] == INF) {
                printf("%18s", "-");
            }else {
                printf("%18d", distance[i][j]);
            }
        }
        printf("\n");
    }
    printf("====================================================\n");
}

void deliveryRequestHandling(char cities[MAX_CITIES][100], int cityCount, int postalCodes[MAX_CITIES],int distance[MAX_CITIES][MAX_CITIES]) {
    if (cityCount < 2) {
        printf("Add at least 2 cities first!\n");
        return;
    }

    int srcCode, destCode;
    float weight;
    int vehicleType;

    printf("Enter source city postal code: ");
    scanf("%d", &srcCode);
    printf("Enter destination city postal code: ");
    scanf("%d", &destCode);

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
        printf("Source and destination cannot be the same!\n");
        return;
    }

    if (distance[srcIndex][destIndex] == INF) {
        printf("Distance between %s and %s not set yet!\n", cities[srcIndex], cities[destIndex]);
        return;
    }
    int minumumDistance=findLeastDistance(cityCount,distance,cities,srcIndex,destIndex);
    
    printf("Enter package weight (kg): ");
    scanf("%f", &weight);
    printf("Select vehicle type (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vehicleType);
    
    
    printf("\n\n====================== Request Report =====================\n");
    printf("source city           : %s\n",cities[srcIndex]);
    printf("Destination city      : %s\n",cities[destIndex]);
    printf("Direct distance In between   : %d\n",distance[srcIndex][destIndex]);
    printf("Shorest path distance        :%d\n",minumumDistance);
    printf("Weight of the package : %f Kg\n",weight);
    if(vehicleType==1){
        printf("Vehicle type          : Van\n");
    }
    else if(vehicleType==2){
        printf("Vehicle type          : Truck\n");
    }
    else {
        printf("Vehicle type          : Lorry\n");
    }
    
    printf("\n");
    
    calculateCost((float)minumumDistance, weight, vehicleType);
}

void dfsLeastDistance(int current, int dest, int visited[MAX_CITIES],
                      int cityCount, int distance[MAX_CITIES][MAX_CITIES],
                      int path[], int pathIndex, int *minDist, int bestPath[]) {
    visited[current] = 1;
    path[pathIndex] = current;

    // If destination is reached, compute total distance
    if (current == dest) {
        int total = 0;
        for (int i = 0; i < pathIndex; i++) {
            total += distance[path[i]][path[i + 1]];
        }
        if (total < *minDist) {
            *minDist = total;
            for (int i = 0; i <= pathIndex; i++) {
                bestPath[i] = path[i];
            }
            bestPath[pathIndex + 1] = -1; // Mark end of path
        }
    } else {
        // Explore all connected cities
        for (int i = 0; i < cityCount; i++) {
            if (!visited[i] && distance[current][i] != INF && distance[current][i] != 0) {
                dfsLeastDistance(i, dest, visited, cityCount, distance,
                                 path, pathIndex + 1, minDist, bestPath);
            }
        }
    }

    visited[current] = 0; // Unmark when backtracking
}


int findLeastDistance(int cityCount, int distance[MAX_CITIES][MAX_CITIES], char cities[MAX_CITIES][100],int srcIndex, int destIndex) {
    int visited[MAX_CITIES] = {0}, path[MAX_CITIES];
    int bestPath[MAX_CITIES];
    for (int i = 0; i < MAX_CITIES; i++) bestPath[i] = -1;

    int minDist = INF;

    dfsLeastDistance(srcIndex, destIndex, visited, cityCount, distance, path, 0, &minDist, bestPath);

    if (minDist == INF) {
        printf("No route found.\n");
        // if no route found, return direct distance if it exists, else INF
        if (distance[srcIndex][destIndex] != INF) return distance[srcIndex][destIndex];
        return minDist;
    }

    printf("\nShortest route: ");
    for (int i = 0; bestPath[i] != -1 && i < MAX_CITIES; i++) {
        printf("%s", cities[bestPath[i]]);
        if (bestPath[i + 1] != -1) printf(" -> ");
    }
    printf("\n");
    return minDist;
}





void calculateCost(float distance, float weight, int vehicleType) {
    float ratePerKm, speed, efficiency, capacity;

    switch (vehicleType) {
        case 1: ratePerKm = 30; speed = 60; efficiency = 12; capacity = 1000; break;
        case 2: ratePerKm = 40; speed = 50; efficiency = 6; capacity = 5000; break;
        case 3: ratePerKm = 80; speed = 45; efficiency = 4; capacity = 10000; break;
        default:
            printf("Invalid vehicle type!\n");
            return;
    }

    if (weight > capacity) {
        printf("Weight exceeds vehicle capacity! Try a larger vehicle.\n");
        return;
    }

    float deliveryCost = distance * ratePerKm * (1 + (weight / 10000));
    
    float fuelUsed = distance / efficiency;
    
    float fuelCost = fuelUsed * 310;
    
    float totalCost = deliveryCost + fuelCost;
    
    float profit = deliveryCost * 0.25;
    
    float customerCharge = totalCost + profit;
    
    float time = distance / speed;

    printf("\n================ DELIVERY ESTIMATION ================\n");
    printf("Distance: %.2f km\n", distance);
    if(vehicleType==1){
        printf("Vehicle type : Van\n");
    }
    else if(vehicleType==2){
        printf("Vehicle type : Truck\n");
    }
    else {
        printf("Vehicle type : Lorry\n");
    }
    printf("Weight: %.2f kg\n", weight);
    printf("-----------------------------------------------------\n");
    printf("Delivery Cost: %.2f LKR\n", deliveryCost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Total Operational Cost: %.2f LKR\n", totalCost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customerCharge);
    printf("Estimated Time: %.2f hrs\n", time);
    printf("=====================================================\n");
}
