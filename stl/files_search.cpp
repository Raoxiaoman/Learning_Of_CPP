#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
class QueryResult{
    public:
        void print();
};

class TextQuery{
    public:
        TextQuery(ifstream &inputFile);
        QueryResult query();
};

void runQuery(ifstream &inputFile){
    TextQuery tq(inputFile);
    while(true){
        cout  << "enter word to look for , or q to quit" << endl;
        string s;
        if(!(cin >> s) && s == "q") break;

        tq.query().print();
    }

}

int main(){
    return 0;
}
