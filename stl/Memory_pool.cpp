#include <iostream>

template <typename T>
class Memory_pool{
public:
    // constructors, asssignment, destructor
    Memory_pool();
    Memory_pool(const Memory_pool&);
    Memory_pool& operator=(const Memory_pool&);
    ~Memory_pool();
    //内存池对外暴露申请内存的接口
    static void *allocate();
    static void *allocate(size_t size);
    // 内存释放
    static void deallocate(void* ptr);
    static void deallocate(void* ptr,size_t size);
    //内存对象构造
    static void construct(T *ptr);
    static void construct(T *ptr,const T& value);
    //内存对象销毁
    static void destroy(T *ptr);
    static void destroy(T *ptr,const T& value);
    
private:
    static const int Align = 8;
    //最大分配的字节
    static const int MaxBytes = 128;
    //自由链表的个数
    static const int NumberOfFreeList = MaxBytes / Align;
    //每次增加内存节点的个数
    static const int NumberOfAddNoteEverytime = 20;
    //内存池分配空间的起点
    static char * startOfPool;
    //内存池分配空间的终点
    static char * endOfPool;

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
    static size_t FreeListIndex(size_t size){
        return (size+Align-1) / Align-1;
    }

    //填充自由内存链表
    void *rfill(size_t size);
    //真正向内存池申请内存
    char *blockAlloc(size_t size,size_t & num);
};
