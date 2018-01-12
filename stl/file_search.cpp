#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <memory>

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
                word_num[word] = no;
            }
            no->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string &word)const {
    //静态的，函数结束不会被销毁
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


class Query_base{
    friend class Query;
    protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
    private:
    virtual QueryResult eval(const TextQuery &) = 0;
    virtual string rep() = 0;
};

class WordQuery : public Query_base{

};

class NotQuery : public Query_base{

};

class BinaryQuery : public Query_base{

};


class AndQuery :public BinaryQuery{

};

class OrQuery :public BinaryQuery{

};

class Query{
    friend Query operator ~(const Query &);
    friend Query operator &(const Query &);
    friend Query operator |(const Query &,const Query &);
    public:
    Query(const string &);
    QueryResult eval(const TextQuery & t){
        return q->eval(t);
    }

    string rep() const {
        return q->rep();
    }
    private:
    Query(shared_ptr<Query_base> qq):q(qq){};
    std::shared_ptr<Query_base> q;

};

ostream & operator << (ostream &os ,const Query &q){
    return  os << q.rep() << endl;
}


int main(){
    ifstream input("./input/file_search.txt");
    runQuery(input);
    return 0;
}
