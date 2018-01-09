#include <iostream>

using namespace std;
class Token{

    friend ostream & operator<<(ostream &os,const Token &t);
    public:
    Token():tok(INT),ival(0){};
    Token(const Token &t):tok(t.tok){copyUnion(t);};
    Token(Token &&t):tok(t.tok){
        cout << "move" << endl;
        copyUnion(t);
    };
    Token & operator=(const Token &t);
    Token & operator=(Token &&t);
    Token & operator=(int);
    Token & operator=(char);
    Token & operator=(double);
    Token & operator=(const string &);
    ~Token(){if(tok == STRING){sval.~string();}};

    private:
    enum {INT,CHAR,DOUBLE,STRING} tok;
    union{
        int ival;
        char cval;
        double dval;
        string sval;
    };
    void copyUnion(const Token &t);
    void copyUnion(Token &&t);


};

void Token::copyUnion(const Token &t){
    switch(t.tok){
        case Token::INT : ival = t.ival;break;
        case Token::CHAR : cval = t.cval;break;
        case Token::DOUBLE : dval = t.dval;break;
        case Token::STRING : new(&sval)string(t.sval);break;
    }

}
void Token::copyUnion(Token &&t){
    switch(t.tok){
        case Token::INT : ival = t.ival;break;
        case Token::CHAR : cval = t.cval;break;
        case Token::DOUBLE : dval = t.dval;break;
        case Token::STRING : new(&sval)string(t.sval);break;
    }

}

Token & Token::operator=(const Token &t){
    if(tok == Token::STRING && t.tok !=Token::STRING){
        sval.~string();
    }
    if(tok == Token::STRING && t.tok ==Token::STRING){
        sval = t.sval;
    }
    else{
        copyUnion(t);
    }

    tok = t.tok;
    return *this;
}

Token & Token::operator=(Token &&t){
    cout << "move" << endl;
    if(tok == Token::STRING && t.tok !=Token::STRING){
        sval.~string();
    }
    if(tok == Token::STRING && t.tok ==Token::STRING){
        sval = t.sval;
    }
    else{
        copyUnion(t);
    }

    tok = t.tok;
    return *this;
}


Token & Token::operator=(int i){
    if(tok == Token::STRING){
        sval.~string();
    }
    ival = i;
    tok = Token::INT;

    return *this;

}

Token & Token::operator=(char c){
    if(tok == Token::STRING){
        sval.~string();
    }
    cval = c;
    tok = Token::CHAR;

    return *this;

}

Token & Token::operator=(double d){
    if(tok == Token::STRING){
        sval.~string();
    }
    dval = d;
    tok = Token::DOUBLE;

    return *this;

}

Token & Token::operator=(const string &s){
    if(tok == Token::STRING){
        sval = s;
    }
    else{
        new (&sval) string(s);
    }
    tok = Token::STRING;
    return *this;
}

ostream & operator<<(ostream &os,const Token &t){
    switch(t.tok){
        case Token::INT : os << t.ival << endl;break;
        case Token::CHAR : os << t.cval << endl;break;
        case Token::DOUBLE : os << t.dval << endl; break;
        case Token::STRING : os << t.sval << endl;break;
    }
    return os;

}



int main(){
    Token t;
    t = 1;
    cout << t << endl;
    t = 'c';
    cout << t << endl;
    t = 4.000;
    cout << t << endl;
    t = *new string("raohui");
    cout << t << endl;
    string s("haha");
    Token t1;
    t1 = s;
    t = std::move(t1);
    cout << t << endl;
    return 0;
}
