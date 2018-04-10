#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <random>

using namespace std;
template <typename vtype>
class skipList{
public:
    // constructors, destructor
    skipList(int maxLevel);
    ~skipList();
    void insertNode(int key,vtype data);
    void deleteNode(int key);
    vtype* getData(int key);
    void displayList();
private:
    int Max_level;
    int RandomLevel();
    
    struct Node{
        int key;
        vtype data;
        int level;
        struct Node **next_nodes;
    };
    struct Node *head;
    struct Node *tail;

};
template <typename vtype>
void skipList<vtype>::displayList() {
    struct Node *cur = head;
    for (int i = Max_level -1; i >=0; --i) {
        while(cur->next_nodes[i] != tail){
            cout << cur->next_nodes[i]->key << "  ";
            cur = cur->next_nodes[i];
        }
        cout << endl;
        cur = head;
    }
}

template <typename vtype>
skipList<vtype>::skipList(int maxLevel) {
    Max_level = maxLevel > 0?maxLevel:1;
    cout << "maxLevel:" << maxLevel << endl; 
    head = new struct Node;
    tail = new struct Node;
    head->next_nodes = new struct Node *[Max_level];
    for (int i = 0; i < Max_level; ++i) {
        head->next_nodes[i] = tail;
    }
}

template <typename vtype>
skipList<vtype>::~skipList() {
    struct Node* cur = nullptr;
    while(head->next_nodes[0]!=tail){
        cur = head->next_nodes[0];
        head->next_nodes[0] = cur->next_nodes[0];
        delete[] cur->next_nodes;
        delete cur;
    }
    delete []head->next_nodes;
    delete head;
    delete tail;
}

template <typename vtype>
void skipList<vtype>::insertNode(int key,vtype data) {
    struct Node *update[Max_level];
    struct Node *cur = head;
    //找不同level下的前驱
    for(int i = Max_level -1;i>=0;i--){
        if(cur->next_nodes[i] == tail || cur->next_nodes[i]->key > key){
            update[i] = cur;
            //if(cur->next_nodes[i]->key > key){
                //cout << "level:" << i << endl;
                //cout << "cur-next-key:" <<  cur->next_nodes[i]->key << endl;
                //cout << "key:" <<  key << endl;
            //}
        }else {
            while(cur->next_nodes[i]!=tail && cur->next_nodes[i]->key < key){
                cur = cur->next_nodes[i];
            }
            update[i] = cur;
        }   
    }

    //创建node
    int level = RandomLevel();
    //cout <<"key:" << key<< "level:" << level << endl;
    struct Node *node = new struct Node;
    node->key = key;
    node->data = data;
    node->level  = level;
    node->next_nodes = new struct Node* [level+1];

    //往不同level链表里面插入node
    for (int i = 0; i <= level; ++i) {
        node->next_nodes[i] = update[i]->next_nodes[i];
        update[i]->next_nodes[i] = node;
    }

}

template <typename vtype>
void skipList<vtype>::deleteNode(int key) {
    //找前驱
    struct Node *update[Max_level];
    struct Node *cur = head;
    for(int i = Max_level -1;i>=0;i--){
        if(cur->next_nodes[i] == tail || cur->next_nodes[i]->key > key){
            update[i] = nullptr;
        }else {
            while(cur->next_nodes[i]!=tail && cur->next_nodes[i]->key < key){
                cur = cur->next_nodes[i];
            }
            if(cur->next_nodes[i]!=tail && cur->next_nodes[i]->key == key){
                update[i] = cur;
            }else{
                update[i] = nullptr;
            }
        }   
    }
    struct Node * temp = nullptr;
    //注意点：需要删除node 只有一个，这个node存在于不同level链表里面，不要多次释放，不同level的update的next_nodes指针指向的是同一个node
    temp = update[0]->next_nodes[0];
    for (int i = 0; i < Max_level; ++i) {
        if(update[i]!=nullptr){
            update[i]->next_nodes[i] = temp->next_nodes[i];
        }
    }
    delete []temp->next_nodes;
    delete temp;

}

template <typename vtype>
vtype* skipList<vtype>::getData(int key) {
    struct Node *cur = head;
    for(int i = Max_level -1;i>=0;i--){
        if(cur->next_nodes[i] == tail || cur->next_nodes[i]->key > key){
            continue;
        }else {
            while(cur->next_nodes[i]!=tail && cur->next_nodes[i]->key < key){
                cur = cur->next_nodes[i];
            }
            if(cur->next_nodes[i]!=tail && cur->next_nodes[i]->key == key){
                return &cur->next_nodes[i]->data;
            }   
        }   
    }

    return  nullptr;
}


int randomInt(int begin,int end){
    static uniform_int_distribution<unsigned> u(begin,end);
    static std::default_random_engine e;
    return u(e);

}

template <typename vtype>
int skipList<vtype>::RandomLevel() {
    int level = 0;
    int num = randomInt(1,10000);
    while(num%2!=0){
        ++level;
        num = randomInt(1,10000);
    }
    return level <= Max_level-1?level:Max_level-1;
}

int main(int argc, char *argv[])
{
    skipList<double> slist(3);
    slist.insertNode(1, 20);
    slist.insertNode(4, 15);
    slist.insertNode(2, 20);
    slist.insertNode(5, 20);
    slist.insertNode(3, 20);
    slist.insertNode(10, 20);
    slist.insertNode(9, 20);
    slist.insertNode(8, 20);
    slist.insertNode(7, 20);

    slist.displayList();

    slist.deleteNode(5);

    slist.displayList();

    cout << *slist.getData(4) << endl;
    return 0;
}
