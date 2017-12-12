#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>

using namespace std;

int main(){
    vector<int> ver;
    ver.push_back(1);
    ver.push_back(2);
    ver.push_back(3);
    ver.push_back(4444);
    ver.push_back(5);


    for (unsigned int i = 0; i < ver.size(); i++) {
        cout << ver[i] << endl;  
    }


    vector<int>::iterator iter  = ver.begin();
    for (; iter!=ver.end() ; iter++) {
        cout << *iter << endl; 
    }


    list<string> lists;
    lists.push_back("raohui");
    lists.push_back("hahh");
    lists.push_back("qihai");
    lists.push_back("leihui");
    lists.push_back("jiayou");
    lists.push_back("gaoxiao");

    list<string>::iterator  liter = lists.begin();
    for(; liter!=lists.end(); liter++){
        cout << *liter << endl; 
    }

    map<int,string> maps;
    pair<int,string> pair1(1,"raohui");
    pair<int,string> pair2(2,"qihai");


    maps.insert(pair1);
    maps.insert(pair2);

    map<int,string>::iterator miter = maps.begin();

    for(;miter!=maps.end();miter++){
        cout << miter->first << endl;
        cout << miter->second << endl;
    }



    return 0;
}
