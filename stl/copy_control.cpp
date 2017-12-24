#include <iostream>
#include <set>
#include <string>

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

class Folder{

};

class Message{
    friend class Folder;
    public:
        explicit Message(const string &s = string()):content(s){}
        Message(const Message &m);
        Message &operator= (const Message &m);
        void save(Folder&f);
        void remove(Folder&f);
    private:
        string content;
        set<Folder*> folders;
        void add_to_folders(const Message & m);
        void remove_from_folders();
};

int main(){
    HasPtr hp("raohui");
    hp.print();
    HasPtr hp1 = hp;
    hp.print();
    hp1.print();
    return 0;

}
