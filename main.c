#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 50
#define MAX_TIME 10

//structres
struct flight {
    char airline[10];
    char number[10];
    int expected_time;
    int scheduled_time;
    char city[10];
};

typedef struct flight FLIGHT;


//global variables

//queues
FLIGHT arrivals[MAX_SIZE];
FLIGHT departures[MAX_SIZE];
FLIGHT schedule[2*MAX_SIZE];

//variables corresponding to above queues
int n1,n2,n3;
int front1=0,front2=0;
int rear1=-1,rear2=-1;
int c1=0,c2=0,c3=0;


//function prototypes

void display_menu();
void enter_arrivals();
void enter_departures();

int main()
{
    int ch,ch1;
    while(1)
    {
        display_menu();
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("\n Enter your choice : \n 1.Arrivals\n 2.Departures\n");
                scanf("%d",&ch1);
                if(ch1==1)
                {
                    enter_arrivals();
                }
                else if(ch1==2)
                {
                    enter_departures();
                }
                else
                {
                    printf("Invalid Choice\n");
                }
                
                break;
            case 2:
                printf("Emergeny arrival\n");
                break;
            case 3:
                printf("Emergency departure\n");
                break;
            case 4:
                printf("Display schedule\n");
                break;
            case 5:
                exit(0);
            default: printf("Invalid choice\n");
            
        }
    }
    return 0;

}


void display_menu()
{
    printf("\n _______________FLIGHT MANAGEMENT SYSTEM__________________\n\n");
    printf("\n Enter your choice \n");
    printf("\n 1. Enter flights data \n 2. Add emergency arrival \n 3. Add emergency departure \n 4. Display Schedule \n 5. Exit\n");
}

void enter_arrivals()
{
    int i;
    printf("Enter number of flights : \n");
    scanf("%d",&n1);
    if(c1+n1>MAX_SIZE)
    {
        printf("Flight limit exceeded\n");
        return;
    }

    for(int i=0;i<n1;i++)
    {
        rear1++;
        printf("\nAirline \t Number \t Arrival Time \t Origin \n");
        scanf("%s",arrivals[rear1].airline);
        scanf("%s",arrivals[rear1].number);
        scanf("%d",&arrivals[rear1].scheduled_time);
        scanf("%s",arrivals[rear1].city);


        arrivals[rear1].scheduled_time = arrivals[rear1].expected_time;

        printf("\n____________________________________________________\n");
    }
    c1+=n1;
    printf("Arrival Data Saved\n");
}


void enter_departures()
{
    int i;
    printf("Enter number of flights : \n");
    scanf("%d",&n2);
    if(c2+n2>MAX_SIZE)
    {
        printf("Flight limit exceeded\n");
        return;
    }

    for(int i=0;i<n2;i++)
    {
        rear2++;
        printf("\nAirline \t Number \t Departure Time \t Destination \n");
        scanf("%s",departures[rear2].airline);
        scanf("%s",departures[rear2].number);
        scanf("%d",&departures[rear2].scheduled_time);
        scanf("%s",departures[rear2].city);


        departures[rear2].scheduled_time = departures[rear2].expected_time;

        printf("\n____________________________________________________\n");
    }
    c2+=n2;
    printf("Arrival Data Saved\n");
}