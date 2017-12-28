#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

using namespace std;
template <typename T>
class MyVector{
    public:
        MyVector(MyVector<T> && v) noexcept;
        MyVector():elements(nullptr),first_free(nullptr),cap(nullptr){}
        MyVector(const MyVector<T> & v);
        MyVector & operator=(const MyVector<T> &v);
        MyVector & operator=(MyVector<T> &&v) noexcept;
        virtual ~MyVector();
        void push_back(const T& item);
        void push_back(T&& item);
        size_t size(){return first_free - elements;}
        size_t capacity(){return cap - elements;}
        T* begin() const {return elements;}
        T* end() const {return first_free;}

    private:
        void check_and_alloc(){if(size()==capacity()) reallocate();}
        std::pair<T*,T*> alloc_n_copy(const T* item1,const T* item2);
        void free();
        void reallocate();
        static std::allocator<T> alloc;
        T *elements;
        T *first_free;
        T *cap;

};

template <typename T>
std::allocator<T> MyVector<T>::alloc;

template <typename T>
void MyVector<T>::push_back(const T& item){
    check_and_alloc();
    alloc.construct(first_free++,item);
}

template <typename T>
void MyVector<T>::push_back( T&& item){
    check_and_alloc();
    alloc.construct(first_free++,move(item));
}

template <typename T>
std::pair<T*,T*> MyVector<T>::alloc_n_copy(const T* item1,const T* item2){
    auto data = alloc.allocate(item2 - item1);
    return {data,std::uninitialized_copy(item1, item2, data)};
}

template <typename T>
void MyVector<T>::free(){
    if(elements){
        for(auto p = first_free;p!=elements;){
            alloc.destroy(--p);
        }
        alloc.deallocate(elements,cap-elements);
    }
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T> & v){
    auto newdata = alloc_n_copy(v.begin(),v.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

template <typename T>
MyVector<T>::MyVector(MyVector<T> &&v) noexcept:elements(v.elements),first_free(v.first_free),cap(v.cap) {
    //重点 移动构造函数需要将传入的右值置为可析构的状态
    v.elements = v.first_free = v.cap = nullptr;
}

template <typename T>
MyVector<T>::~MyVector(){
    free();
}

template <typename T>
MyVector<T> & MyVector<T>::operator=(const MyVector<T> &v){
    auto newdata = alloc_n_copy(v.begin(),v.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
    return *this;
}

template <typename T>
MyVector<T> & MyVector<T>::operator=(MyVector<T> &&v)noexcept{
    if(this != &v){
        free();
        elements = v.elements;
        first_free = v.first_free;
        cap = v.cap;

        //重点 移动赋值函数需要将传入的右值置为可析构的状态
        v.elements = v.first_free = v.cap = nullptr;
    }

    return *this;
}


template <typename T>
void MyVector<T>::reallocate(){
    auto newcapacity = size()?size()*2:1;
    auto newdata = alloc.allocate(newcapacity);

    //auto dest = newdata;
    //auto elem = elements;
    //for(size_t i = 0;i!=size();i++){
        //alloc.construct(dest++,std::move(*elem++));
    //}
    //使用移动迭代器
    auto dest  = std::uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), newdata);
    free();
    elements = newdata;
    first_free = dest;
    cap = elements+ newcapacity;

}

int main(){
    MyVector<std::string> mv;
    string s = "raohui";
    mv.push_back(s);
    s = "haha";
    mv.push_back(s);
    for_each(mv.begin(),mv.end(),[](std::string &s){std::cout << s << std::endl;});
    return 0;
}
