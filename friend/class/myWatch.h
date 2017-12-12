#ifndef MYWATHCH_
#define MYWATHCH_
#include "myTime.h"

class Watch{
    public:
        Watch(Time &t):t(t){};
        void printfTime();
    private:
        Time t;
};

#endif

