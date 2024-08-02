#include <stdio.h>
#include "utils/murty.h"
#include <string.h>
#include <stdlib.h>


#define MAX_NAME_LENGTH 100


int main(){
    
    #if defined(_WIN32)
        system("cls");
    #elif defined(_WIN64)
        system("cls");
    #elif defined(__APPLE__)
        system("clear");
    #endif

    
    say_hello();

    printf("Welcome to the Vehicle Accelerator!!!\n");

    char  vehicle_name[MAX_NAME_LENGTH];
    int tire_number;
    int seat_number;
    float acceleration;
    int time;

    printf("Enter a vehicle name: ");
    scanf("%s",vehicle_name);

    while (1){
        printf("Enter tire number: ");
        
        if(scanf("%d",&tire_number) == 1){
            break;
        }else{
            printf("Enter a valid tire number!\n");
            while (getchar() != '\n'); //clearing the input buffer
        }
    }
    
    while(1){
        printf("Enter seat number: ");
        if(scanf("%d",&seat_number) == 1){
            break;
        }else{
            printf("Enter a valid seat number!\n");
            while(getchar() != '\n');
        }
    }

    while(1){
        printf("Enter acceleration: ");

        if(scanf("%f",&acceleration) == 1){
            break;
        }else{
            printf("Enter a valid acceleration!\n");
            while(getchar() != '\n');
        }
    }

    while(1){
        printf("Enter total driving time (seconds): ");
        if(scanf("%d",&time) == 1){
            break;
        }
        else{
            printf("Enter a valid time!\n");
            while(getchar() != '\n');
        }
    }


    struct Vehicle my_car;

    my_car.car_name = vehicle_name;
    my_car.tire_number = tire_number;
    my_car.seat_number = seat_number;
    my_car.acceleration = acceleration;

    struct Vehicle * ptr_my_car = &my_car;

    calculate(ptr_my_car,time);


    return 0;
}