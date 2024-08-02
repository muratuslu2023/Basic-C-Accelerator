#ifndef MURTY_H
#define MURTY_H


struct Vehicle
{
    char * car_name;
    int seat_number;
    int tire_number;
    float acceleration;
};



void say_hello();

void calculate(struct Vehicle * ptr_car, int time);

float distance_gone_with_acceleration(float acceleration, int time);

void save_stats(char * stat_lines[], int stat_lines_length);

#endif