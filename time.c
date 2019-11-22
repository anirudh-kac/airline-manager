#include <stdio.h>

int time_to_min(int time)
{
    int minutes = (time/100)*60 +(time%100);
    return minutes;
}

int min_to_hh(int min)
{
    int hh = min/60;
    return hh;
    int mm = min%60;

}

int min_to_mm(int min)
{

    int mm = min%60;
    return mm;
}

int main()
{
    timetomin(1200);
    mintotime(720);

    return 0;
}