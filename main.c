#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE 100
#define MAX_TIME 30
//structures


struct flight {
    char airline[10];
    char number[10];
    int expected_time;  // stoted in form of minutes passed from 0000
    int scheduled_time;
    char city[10];
    char type; // Arriving or departing 'A' / 'D'
};

typedef struct flight FLIGHT;


//global variables

//queues
FLIGHT arrivals[MAX_SIZE];
FLIGHT departures[MAX_SIZE];
FLIGHT schedule[2*MAX_SIZE];

//variables corresponding to above queues
// 1 for arrivals, 2 for departures , 3 for all
int n1,n2,n3;

//initialisation of front , rear and count variables
int front1=0,front2=0;
int rear1=-1,rear2=-1;
int c1=0,c2=0,c3=0;


//function prototypes

void display_menu();  
void enter_arrivals();
void enter_departures();
void emergency_arrival();
void emergency_departure();
void schedule_flights();
void display_list(int ch); // 1 for arrivals, 2 for departures , 3 for full schedule


int time_to_min(int time);
int min_to_hh(int min);
int min_to_mm(int min);


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
                    continue;
                }
                
                break;
            case 2:
                emergency_arrival();
                break;
            case 3:
                emergency_departure();
                break;
            case 4:
                schedule_flights();
                display_list(3);
                break;
            case 5:
                display_list(1);
                break;
            case 6:
                display_list(2);
                break;
            case 7:
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
    printf("\n 1. Enter flights data \n 2. Add emergency arrival \n 3. Add emergency departure \n 4. Display Schedule \n 5. Display Arrivals \n 6. Display Departures \n 7. Exit\n");
}

void enter_arrivals()
{
    int i,temp_time; // temp_time temporarily stores time before conversion
    printf("Enter number of flights : \n");
    scanf("%d",&n1);

    if(c1+n1>MAX_SIZE)
    {
        printf("Flight limit exceeded\n");
        return;
    }

    for(int i=0;i<n1;i++)
    {

        //inserting at rear end of the queue
        rear1++;
        printf("\nAirline \t Number \t Arrival Time \t Origin \n");
        scanf("%s",arrivals[rear1].airline);
        scanf("%s",arrivals[rear1].number);
        scanf("%d",&temp_time);
        scanf("%s",arrivals[rear1].city);

        arrivals[rear1].expected_time = time_to_min(temp_time);
        arrivals[rear1].scheduled_time = arrivals[rear1].expected_time;
        arrivals[rear1].type = 'A';


        printf("\n____________________________________________________\n");
    }

    c1+=n1;
    printf("Arrival Data Saved\n");
}


void enter_departures()
{
    int i,temp_time;
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
        scanf("%d",&temp_time);
        scanf("%s",departures[rear2].city);

        departures[rear2].expected_time = time_to_min(temp_time);
        departures[rear2].scheduled_time = departures[rear2].expected_time;
        departures[rear2].type = 'D';
      

        printf("\n____________________________________________________\n");
    }
    c2+=n2;
    printf("Arrival Data Saved\n");
}


void emergency_arrival()
{
    FLIGHT arrival;
    // arrivial contains the data of emergency arrival
    // this is to be added to arrivals queue using insertion sort technique by comparing the time

    int j,time,temp_time;
    printf("\nEnter emergency flight data : \n");
    printf("\n Airline \t Number \t Arrival Time \t Source \n ");
    scanf("%s %s %d %s",arrival.airline, arrival.number,&temp_time,arrival.city);

    arrival.expected_time = time_to_min(temp_time);
    arrival.scheduled_time = arrival.expected_time;
    arrival.type= 'A';

    j=rear1;
    time = arrival.expected_time;

    while(j>=0 && time<arrivals[j].scheduled_time)
    {
        arrivals[j+1] =  arrivals[j];
        j--;
    }

    arrivals[j+1] = arrival;
    rear1++;
    c1++; 

    printf("Emergency arrival added\n");
}

void emergency_departure()
{
    FLIGHT departure;
    // add departure to departures queue using insertion sort

    int j,time,temp_time;
    printf("\nEnter emergency flight data : \n");
    printf("\n Airline \t Number \t Departure Time \t Destination \n ");
    scanf("%s %s %d %s",departure.airline, departure.number,&temp_time,departure.city);

    departure.expected_time = time_to_min(temp_time);
    departure.scheduled_time = departure.expected_time;
    departure.type = 'D';
    j=rear2;
    time = departure.expected_time;
    while(j>=0 && time<departures[j].scheduled_time)
    {
        departures[j+1] =  departures[j];
        j--;
    }
    departures[j+1] = departure;
    rear2++;
    c2++; 
    printf("Emergency departure added\n");
}


