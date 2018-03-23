#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;
class People{
    public:
        string name;
        size_t age;
        People(string n,size_t a):name(n),age(a){}

};

size_t hasher(const People &p){
    return hash<int>()(p.age);
}

bool eqOp(const People &p1,const People &p2){
    return p1.name == p2.name && p1.age == p2.age;
}


void word_count(){
    map<string,size_t> words;
    set<string> exclude = {"a","A"};

    string word;
    while(cin >> word){
        if(exclude.find(word)  == exclude.end()){
            words[word]++;
        }
    }

    for(auto w : words){
        cout << w.first << ":" << w.second << endl;
    }

}


map<string,string> buildMap(std::ifstream &map_file){
    map<string,string> map;
    string key;
    string value;
    while(map_file >> key && getline(map_file,value)){
        if(value.size() > 1){
            map[key] = value.substr(1);
        }else{
            throw runtime_error("no rule for" + key);
        }
    }

    return map;

}

const string& transform(const string &s,const map<string,string> &map){
    auto map_it = map.find(s);
    if(map_it != map.end()){
        return map_it->second;
    }else{
        return s;
    }

}


void word_transform(std::ifstream &map_file,std::ifstream &input){
    map<string,string> rule_map = buildMap(map_file);
    for_each(rule_map.cbegin(),rule_map.cend(),[](pair<string,string> rule){cout << rule.first 
            << ":" << rule.second << endl;});
    string text;
    while(getline(input,text)){
        istringstream line(text);
        string word;
        bool firstWorld = true;
        while(line >> word){
            if(firstWorld){
                firstWorld = false;
                cout << transform(word,rule_map);
            }else{
                cout << " ";
                cout << transform(word,rule_map);
            }
        }

        cout << endl;


    }


}


int main(){
    //word_count();
    std::ifstream rule("./input/rule.txt");
    std::ifstream words("./input/words.txt");
    word_transform(rule,words);
    unordered_map<People,size_t,decltype(hasher) *,decltype(eqOp) *> peoples(10,hasher,eqOp);
    People p("raohui",20);
    peoples[p] = 100;
    People p1("leihui",20);
    peoples[p1] = 90;
    for_each(peoples.cbegin(),peoples.cend(),[](pair<People,size_t> p)
            {cout << p.first.name << ":" <<p.first.age << ":"<< p.second << endl;});
    return 0;
}
