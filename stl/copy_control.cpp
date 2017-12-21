#include <iostream>
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


int main(){
    HasPtr hp("raohui");
    hp.print();
    HasPtr hp1 = hp;
    hp.print();
    hp1.print();
    return 0;

}
