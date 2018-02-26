#include <iostream>
#include <string>

using namespace std;
template <typename T>
class SmartPtr
{
public:
    SmartPtr (T *p);
    virtual ~SmartPtr ();
    SmartPtr(const SmartPtr<T> &);
    SmartPtr<T> & operator =(const SmartPtr<T> &rhs);
    T & operator *();
    void printUseCount(){
        cout << *use_count << endl;
    }

private:
    T *ptr;;
    int *use_count;
};

template <typename T>
T & SmartPtr<T>::operator*(){
    if(ptr !=nullptr){
        return *ptr;
    }
};

template <typename T>
SmartPtr<T>::SmartPtr(T *p):ptr(p){
    try {
        use_count = new int(1);
    }catch(...) {
        delete ptr;
        ptr = nullptr;
        use_count = nullptr;
        cout << "use_count error!" << endl;
        exit(1);
    }
    
    cout << "Construction is successful" << endl;

}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T> &sm){
    ptr = sm.ptr;
    use_count = sm.use_count;
    (*use_count)++;
    cout << "Copy Construction is successful" << endl;
}

template <typename T>
SmartPtr<T>::~SmartPtr(){
    if(--(*use_count) == 0){
        delete ptr;
        delete use_count;
        ptr = nullptr;
        use_count = nullptr;
        cout << "Destruction is successful" << endl;
    }
    else{
        cout <<  "-- use_count" << endl;
    }
}

template <typename T>
SmartPtr<T> & SmartPtr<T>::operator=(const SmartPtr<T> &rhs){
    if(--(*use_count) == 0){
        delete ptr;
        delete use_count;
        cout << "Destruction is successful" << endl;
    }
    ++(*rhs.use_count);
    ptr = rhs.ptr;
    use_count = rhs.use_count;

    cout << "Assignmet operator overload is successful" << endl;
    return *this;
}

int main(int argc, char *argv[])
{
    SmartPtr<string> sp(new string("raohui"));
    cout << *sp << endl;
    sp.printUseCount();
    SmartPtr<string> sp1(sp);
    cout << *sp1 << endl;
    sp.printUseCount();
    SmartPtr<string> sp2(new string("haha"));
    cout << *sp2 << endl;
    sp2 = sp1;
    sp.printUseCount();
    cout << *sp2 << endl;


    return 0;
}





