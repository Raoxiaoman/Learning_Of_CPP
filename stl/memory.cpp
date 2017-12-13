#include <memory>
#include <iostream>
#include <vector>
#include <string>

template<typename T>
class Blob{
    public:
        typedef typename std::vector<T>::size_type size_type;
        Blob();
        Blob(std::initializer_list<T> il);
        size_type size(){return data->size();};
        bool empty() const {return data->empty();};
        void push_back(const T &s){data->push_back(s);};
        void pop_back();
        T& front();
        T& back();
        T& back() const;
        T& front() const;
        void print() const;

    private:
        void check(size_type i,const T &msg) const{
            if(i >= data->size()){
                std::cout <<  msg << std::endl;
                throw msg;
            }
        };
    private:
        std::shared_ptr<std::vector<T>> data;
};

template<typename T>
Blob<T>::Blob(): data(std::make_shared<std::vector<T>>()){}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il): data(std::make_shared<std::vector<T>>(il)){}

template<typename T>
T& Blob<T>::front(){
   check(0,"front on empty Blob<T>"); 
   return data->front();
}

template<typename T>
T& Blob<T>::front() const{
   check(0,"front on empty Blob<T>"); 
   return data->front();
}

template<typename T>
T& Blob<T>::back(){
   check(0,"back on empty Blob<T>"); 
   return data->back();
}

template<typename T>
T& Blob<T>::back() const{
   check(0,"back on empty Blob<T>"); 
   return data->back();
}

template<typename T>
void Blob<T>::pop_back(){
   check(0,"pop_back on empty Blob<T>"); 
   data->pop_back();
}

template<typename T>
void Blob<T>::print() const{
    for(auto s:*data){
        std::cout << s << std::endl;
    }
}

int main(){
    Blob<std::string> sb1;
    {   Blob<std::string> sb = {"raohui","test","haha"};
        sb1 = sb;
        sb.print();
        sb1.push_back("haha");
        sb.print();
    }
    sb1.print();
    return 0;
}
