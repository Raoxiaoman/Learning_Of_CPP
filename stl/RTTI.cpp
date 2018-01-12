#include <typeinfo>
#include <iostream>

using namespace std;

class base{
    friend  bool operator ==(const base& lhs, const base& rhs);
    public:
    int i;
    base(int a = 0):i(a){}
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
    protected:
        bool equals(const base & ) const;

};

bool child_of_base::equals(const base &b) const{
    auto r = dynamic_cast<const child_of_base &>(b);
    cout << "child equals" << endl;
    return i == r.i && j == r.j;
}

int main(){
    base b1(1);
    base b2(2);
    child_of_base cb1(1,1);
    child_of_base cb2(1,1);

    cout << (b1 == b2) << endl;
    cout << (cb1 == cb2) << endl;
    cout << (b1 == cb1) << endl;

    return 0;

}
