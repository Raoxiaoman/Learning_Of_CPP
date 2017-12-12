#ifndef TIME_H
#define TIME_H
class Watch;

class Time{
    friend class Watch;
    public:
    Time(int hour,int minute):hour(hour),minute(minute){}
    private:
    int hour;
    int minute;
};

#endif

