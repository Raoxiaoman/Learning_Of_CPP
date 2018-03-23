#include <iostream>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <vector>
#include <string>

using namespace std;

int main(){

    /**
     *vector:就看做数组，支持[],随机访问，但是中间部位插入，删除代价大，不支持push_front|pop_front
     *相当于数组，但其大小可以不预先指定，并且自动扩展。它可以像数组一样被操作，由于它的特性我们完全可以将 vector 看作动态数组。
     *在创建一个 vector 后，它会自动在内存中分配一块连续的内存空间进行数据存储，
     *初始的空间大小可以预先指定也可以由 vector 默认指定，这个大小即 capacity （）函数的返回值。
     *当存储的数据超过分配的空间时 vector 会重新分配一块内存块，但这样的分配是很耗时的，效率非常低。
     * */
    vector<int> ver = {55,44,66};
    ver.push_back(1);
    ver.push_back(2);
    ver.push_back(3);
    ver.push_back(4444);
    ver.push_back(5);

    cout << "*********vector begin***********" << endl;
    //vector[]随机访问
    for (unsigned int i = 0; i < ver.size(); i++) {
        cout << ver[i] << " ";  
    }
    cout << endl;

    //vertor使用迭代器访问
    vector<int>::iterator iter  = ver.begin();
    for (; iter!=ver.end() ; iter++) {
        cout << *iter << " "; 
    }
    cout << endl;
    //vertor使用insert和erase
    auto iiter = ver.begin();
    ver.insert(iiter+4, 55);
    ver.erase(iiter+2);
    for (auto iiiter : ver) {
        cout << iiiter <<" ";
    }
    cout << endl;
    cout << "*********vector end***********" << endl;


    /**
     * list: 不支持随机访问[],但中间部分进行插入删除操作十分方便，支持push_front和pop_front
     * 是一个线性链表结构，它的数据由若干个节点构成，每一个节点都包括一个信息块（即实际存储的数据）、一个前驱指针和一个后驱指针。
     * 它无需分配指定的内存大小且可以任意伸缩，这是因为它存储在非连续的内存空间中，并且由指针将有序的元素链接起来。
     * */

    cout << "*********list begin***********" << endl;
    list<string> lists = {"heloo","taiyan"};
    lists.push_back("raohui");
    lists.push_back("hahh");
    lists.push_back("qihai");
    lists.push_back("leihui");
    lists.push_front("raohuifront");
    lists.push_back("jiayou");
    lists.push_back("gaoxiao");


    //list使用迭代器访问
    list<string>::iterator  liter = lists.begin();
    for(; liter!=lists.end(); liter++){
        cout << *liter <<" " ; 
    }
    cout << endl;
    auto  llter = lists.begin();
    //list使用insert和erase,list的迭代器不支持+和-运算符重载，但是支持++和--
    lists.insert(++llter,"heheh");
    auto llter_and = lists.end();
    lists.erase(--llter_and);

    for(auto lllter:lists){
        cout << lllter<< " ";
    }
    cout << endl;
    cout << "*********list end***********" << endl;
    cout << "*********deque begin***********" << endl;

    /**
     *deque:支持随机访问[],支持push_front和pop_front,中间部分插入和删除，效率比vetor好但是比list差。
     *它不像 vector 把所有的对象保存在一块连续的内存块，而是采用多个连续的存储块，并且在一个映射结构中保存对这些块及其顺序的跟踪。
     *向deque两端添加或删除元素的开销很小，它不需要重新分配空间。
     * */
    deque<string> deques = {"wuyu","jiada"};
    deques.push_back("raohui");
    deques.push_back("hahh");
    deques.push_back("qihai");
    deques.push_back("leihui");
    deques.push_front("raohuifront");
    deques.push_back("jiayou");
    deques.push_back("gaoxiao");

    //deque使用[]遍历
    for (size_t i = 0; i < deques.size(); ++i) {
        cout << deques[i] << " ";
    }
    cout << endl;

    //deque使用迭代器遍历
    auto diter = deques.begin();
    for(;diter!=deques.end();diter++){
        cout << *diter<< " ";
    }
    cout << endl;

    auto dditer = deques.begin();
    //deque进行insert和erase操作
    deques.insert(dditer+3,"hehea");
    deques.erase(dditer+5);
    for (auto ddditer : deques) {
        cout << ddditer << " ";
    }
    cout << endl;
    cout << "*********deque end***********" << endl;


    /**
     *关联容器的特点是明显的，相对于顺序容器，有以下几个主要特点：
     *A. 其内部实现是采用非线性的二叉树结构，具体的说是红黑树的结构原理实现的；
     *B. set 和 map 保证了元素的唯一性，mulset 和 mulmap 扩展了这一属性，可以允许元素不唯一；
     *C. 元素是排序的集合，默认在插入的时候按升序排列。
     *D. 由于存储元素是排序的，所以关联容器对于元素插入操作是无序的，插入的顺序在存储内部由于排序会被打乱,
     *所以关联容器不支持push_back,push_front,pop_back,pop_front的操作
     *由于内部存储结构是红黑树所以关联容器插入和删除操作比vector块，但比list慢，因为红黑树修改一个节点会涉及到其他节点的变动比list多,而且得重新排序，
     *关联容器查询效率比list快，因为红黑树是排序的，但还比vector慢.
     **/

    cout << "*********map begin***********" << endl;
    map<int,string> maps ={{7,"hai"},{8,"wasai"}};
    pair<int,string> pair1(1,"raohui");
    pair<int,string> pair2(2,"qihai");
    //map使用insert和erase
    maps.insert(pair1);
    maps.insert(pair2);
    //map也可以使用[]访问，以这种方式[key]
    cout << maps[1] << endl;
    cout << maps[2] << endl;

    //map使用迭代器遍历
    for (auto miter = maps.begin(); miter != maps.end(); ++miter) {
        std::cout << miter->first << ":";
        cout << miter->second << " ";
    }
    cout << endl;

    //pair也可以使用{key,value}的方式,map的元素的排序是根据key来比较的
    //map的元素的唯一性是一个key对应一个value,相同key的前面的value会被后面的value覆盖
    maps.insert({2,"heheh"});
    maps.insert({4,"你好lo"});
    maps.erase(2);
    //同为链式存储，map的迭代器不支持+和-运算符，支持++和--运算符
    maps.erase(maps.begin()++);
    for (auto mmiter : maps) {
        cout << mmiter.first << ":";
        cout << mmiter.second << " ";
    }
    cout << endl;
    cout << "*********map end***********" << endl;
    cout << "*********set begin***********" << endl;
    set<string> sets = {"raohui","gaoxiao","jiayou","lalalal","raohui"};

    //set使用迭代器访问
    set<string>::iterator siter = sets.begin();
    for(;siter!=sets.end();siter++){
        cout << *siter<< " ";
    }
    cout << endl;
    auto ssiter = sets.begin();
    //set使用insert和erase,set的具有元素的唯一性和排序性
    sets.insert("heheh");
    sets.insert("raohui");
    //同为链式存储，set的迭代器不支持+和-运算符，支持++和--运算符
    sets.erase(ssiter++);
    for (auto sssiter : sets) {
        cout << sssiter << " ";
    }
    cout << endl;
    cout << "*********set end***********" << endl;
    return 0;
}
