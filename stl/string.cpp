#include <string>
#include <iostream>

using namespace std;

void trim(string &s){
    if(!s.empty()){
        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ")+1);
    }
}

void deleteMark(string &s,const string &Mark){
    string::size_type size = Mark.size();
    string::size_type pos = 0;
    if(!s.empty() && !Mark.empty()){
        while(1){
            pos = s.find(Mark,pos);
            if(pos==string::npos){
                return;
            }
            s.erase(pos,size);
        }
    }
}


int main(){
    string s = " helloWorld ";
    cout << s << endl;
    trim(s);
    cout << s << endl;
    s = " hello     World ";
    deleteMark(s, " ");
    cout << s << endl;
    return 0;
}
