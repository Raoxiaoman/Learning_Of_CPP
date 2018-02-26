#include <iostream>

int main(){

    int a = 5;
    const int *p1 = &a;
    int * const p2 = &a;
    int *p4 = p2;
    *p4 = 4;
    double d = 1/3;
    std::cout << d << std::endl;
    return 0;
}