void display_list(int ch)
{
    int front,rear,i;
    // front and rear are used to iterate wothout changing actual front and rear
    // 1 for arrivals ,2 for departures , 3 for all 
    if(ch==1)
    {

        front=front1;
        rear=rear1;
        if(front>rear)
        {
            printf("\nNo flight in list\n");
            return;
        }
        printf("\n AIRLINE \t NUMBER \t ARRIVAL TIME \t ORIGIN \n ");
        for(i=front;i<=rear;i++)
        {
            printf("\n    %s   \t   %s   \t     %d:%d    \t   %s\n",arrivals[i].airline,arrivals[i].number, min_to_hh(arrivals[i].scheduled_time),  min_to_mm(arrivals[i].scheduled_time), arrivals[i].city);

        }
    }
    else if (ch==2)
    {
        front=front2;
        rear=rear2;
        if(front>rear)
        {
            printf("\nNo flight in list\n");
            return;
        }
        printf("\n AIRLINE \t NUMBER \t DEPARTURE TIME \t DESTINATION \n ");
        for(i=front;i<=rear;i++)
        {
            printf("\n    %s   \t   %s   \t     %d:%d    \t   %s\n",departures[i].airline,departures[i].number,min_to_hh(departures[i].scheduled_time),min_to_mm(departures[i].scheduled_time) , departures[i].city);

        }
    }
    else 
    {
        if(c3==0)
        {
            printf("No flights in Schedule\n");
            return;
        }
        printf("\nS.NO \t AIRLINE \t NUMBER \t \t A/D  \t   TIME   \t CITY \n ");
        for(i=0;i<c3;i++)
        {

            printf("\n%d   \t   %s   \t   %s   \t    %c    \t   %d:%d   \t  %s\n",i+1, schedule[i].airline, schedule[i].number, schedule[i].type, min_to_hh(schedule[i].scheduled_time),min_to_mm(schedule[i].scheduled_time), schedule[i].city);
        }

    }
}


void schedule_flights()
{
    c3=0;
    int i = 0 ;
    // variables to iterate over the queues
    int f1 = front1, r1 = rear1 , f2 = front2 , r2 = rear2;
    //last flight operation set to negative initially
    int last_flight = -MAX_TIME;

    // both arrivals and departures are present
    while(f1<=r1 && f2<=r2)
    {
        // if arrival has to proceed
        if(arrivals[f1].scheduled_time<=departures[f2].scheduled_time)
        {
            // if arrival needs extra time
            if(arrivals[f1].scheduled_time-last_flight < MAX_TIME)
            {
                arrivals[f1].scheduled_time += MAX_TIME;
                departures[f2].scheduled_time+=MAX_TIME;
            }
            else
            {
                schedule[c3++]=arrivals[f1];
                last_flight=arrivals[f1].scheduled_time;
                f1++;
            }
            
        }
        else
        {

            //if departure will affect next arrival, departing flight is delayed
            if(arrivals[f1].scheduled_time - departures[f2].scheduled_time < MAX_TIME)
            {
                departures[f2].scheduled_time+=MAX_TIME;
            }
            else
            {
                schedule[c3++]=departures[f2];
                last_flight=departures[f2].scheduled_time;
                f2++;
            }
            
        }
        

    }

    // arrivals still left
    while(f1<=r1)
    {
        // if time between consecutive flights is less
        if(arrivals[f1].scheduled_time-last_flight<MAX_TIME)
        {
            arrivals[f1].scheduled_time+=MAX_TIME;
        }
        else
        {
            schedule[c3++]=arrivals[f1];
            last_flight=arrivals[f1].scheduled_time;
            f1++;
        }
        
    }

    //departures are left

    while(f2<=r2)
    {
        if(departures[f2].scheduled_time-last_flight<MAX_TIME)
        {
            departures[f2].scheduled_time+=MAX_TIME;
        }
        else
        {
            schedule[c3++]=departures[f2];
            last_flight=departures[f2].scheduled_time;
            f2++;
        }
        
    }

}


//time functionality functions

int time_to_min(int time) // convert 24 hour time format to minutes elapsed form 0000;
{
    int minutes = (time/100)*60 +(time%100);
    return minutes;
}

int min_to_hh(int min)  // convert minutes elapsed into  number of hours
{
    int hh = min/60;
    return hh;
}

int min_to_mm(int min)  // convert minutes into minutes in hh:mm format
{

    int mm = min%60;
    return mm;
}