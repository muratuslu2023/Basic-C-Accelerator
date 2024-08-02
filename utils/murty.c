#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>


#define MAX_STAT_LINE_LENGTH 256


struct Vehicle
{
    char * car_name;
    int seat_number;
    int tire_number;
    float acceleration;
};


void say_hello(){
    printf("Hello!\n");
}


float distance_gone_with_acceleration(float acceleration, int time){
    return .5 * (acceleration) * (float)pow(time,2);
}
void save_stats(char * stat_lines[], int stat_lines_length, struct Vehicle * ptr_car){
    
    FILE * fp;

    int car_name_length = strlen(ptr_car->car_name);
    int file_title_length = 10 + car_name_length;
    char file_title[file_title_length];

/*     char cwd[PATH_MAX];
    getcwd(cwd,sizeof(cwd)); */

    sprintf(file_title,"./stats_%s.txt",ptr_car->car_name);

    fp = fopen(file_title,"w");

    
    time_t now;
    struct tm * local;
    time(&now);
    local = localtime(&now);

    char local_hour[3];
    snprintf(local_hour,sizeof(local_hour),"%02d",local->tm_hour);

    char local_minute[3];
    snprintf(local_minute,sizeof(local_minute),"%02d",local->tm_min);

    char local_day[3];
    snprintf(local_day,sizeof(local_day),"%02d",local->tm_mday);

    // Format the month (adding 1 because tm_mon is 0-based)
    char local_month[3];
    snprintf(local_month, sizeof(local_month), "%02d", local->tm_mon + 1);

    // Format the year (adding 1900 because tm_year is years since 1900)
    char local_year[5];
    snprintf(local_year, sizeof(local_year), "%d", local->tm_year + 1900);
    
    int content_title_length = sizeof(local_day) + sizeof(local_hour) + sizeof(local_minute) + sizeof(local_month) + sizeof(local_year) + car_name_length + 9;
    char content_title[content_title_length];

    sprintf(content_title,"%s - %s/%s/%s | %s:%s",ptr_car->car_name,local_day,local_month,local_year,local_hour,local_minute);



    int stat_lines_str_length = 0;
    for(int i = 0; i < stat_lines_length; i++){
        stat_lines_str_length = stat_lines_str_length + strlen(stat_lines[i]);
        stat_lines_str_length ++;
    }
    
    char * stat_lines_str = (char*) malloc(stat_lines_str_length * sizeof(char));

    for(int i = 0; i < stat_lines_length; i++){
        strcat(stat_lines_str,stat_lines[i]);
        if(i < stat_lines_length - 1){
            strcat(stat_lines_str,"");
        }
    }


    int content_length = content_title_length + 1 + stat_lines_str_length;
    char * content = (char*) malloc(content_length * sizeof(char));

    sprintf(content,"%s\n%s",content_title,stat_lines_str);

    fprintf(fp,"%s",content);

    fclose(fp);

}
void calculate(struct Vehicle * ptr_car, int time){


    float total_distance = distance_gone_with_acceleration(ptr_car->acceleration,time);
    float acceleration = ptr_car->acceleration;
    float distance_left = total_distance;

    float coefficient = ptr_car->acceleration / 2;
    int time_ = 0;
    float distance_gone = 0;

    int stat_lines_length = time;
    
    char * stat_lines[stat_lines_length];

    for(int i = 0; i < stat_lines_length; i ++){
        stat_lines[i] = (char*)malloc(MAX_STAT_LINE_LENGTH * sizeof(char));
    }

    while(time_ < time){
        time_++;
        float second_based_distance = (2*time_ - 1) * acceleration * .5;
        distance_gone = pow(time_,2) * coefficient;
        distance_left = distance_left - second_based_distance;
        printf("Time: %d Distance Gone: %.2f Distance Left: %.2f Second Based Distance: %.2f\n",time_,distance_gone,distance_left,second_based_distance);
        sprintf(stat_lines[time_ - 1],"Time: %d Distance Gone: %.2f Distance Left: %.2f Second Based Distance: %.2f\n",time_,distance_gone,distance_left,second_based_distance);
    }

    char response_buffer[100];
    while (1){
        printf("Do you want to save these results? [y/N]: ");
        scanf("%s",response_buffer);

        response_buffer[strcspn(response_buffer, "\n")] = 0;

        if(strcmp(response_buffer,"y") == 0 || strcmp(response_buffer,"Y") == 0){
            save_stats(stat_lines, stat_lines_length, ptr_car);
            printf("SAVED!!!\n");
            break;
        }else if(strcmp(response_buffer,"n") == 0 || strcmp(response_buffer,"N") == 0){
            printf("GOOD BYE!\n");

            break;
        }else{
            printf("Enter a valid response!\n");
            while(getchar() != '\n');
        }
    
    }
    
}

