#include <typeinfo>
#include <iostream>

using namespace std;
class base{
    friend  bool operator ==(const base& lhs, const base& rhs);
    public:
    int i;
    base(int a = 0):i(a){}
    virtual void fun()const{
        cout << "base fun" << endl;
    }
    protected:
    virtual bool equals(const base & b) const{
        cout << "base equals" << endl;
        return i ==  b.i;
    }
};


bool operator ==(const base &lhs,const base &rhs){
    cout << "lhs:" << typeid(lhs).name() << endl;
    cout << "rhs:" << typeid(rhs).name() << endl;
    return typeid(lhs) == typeid(rhs) && lhs.equals(rhs);
}

class child_of_base: public base {
    public:
        double j;
        child_of_base(int a,double b):j(b){
            i = a;
        }
    void fun()const{
        cout << "chlid fun" << endl;
    }
    void fun2()const{
        cout << "chlid fun2 and i = "<< j << endl;
    }
    protected:
        bool equals(const base & ) const;

};

bool child_of_base::equals(const base &b) const{
    auto r = dynamic_cast<const child_of_base &>(b);
    cout << "child equals" << endl;
    return i == r.i && j == r.j;
}

int main(){

    cout << "---------dynamic_cast test---------" << endl;
    base b1(1);
    base b2(2);
    child_of_base cb1(1,1);
    child_of_base cb2(1,1);
    cout << (b1 == b2) << endl;
    cout << (cb1 == cb2) << endl;
    cout << (b1 == cb1) << endl;
    base *pb2 = &b1;
    child_of_base *pcb2 = dynamic_cast<child_of_base *>(pb2);
    if(pcb2==nullptr){
        cout << "dynamic_cast null" << endl;
    }else{
        pcb2->fun();
    }

    cout << "--------static_cast test----------" << endl;
    base *pb1 = &b1;
    child_of_base *pcb1 = static_cast<child_of_base *>(pb1);
    pcb1->fun();
    pcb1->j = 10;
    pcb1->fun2();


    cout << "---------reinterpret_cast test---------" << endl;
    int ra = 49;
    int *rpi = &ra;
    char *rpc = reinterpret_cast<char* >(rpi);
    cout << *rpc <<  endl;
    unsigned long rb  = reinterpret_cast<unsigned long>(rpi);
    cout << rb << endl;
    int *rpi2 = reinterpret_cast<int *>(rb);
    cout << *rpi2 << endl;


    cout << "---------const_cast test-----------" << endl;
    const int ca = 10;
    int *cpa = const_cast<int *>(&ca);
    cout << *cpa << endl;
    cout << &ca << "------" << cpa << endl;

    return 0;

}
