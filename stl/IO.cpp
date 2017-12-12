#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>

using namespace std;
void fstream_test(){
    ifstream input("./input/input.txt",ifstream::in);
    list<string> strs;
    string str;
    if(input){
        while(input >> str){
            strs.push_back(str);
        }
    }
    for_each(strs.cbegin(),strs.cend(),[](const string& s){cout << s << endl;});
}

struct PersonInfo{
    string name;
    vector<string> phones;
};
void  sstring_test(){
    ifstream input("./input/phoneNum.txt");
    string line;
    vector<PersonInfo> ps;
    if(input){
        while(getline(input,line)){
            PersonInfo p;
            istringstream info(line);
            info >> p.name;
            string word;
            while(info >> word){
                p.phones.push_back(word);
            }

            ps.push_back(p);
        }
    }

    for_each(ps.cbegin(),ps.cend(),[](const PersonInfo &p){ cout << p.name << ":phoneNum:" << endl;
            for_each(p.phones.cbegin(),p.phones.cend(),[](const string &s){cout << s << endl;});});
}

int main(){
    fstream_test();
    sstring_test();
    return 0;
}
