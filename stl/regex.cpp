#include <regex>
#include <iostream>
#include <string>
#include <fstream>


using namespace std;
void regex_search_test(){
    string test_str = "receipt freind theif receive";
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*"; 
    regex r(pattern);
    smatch result;
    if(regex_search(test_str,result,r)){
        cout << result.str(0) << endl; 
    }

}

void sregex_iterator_test(){
    string test_str = "receipt freind theif receive";
    string pattern("[^c]ei");
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*"; 
    regex r(pattern);

    for(sregex_iterator it(test_str.begin(),test_str.end(),r),end; it != end;++it){
        cout << it->str(0) << endl;
    }
}

bool vaild(const smatch& s){

    if(s[1].matched){
        return s[3].matched && (s[4].matched == 0 || s[4].str() == " ");
    }
    else{
        return !s[3].matched && s[4].str() == s[6].str();
    }

}

//1.(\\()?表示区号部分可选的左括号
//2.(\\d{3})表示区号
//3.(\\))?表示区号部分可选的右括号
//4.([-. ])?表示区号部分可选的分隔符
//5.(\\d{3})表示号码的下三位数字
//6.([-. ])?表示可选的分隔符
//7.(\\d{4})表示号码的最后四位数字
void sub_match_test(){

    ifstream input("./input/regex_phone_num.txt");
    string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
    string s;
    regex r(phone);

    while(getline(input,s)){
        for(sregex_iterator it(s.begin(),s.end(),r),end_it;it != end_it;++it){
            if(vaild(*it)){
                cout << "vaild:" << it->str(0) << endl;
            }
            else{
                cout << "Invaild:" << it->str(0) << endl;
            }
        }
    }

}

void regex_replace_test(){
    ifstream input("./input/regex_phone_num.txt");
    string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
    string s;
    regex r(phone);
    string fmt = "$2.$5.$7";

    while(getline(input,s)){
        cout << regex_replace(s,r,fmt,std::regex_constants::format_no_copy) << endl;
    }

}

int main(){
    regex_search_test();
    sregex_iterator_test();
    sub_match_test();
    regex_replace_test();
    return 0;
}
