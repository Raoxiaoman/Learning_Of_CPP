#include <iostream>
#include <functional>
#include <thread>

class test
{
    public:
        test(int a):tt(std::bind(&test::print,this)),aa(a){
            tt.join();
        };
        test(const test&);
        void print(void){
            std::cout << "test:" << aa  << std::endl;
        }
        virtual ~test(){};
    private:
        std::thread tt;
        int aa;
};

test::test(const test& test){
    aa = test.aa;
}

void testfunction(int a,int b){

    std::cout << "function:" <<  a << b << std::endl;
}

void threadRunMemberFunction(void){
    test cf(10);
    std::thread *t = new std::thread(&test::print,cf);
    t->join();
    delete t;
}


void threadRunFunction(){
    std::thread *t = new std::thread(testfunction,19,29);
    t->detach();
    delete t;
}

int main()
{
    threadRunFunction();
    test cf(500);
    threadRunMemberFunction();
    std::cout << "main" << std::endl;
    return 0;
}

