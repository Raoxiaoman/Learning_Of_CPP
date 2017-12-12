#include <iostream>
#include "myTime.h"
#include "myWatch.h"

void printfTime(Time &t){
    std::cout << t.hour << t.minute << std::endl;
}

int main(){
    Time t(19,9);
    Watch w;
    printfTime(t);
    w.printfTime(t);
    return 0;
}
