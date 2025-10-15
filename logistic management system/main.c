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



int main(void) {
    
    int choice=0;
    
    do{
        printf("1. City Management");
        printf("2. Distance Management");
        printf("3. Vehicle Management");
        printf("4. Delivery Request Handling");
        printf("5. Cost, Time, and Fuel Calculations");
        printf("6. Delivery Records");
        printf("7. Finding The Least-Cost Route"); //(Least-Distance)
        printf("8. Performance Reports");
        printf("9. File Handling");
        printf("10.Exit..");
        printf("Enter your choice :");
        scanf("%d", &choice);
        
        switch (choice){
            case 1:
                //city management
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
