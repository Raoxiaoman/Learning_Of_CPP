#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

//删除字符串两边的空格
void trim(string &s){
    if(!s.empty()){
        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ")+1);
    }
}

//在字符重删除指定的字符串
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

/**
 *说明： 如果 string sub = ”abc“；
    string s = ”cdeabcigld“；
    s.find(sub) , s.rfind(sub) 这两个函数，如果完全匹配，才返回匹配的索引, 
    即：当 s 中含有 abc 三个连续的字母时，才返回当前索引。
    s.find_first_of(sub),   s.find_first_not_of(sub),   s.find_last_of(sub),  s.find_last_not_of(sub)
    这四个函数，查找 s 中含有 sub 中任意字母的索引。
 *
 * */
void string_find_test(string str,string flag){
    cout << str << endl;
    cout << flag << endl;
    //find_first_of 函数 返回 flag 中任意字符 在 s 中第一次出现的下标位置
    cout << str.find_first_of(flag) << endl;
    // 从字符串 s 下标 5 开始，查找字符串flag , 返回flag 在 s 中的下标
    cout << str.find(flag,5) << endl;

    // 查找s中flag 出现的所有位置。
    int i=1;
    size_t position = 0;
    while((position=str.find_first_of(flag,position))!=string::npos)
    {
        //position=str.find_first_of(flag,position);
        cout<<"position"<<i<<":"<<position<<endl;
        position++;
        i++;
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
    string_find_test("raohuijiayouhahahhnimei","h");
    return 0;
}
