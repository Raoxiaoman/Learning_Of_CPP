#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <type_traits>


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
        BlobPtr<TT> & operator ++(int); BlobPtr<TT> & operator --(int); private:
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
    template<typename U>
    friend bool operator== (const Blob<U> &,const Blob<U> &);
    public:
        typedef typename std::vector<T>::size_type size_type;
        Blob();
        Blob(std::initializer_list<T> il);
        template <typename it>Blob(it begin,it end);
        template <typename it>auto fcn(it bg) -> decltype(*bg){
            return *bg;
        }
        template <typename it>auto fcb(it bg) -> typename std::remove_reference<decltype(*bg)>::type{
            return *bg;
        }
        size_type size(){return data->size();};
        bool empty() const {return data->empty();};
        void push_back(const T &s){data->push_back(s);};
        void push_back(T &&s){data->push_back(std::move(s));};
        void pop_back();
        T& front();
        T& back();
        T& back() const;
        T& front() const;
        T& operator[](size_type i);
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
template<typename it>
Blob<T>::Blob(it begin,it end):data(std::make_shared<std::vector<T>>(begin,end)){}



template<typename U>
bool operator == (const Blob<U> &lhs,const Blob<U> &rhs){
    return *(lhs.data) == *(rhs.data);
}

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

template<typename T>
T& Blob<T>::operator[](size_type i){
    check(i,"subscript out of range");
    return (*data)[i];
}

template<typename T>
std::ostream &print(std::ostream &os,const T&t){
    os << t << std::endl;
    return os;
}

template<typename T,typename ... Args>
std::ostream &print(std::ostream &os,const T&t,const Args& ...args){
    os << t << ",";
    return  print(os,args...);
}

int main(){
    Blob<std::string> sb1;

    {   
        Blob<std::string> sb = {"raohui","test","haha"};
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
    std::cout << sb1[1] <<  std::endl;
    std::vector<int> v = {1,2,3,4};
    Blob<int> sb2(v.begin(),v.end());
    sb2.print();
    print(std::cout,"raohui",1,23,18.9);

    return 0;
}

