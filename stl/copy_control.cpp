#include <iostream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

class HasPtr{
    public:
        HasPtr(const string &s = string()):i(0),ps(new string(s)),use(new size_t(1)){};
        HasPtr(const HasPtr &rhp):i(rhp.i),ps(rhp.ps),use(rhp.use){++*use;};
        ~HasPtr(){
            if(--*use == 0){
                delete ps;
                delete use;
            }
        }

        HasPtr & operator=(const HasPtr &);
        void print(){
            cout << ps << endl;
            cout << *ps  << ":" << *use << endl;
        }
        
    private:
        int i;
        string *ps;
        size_t *use;
};

HasPtr & HasPtr::operator=(const HasPtr &rhp){
    ++*rhp.use;
    if(--*use == 0){
        delete ps;
        delete use;
    }

    i = rhp.i;
    ps = rhp.ps;
    use = rhp.use;
    return *this;
}

class Message;
class Folder{
    public:
        void addMsg(Message *m);
        void remMeg(Message *m);
        virtual ~Folder();
    private:
        set<Message*> messages;
        void remove_all_message();

};

void Folder::addMsg(Message *m){
    messages.insert(m);
}

void Folder::remMeg(Message *m){
    messages.erase(m);
}

void Folder::remove_all_message(){
    for(auto m:messages){
        messages.erase(m);
    }
}

Folder::~Folder(){
    //必须释放掉存有的message指针，不然可能存储空的message指针
    remove_all_message();
    cout << "~Folder" << endl;
}

class Message{
    friend class Folder;
    friend void swap(Message &lm,Message &rm);
    public:
    explicit Message(const string &s = string()):content(s){}
    Message(const Message &m);
    Message &operator= (const Message &m);
    void save(Folder&f);
    void remove(Folder&f);
    virtual ~Message();
    void print(){
        cout << "content:" << content << endl;
        for_each(folders.cbegin(),folders.cend(),[](Folder *f){cout << f << endl;});
    }
    private:
    string content;
    set<Folder*> folders;
    void add_to_folders(const Message & m);
    void remove_from_folders();
};

void swap(Message &lm,Message &rm){
    using std::swap;

    for(auto f:lm.folders){
        f->remMeg(&lm);
    }
    for(auto f:rm.folders){
        f->remMeg(&rm);
    }
    swap(lm.content,rm.content);
    swap(lm.folders,rm.folders);

    for(auto f:lm.folders){
        f->addMsg(&lm);
    }
    for(auto f:rm.folders){
        f->remMeg(&rm);
    }


}
void Message::add_to_folders(const Message &m){
    for(auto f:m.folders){
        f->addMsg(this);
    }
}

void Message::remove_from_folders(){
    for(auto f: folders){
        f->remMeg(this);
    }
}

Message::Message(const Message &m):content(m.content),folders(m.folders){
    add_to_folders(*this);
}

Message::~Message(){
    cout << "~Message" << endl;
    remove_from_folders();
}

Message & Message::operator=(const Message &m){
    remove_from_folders();
    content = m.content;
    folders = m.folders;
    add_to_folders(*this);
    return *this;

}


void Message::save(Folder &f){
    folders.insert(&f);
    f.addMsg(this);

}

void Message::remove(Folder &f){
    folders.erase(&f);
    f.remMeg(this);
}

int main(){
    //HasPtr hp("raohui");
    //hp.print();
    //HasPtr hp1 = hp;
    //hp.print();
    //hp1.print();

    Message test("raohui");
    Folder f;
    test.save(f);
    test.print();
    Message test1 = test;
    test1.print();

    return 0;

}
