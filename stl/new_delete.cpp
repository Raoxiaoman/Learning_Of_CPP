#include <cstdlib>
#include <typeinfo>
#include <iostream>

class new_delete{
    int i;
    double j;
    public:
    void * operator new(size_t size){
        if(void *mem = malloc(size)){
            std::cout << "new" << std::endl;
            return mem;
        }
        else{
            throw  std::bad_alloc();
        }
    }

    void operator delete(void * mem) noexcept{
        std::cout << "delete" << std::endl;
        free(mem);
    }
};


int main(){
    new_delete * nd = new new_delete();
    delete  nd;
    return 0;
}
