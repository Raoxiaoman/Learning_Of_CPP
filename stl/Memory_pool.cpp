#include <iostream>

template <typename T>
class Memory_pool{
public:
    // constructors, asssignment, destructor
    Memory_pool();
    Memory_pool(const Memory_pool&);
    Memory_pool& operator=(const Memory_pool&);
    ~Memory_pool();
    
private:
    static const int Align = 8;
    //最大分配的字节
    static const int MaxBytes = 128;
    //自由链表的个数
    static const int NumberOfFreeList = MaxBytes / Align;
    //每次增加内存节点的个数
    static const int NumberOfAddNoteEverytime = 20;


    //自由链表的节点
    union node{
        union node * next;
        char client[1];
    };

    //自由链表的数组
    static node* freeList[NumberOfFreeList];

    
    //返回的值是大于等于输入值且是Align大小的倍数
    static size_t ROUND_UP(size_t size){
        return ((size+Align-1) & ~(Align-1));

    }
    //返回可以容纳输入值的最小的自由链表的index

};
