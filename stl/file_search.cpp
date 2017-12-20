#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <memory>
#include "Blob_memeryTest.cpp"

using namespace std;
class QueryResult{
    friend ostream & print(ostream &,const QueryResult &);
    public:
        using line_no = vector<string>::size_type;
        QueryResult(string w,shared_ptr<vector<string>> l,shared_ptr<set<line_no>> n):word(w),lines(l),num(n){}
    private:
        string word;
        shared_ptr<vector<string>> lines;
        shared_ptr<set<line_no>> num;
};


ostream & print(ostream &os,const QueryResult &qr){
    os << qr.word <<  "  occurs  " << qr.num->size() << "  times" << endl;
    for(auto n: *qr.num){
        os << "\t(line" << n + 1 << ")" << *(qr.lines->begin()+n) << endl;
    }
    return os;
}

class TextQuery{
    public:
        using line_no = vector<string>::size_type;
        TextQuery(ifstream &inputFile);
        QueryResult query(const string &s) const;
    private:
        shared_ptr<vector<string>> lines;
        map<string,shared_ptr<set<line_no>>> word_num;
};

TextQuery::TextQuery(ifstream &inputFile):lines(make_shared<vector<string>>()){
    string line;
    while(getline(inputFile,line)){
        lines->push_back(line);
        size_t n = lines->size() - 1;
        string word;
        istringstream words(line);
        while(words >> word){
            auto &no = word_num[word];
            if(!no){
                no.reset(new set<line_no>);
            }
            no->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string &word)const {
    //静态的，函数结束不会销毁
    static  shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto result = word_num.find(word);
    if(result == word_num.end()){
        return QueryResult(word,lines,nodata);
    }
    else{
        return QueryResult(word,lines,result->second);
    }

}


void runQuery(ifstream &inputFile){
    TextQuery tq(inputFile);
    while(true){
        cout  << "enter word to look for , or q to quit" << endl;
        string s;
        if(!(cin >> s) || s == "q") break;
        print(cout ,tq.query(s));
    }

}

class QueryResult_Blob{
    friend ostream & print_Blob(ostream &,const QueryResult_Blob &);
    public:
        using line_no = Blob<string>::size_type;
        QueryResult_Blob(string w,shared_ptr<Blob<string>> l,shared_ptr<set<line_no>> n):word(w),lines(l),num(n){}
    private:
        string word;
        shared_ptr<Blob<string>> lines;
        shared_ptr<set<line_no>> num;
};

ostream & print_Blob(ostream &os,const QueryResult_Blob &qr){
    os << qr.word <<  "  occurs  " << qr.num->size() << "  times" << endl;
    for(auto n: *qr.num){
        BlobPtr<string> bp(*(qr.lines),n);
        os << "\t(line" << n + 1 << ")" << *(bp) << endl;
    }
    return os;
}

class TextQuery_Blob{
    public:
        using line_no = Blob<string>::size_type;
        TextQuery_Blob(ifstream &inputFile);
        QueryResult_Blob query(const string &s) const;
    private:
        shared_ptr<Blob<string>> lines;
        map<string,shared_ptr<set<line_no>>> word_num;
};

TextQuery_Blob::TextQuery_Blob(ifstream &inputFile):lines(make_shared<Blob<string>>()){
    string line;
    while(getline(inputFile,line)){
        lines->push_back(line);
        size_t n = lines->size() - 1;
        string word;
        istringstream words(line);
        while(words >> word){
            auto &no = word_num[word];
            if(!no){
                no.reset(new set<line_no>);
            }
            no->insert(n);
        }
    }
}

QueryResult_Blob TextQuery_Blob::query(const string &word)const {
    //静态的，函数结束不会销毁
    static  shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto result = word_num.find(word);
    if(result == word_num.end()){
        return QueryResult_Blob(word,lines,nodata);
    }
    else{
        return QueryResult_Blob(word,lines,result->second);
    }

}


void runQuery_Blob(ifstream &inputFile){
    TextQuery_Blob tq(inputFile);
    while(true){
        cout  << "enter word to look for , or q to quit" << endl;
        string s;
        if(!(cin >> s) || s == "q") break;
        print_Blob(cout ,tq.query(s));
    }

}

int main(){
    ifstream input("./input/file_search.txt");
    runQuery_Blob(input);
    return 0;
}
