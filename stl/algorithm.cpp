#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <string>
#include <functional>
#include <list>
using namespace std;
using namespace std::placeholders;

void init(vector<size_t> &vec){
    for(size_t i = 1;i<=10;i++){
        vec.push_back(i);
    }
}

template<typename T>
void print(vector<T> &vec){
    cout << "================"<< endl;
    auto temp = vec.begin();
    while(temp != vec.end()){
        cout << *temp  << endl;
        temp++;
    }
}

bool isShorter(const string &s1,const string &s2){
    return s1.size() < s2.size();
}

bool sizeIsOk(const string &s1,size_t size){
    return s1.size() >= size;
}

void elimDups(vector<string> &s){
    sort(s.begin(),s.end(),isShorter);
    auto end_unique = unique(s.begin(),s.end());
    s.erase(end_unique,s.end());
    stable_sort(s.begin(),s.end(),isShorter);
}

void forPartition(vector<string> &s,size_t size){
    auto after_part = partition(s.begin(),s.end(),
            [size] (const string &a)
            { return a.size() >= size;} );
    s.erase(after_part,s.end());
}

void forPartition_bind(vector<string> &s,size_t size){
    auto bind_sizeIsOk =  bind (sizeIsOk,_1,size);
    auto after_part = partition(s.begin(),s.end(),bind_sizeIsOk);
    s.erase(after_part,s.end());
}

void check_book(){
    list<int> lists = {1,2,3,4};
    list<int> lists2,lists3;
    copy(lists.cbegin(),lists.cend(),front_inserter(lists2));
    copy(lists.cbegin(),lists.cend(),inserter(lists3,lists3.end()));
    for_each(lists2.cbegin(),lists2.cend(),[](int i){cout << i << endl;});
    for_each(lists3.cbegin(),lists3.cend(),[](int i){cout << i << endl;});
}


int main(){
    vector<size_t> vec;
    init(vec);
    print<size_t>(vec);
    int sum = accumulate(vec.begin(),vec.end(),0);
    cout << sum << endl;
    fill(vec.begin(),vec.end(),10);
    print<size_t>(vec);
    vector<size_t> vec1;
    fill_n(back_inserter(vec1),10,0);
    print<size_t>(vec1);
    string wordword[] = {"raohui","test","shuaige","hahh","hahh"};
    vector<string> words(wordword,wordword+4);
    print<string>(words);
    elimDups(words);
    print<string>(words);
    forPartition_bind(words,5);
    print<string>(words);
    check_book();

    return 0;
}
