#include <iostream>
#include "myTime.h"
#include "myWatch.h"


int main(){
    Time t(19,9);
    Watch w(t);
    w.printfTime();
    return 0;
}
