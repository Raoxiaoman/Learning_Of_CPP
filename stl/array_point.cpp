#include <iostream>
#include <typeinfo>

using namespace std;

int main(){
    int a[2][2] = {{1,2},{3,4}};
    int (*p)[2] = a;
    decltype(p) * pp = &p;

    cout <<"数组指针的地址:" << pp << endl;
    cout <<"二维----列首地址:" <<  p << endl;
    cout <<"一维----行首地址:" <<  *p << endl;
    cout <<"首元素的值:"<< **p << endl;
    return 0;

}
