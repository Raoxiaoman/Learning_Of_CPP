#include <string>
#include <iostream>
#include "LRUCache.h"

using namespace std;
int main(){
    LRUCache<int, string> lru_cache(100);
    lru_cache.Put(1, "one");
    cout<<lru_cache.Get(1)<<endl;
    if(lru_cache.Get(2) == "")
        lru_cache.Put(2, "two");
    cout<<lru_cache.Get(2) <<endl;
    return 0;
}
