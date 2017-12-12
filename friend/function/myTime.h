#ifndef TIME_H
#define TIME_H
#include "myWatch.h"

class Time{
    friend void printfTime(Time &t);
    friend void Watch::printfTime(Time &t);
    public:
    Time(int hour,int minute):hour(hour),minute(minute){}
    private:
    int hour;
    int minute;
};

#endif

