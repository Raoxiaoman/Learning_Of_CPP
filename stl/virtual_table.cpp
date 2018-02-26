#include <iostream>

using namespace std;
class base{
public:
    virtual void f(){
        cout << "base::f()" << endl;
    }
    virtual void g(){
        cout << "base::g()" << endl;
    }
    virtual void h(){
        cout << "base::h()" << endl;
    }
    
    
};

class derive1 :public base{

};

class derive2 :public base{
    virtual void f(){
        cout << "derive2::f()" << endl;
    }
    virtual void g(){
        cout << "derive2::g()" << endl;
    }
    virtual void h(){
        cout << "derive2::h()" << endl;
    }

};



typedef void(*Fun)(void);
int main(){
    cout << sizeof(int) << endl;
    base b;
    Fun pfun = NULL;

    cout << "基类" << endl;
    cout << "虚函数表指针的地址:" << (int*)(&b) << endl;
    cout << "虚函数表的地址--第一个虚函数的地址:" << (int*)(*(int*)(&b)) << endl;
    pfun = (Fun)*((int*)*(int*)(&b));
    pfun();

    derive1 d;
    derive1 dd;
    cout << "子类1" << endl;
    cout << "虚函数表指针的地址:" << (int*)(&d) << endl;
    cout << "虚函数表的地址--第一个虚函数的地址:" << (int*)(*(int*)(&d)) << endl;
    cout << "虚函数表指针的地址:" << (int*)(&dd) << endl;
    cout << "虚函数表的地址--第一个虚函数的地址:" << (int*)(*(int*)(&dd)) << endl;
    long * ifun = (long*)*(int*)(&d);
    //pfun = (Fun)ifun[0];
    pfun = (Fun)*(ifun+0);
    pfun();
    pfun = (Fun)*(ifun+1);
    pfun();
    pfun = (Fun)ifun[2];
    pfun();
    
    derive2 d2;
    cout << "子类2" << endl;
    cout << "虚函数表指针的地址:" << (int*)(&d2) << endl;
    cout << "虚函数表的地址--第一个虚函数的地址:" << (int*)(*(int*)(&d2)) << endl;
    ifun = (long*)*(int*)(&d2);
    pfun = (Fun)ifun[0];
    pfun();
    pfun = (Fun)ifun[1];
    pfun();

    pfun = (Fun)ifun[2];
    pfun();
 

    return 0;

}
