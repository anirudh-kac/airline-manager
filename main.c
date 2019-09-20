#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "display.h"

struct FLIGHT
{
    char airline[20];
    char number[10];
    int type;  // 0 for departure , 1 for arrival
    int status;  // 0 for on time, 1 for delayed
    int time;
};

typedef struct FLIGHT FLIGHT;
void printflight(FLIGHT f);

int main()
{
    printintro();
    printmenu();
    FLIGHT flight1={"INDIGO", "6E123" ,0,0,1200};
    printflight(flight1);
    return 0;
}


void printflight(FLIGHT f)
{
    char status[10];
    char type[10];
    if(f.type==0){
        strcpy(status,"DEPARTURE");
    }else{
        strcpy(status,"ARRIVAL");

    }

    if(f.status==0){
        strcpy(status,"ON TIME");
    }else{
        strcpy(status,"DELAYED");

    }


    printf("\t \t _________________________________________\n");
    printf("\t %s \t %s \t %s \t %s \t %d",f.airline,f.number,type,status,f.time);
}
