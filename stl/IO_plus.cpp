#include <fstream>
#include <string>
#include <iostream>

using namespace std;
int test_seek_tell(){
    fstream inOut("./input/copyOut",fstream::ate | fstream::in | fstream::out);
    if(!inOut){
        cerr << "Uable to open file" << endl;
        return EXIT_FAILURE;
    }

    auto end_mark = inOut.tellg();
    inOut.seekg(0,fstream::beg);
    size_t cnt  = 0;
    string line; 

    while(inOut && inOut.tellg()!= end_mark && getline(inOut,line)){
        cnt += line.size() + 1;
        auto mark = inOut.tellg();
        inOut.seekg(0,fstream::end);
        inOut << cnt;
        if(mark !=  end_mark){
            inOut << " ";
        }
        
        inOut.seekg(mark);
    }

    inOut.seekg(0,fstream::end);
    inOut << "\n";

    return 0;
}


int main(){
    test_seek_tell();
    return 0;
}
