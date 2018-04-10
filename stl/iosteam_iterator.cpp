#include <iostream>
#include <sstream>
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

void test4(){
    ifstream in("input/name.txt");
    string line,strtmp;
    vector<string> vect; 

    while(getline(in, line)){
        istringstream ss(line);
        while(getline(ss,strtmp,' ')){
            vect.push_back(strtmp);
        }
    }
    //istream_iterator<string> item_iter(in),eof;
    //vector<string> vect(item_iter,eof);
    cout << vect.size() << endl;
    for (auto iter : vect) {
        cout << iter << endl;
    }

    sort(vect.begin(), vect.end());
    for (auto iter : vect) {
        cout << iter << endl; 
    }
    vector<string> vect1;
    unique_copy(vect.begin(), vect.end(),back_inserter(vect1));
    cout << vect1.size() << endl;
    for (auto iter : vect1) {
        cout << iter << endl;
    }
}

int main(){

    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}
