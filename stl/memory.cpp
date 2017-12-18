#include <memory>
#include <iostream>
#include <vector>
#include <string>

template<typename T>
class Blob;

//定义Blob广义上的指针,伴随指针类---迭代器
template<typename TT>
class BlobPtr{
    public:
        BlobPtr():curr(0){}
        BlobPtr(Blob<TT> &bl,std::size_t sz = 0):wptr(bl.data),curr(sz){}
        TT & operator *() const;
        TT * operator ->() const;
        BlobPtr<TT> & operator ++();
        BlobPtr<TT> & operator --();
        BlobPtr<TT> & operator ++(int);
        BlobPtr<TT> & operator --(int);
    private:
        std::shared_ptr<std::vector<TT>> check(std::size_t,const std::string &) const;
        std::size_t curr;
        std::weak_ptr<std::vector<TT>> wptr;
};

template<typename TT>
TT & BlobPtr<TT>::operator *() const{
    auto p = check(curr,"dereferebce past end");
    return (*p)[curr];
}

template<typename TT>
TT * BlobPtr<TT>::operator ->() const{
    return & this->operator*();
}

template<typename TT>
BlobPtr<TT> & BlobPtr<TT>::operator ++() {
    check(curr,"increment past end of BlobPtr");
    ++curr;
    return *this;
}

template<typename TT>
BlobPtr<TT> & BlobPtr<TT>::operator --() {
    --curr;
    check(curr,"increment past end of BlobPtr");
    return *this;
}

template<typename TT>
BlobPtr<TT> & BlobPtr<TT>::operator ++(int) {
    BlobPtr<TT> ret = *this;
    ++(*this);
    return ret;
}

template<typename TT>
BlobPtr<TT>& BlobPtr<TT>::operator --(int) {
    BlobPtr<TT> ret = *this
    --(*this);
    return ret;
}


template<typename TT>
std::shared_ptr<std::vector<TT>> BlobPtr<TT>::check(std::size_t i,const std::string &msg) const{
    auto ret = wptr.lock();
    if(!ret){
        throw std::runtime_error("unbound BlobPtr");
    }
    if(i >= ret->size()){

        throw std::out_of_range(msg);
    }

    return ret;
}

template<typename T>
class Blob{
    friend class BlobPtr<T>;
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
                throw std::out_of_range(msg);
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
    BlobPtr<std::string> sbr(sb1,1);
    std::string s = *sbr;
    std::cout << s << std::endl;
    s = *(++sbr);
    std::cout << s << std::endl;
    return 0;
}
