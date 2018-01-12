#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>

using namespace std;
class QueryResult;
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

class QueryResult{
    friend ostream & print(ostream &,const QueryResult &);
    public:
    using line_no = vector<string>::size_type;
    set<line_no>::iterator begin();
    set<line_no>::iterator end();
    shared_ptr<vector<string>> get_file();
    QueryResult(string w,shared_ptr<vector<string>> l,shared_ptr<set<line_no>> n):word(w),lines(l),num(n){}
    private:
    string word;
    shared_ptr<vector<string>> lines;
    shared_ptr<set<line_no>> num;
};

set<QueryResult::line_no>::iterator QueryResult::begin(){
    return num->begin();
}

set<QueryResult::line_no>::iterator QueryResult::end(){
    return num->end();
}

shared_ptr<vector<string>> QueryResult::get_file(){
    return lines;
}

ostream & print(ostream &os,const QueryResult &qr){
    os << qr.word <<  "  occurs  " << qr.num->size() << "  times" << endl;
    for(auto n: *qr.num){
        os << "\t(line" << n + 1 << ")" << *(qr.lines->begin()+n) << endl;
    }
    return os;
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
    virtual QueryResult eval(const TextQuery &)const = 0;
    virtual string rep()const = 0;
};

class WordQuery : public Query_base{
    friend class Query;
    WordQuery(const string &s):queryWord(s){};

    QueryResult eval(const TextQuery &t)const{
        return  t.query(queryWord);
    }

    string rep()const{return queryWord;}

    string queryWord;


};

class Query{
    friend Query operator ~(const Query &);
    friend Query operator &(const Query &,const Query &);
    friend Query operator |(const Query &,const Query &);
    public:
    Query(const string &);
    QueryResult eval(const TextQuery & t) const{
        return q->eval(t);
    }

    string rep() const {
        return q->rep();
    }
    private:
    Query(shared_ptr<Query_base> qq):q(qq){};
    std::shared_ptr<Query_base> q;

};

inline Query::Query(const string &s):q(new WordQuery(s)){}
ostream & operator << (ostream &os ,const Query &q){
    return  os << q.rep() << endl;
}

class NotQuery : public Query_base{
    friend Query operator ~(const Query &);
    NotQuery(const Query &q):query(q){};
    string rep() const {return "~("+query.rep()+")";}
    QueryResult eval(const TextQuery &) const;
    Query query;

};

inline Query operator~(const Query &q){
    return shared_ptr<Query_base>(new NotQuery(q));
}

QueryResult NotQuery::eval(const TextQuery &t) const{
    auto result = query.eval(t);
    auto ret_lines = make_shared<set<line_no>>();
    auto beg = result.begin();
    auto end = result.end();

    auto size  = result.get_file()->size();

    for(size_t n = 0;n !=size;n++){
        if(beg == end || *beg != n){
            ret_lines->insert(n);
        }else if(beg!=end){
            ++beg;
        }

    }
    return QueryResult(rep(),result.get_file(),ret_lines);
}


class BinaryQuery : public Query_base{
    protected:
        BinaryQuery(const Query &l,const Query &r,string s):lhs(l),rhs(r),opSym(s){};
        string rep()const{return "(" + lhs.rep() + " "+opSym + " " + rhs.rep() + ")";}
        Query lhs;
        Query rhs;
        string  opSym;
};


class AndQuery :public BinaryQuery{
    friend Query operator&(const Query &,const Query &);
    AndQuery(const Query &left,const Query &right):BinaryQuery(left,right,"&"){}
    QueryResult eval(const TextQuery &) const;
    
};

inline Query operator& (const Query &lhs,const Query &rhs){
    return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

QueryResult AndQuery::eval(const TextQuery &t)const{
    auto left = lhs.eval(t);
    auto right = rhs.eval(t);
    auto ret_lines = make_shared<set<line_no>>();
    set_intersection(left.begin(),left.end(), right.begin(), right.end(),inserter(*ret_lines ,ret_lines->begin()));
    return QueryResult(rep(),left.get_file(),ret_lines);
}

class OrQuery :public BinaryQuery{
    friend Query operator  | (const Query &,const Query &);
    OrQuery(const Query &left,const Query &right):BinaryQuery(left,right,"|"){}
    QueryResult eval(const TextQuery &) const;

};

inline Query operator| (const Query &l,const Query &r){
    return shared_ptr<Query_base>(new OrQuery(l,r));
}

QueryResult OrQuery::eval(const TextQuery &t)const{
    auto left = lhs.eval(t);
    auto right = rhs.eval(t);
    auto ret_lines = make_shared<set<line_no>>(left.begin(),left.end());
    ret_lines->insert(right.begin(),right.end());
    return QueryResult(rep(),left.get_file(),ret_lines);
}



int main(){
    ifstream input("./input/file_search.txt");
    runQuery(input);
    return 0;
}
