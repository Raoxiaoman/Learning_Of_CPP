#include <random>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

void test_random(){
    std::default_random_engine e;
    for (int i = 0; i < 10; i++) {
        std::cout << e() << std::endl;
    }
    cout << "max:" <<  e.max() << " min:" << e.min() << endl;
    e.seed(time(0));
    for (int i = 0; i < 10; i++) {
        std::cout << e() << std::endl;
    }
    
}

void test_random_distributed(){
    uniform_int_distribution<unsigned> u(0,9);
    std::default_random_engine e;
    for (int i = 0; i < 10; i++) {
        std::cout << u(e) << std::endl;
    }
    uniform_real_distribution<double> r(0,1);
    for (int i = 0; i < 10; i++) {
        std::cout << r(e) << std::endl;
    }

}

void test_random_normal_distributed(){
    normal_distribution<> nd(4,1.5);
    std::default_random_engine e;
    vector<unsigned> vs(9);

    for(size_t i = 0 ;i < 200; i++){
        unsigned v = lround(nd(e));
        if(v < vs.size()){
            vs[v]++;
        }
    }

    for(size_t i = 0; i < vs.size();i++){
        cout << i << ": " <<  std::string(vs[i],'*') << endl;
    }
    
}

bool play(bool first){
    return !first;
}

void test_random_bernoulli_distributed(){
    string again;
    bernoulli_distribution b;
    std::default_random_engine e;

    do{
        bool first = b(e);
        cout  << (first?"We go first":"You go first")  << endl;

        cout << (play(first)?"sorry You lost":"You Win") << endl;


        cout << "try aggin? input yes or no" << endl;

    }while(cin >> again && again[0] == 'y');
    
}

int main(){
    test_random();
    test_random_distributed();
    test_random_normal_distributed();
    test_random_bernoulli_distributed();
    return 0;
}
