#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

void test1(){
    ifstream file("./input/test.txt");
    istream_iterator<string> item_iter(file),eof;
    vector<string> test(item_iter,eof);
    for_each(test.cbegin(),test.cend(),[](const string &s){cout << s << endl;});
}

void test2(){
    istream_iterator<int> item_iter(cin),eof;
    vector<int> test(item_iter,eof);
    ostream_iterator<int> out_iter(cout," ");
    sort(test.begin(),test.end());
    copy(test.cbegin(),test.cend(),out_iter);
    cout << endl;
}

//void test3(){
    //istream_iterator<pair<string,int>> item_iter(cin),eof;
    //vector<pair<string,int>> test(item_iter,eof);
    //for(auto &v : test){
        //cout << v.first << ":" << v.second  << endl;
    //}
//}

int main(){
    
    test1();
    test2();
    //test3();
    return 0;
}
