#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Memory_pool{

public:
    typedef T            value_type;
    typedef T*            pointer;
    typedef const T*    const_pointer;
    typedef T&            reference;
    typedef const T&    const_reference;
    typedef size_t        size_type;
    //typedef ptrdiff_t    difference_type;
    //内存池对外暴露申请内存的接口
    static T *allocate();
    static T * allocate(size_t n);
    // 内存释放
    static void deallocate(T* ptr);
    static void deallocate(T* ptr,size_t size);
    //内存对象构造
    static void construct(T *ptr);
    static void construct(T *ptr,const T& value);
    //内存对象销毁
    static void destroy(T *ptr);

private:

    //内存池的大小
    static size_t pool_size;
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

    //分配内存
    static void * _allocate(size_t size);
    //填充自由内存链表
    static void *rfill(size_t size);
    //真正向内存池申请内存
    static char *blockAlloc(size_t size,size_t & num);
};

template <typename T>
size_t  Memory_pool<T>::pool_size = 0;

template <typename T>
char*  Memory_pool<T>::startOfPool = nullptr;

template <typename T>
char*  Memory_pool<T>::endOfPool = nullptr;

template <typename T>
typename Memory_pool<T>::node* Memory_pool<T>::freeList[NumberOfFreeList]  = {nullptr};

template <typename T>
void Memory_pool<T>::construct(T*ptr){
    new (ptr) T;
}

template <typename T>
void Memory_pool<T>::construct(T*ptr,const T&value){
    new (ptr) T(value);
}

template <typename T>
void Memory_pool<T>::destroy(T*ptr){
    ptr->~T();
}

template <typename T>
void Memory_pool<T>::deallocate(T *ptr){
    Memory_pool<T>::deallocate(ptr,sizeof(ptr));
}

template <typename T>
void Memory_pool<T>::deallocate(T *ptr,size_t size){
    if(size > 128){
        free(ptr);
    }else{
        node** suitList  = freeList + FreeListIndex(size);
        reinterpret_cast<node*>(ptr)->next = *suitList;
        *suitList = reinterpret_cast<node*>(ptr);
    }

}

template <typename T>
T* Memory_pool<T>::allocate(){
    return  static_cast<T*>(Memory_pool<T>::_allocate(sizeof(T)));
}
template <typename T>
T* Memory_pool<T>::allocate(size_t n){
    return  static_cast<T*>(Memory_pool<T>::_allocate(sizeof(T)*n));
}

template <typename T>
void * Memory_pool<T>::_allocate(size_t size){
    if(size > 128){
        return static_cast<T*>(malloc(size));
    }
    //获取对应的自由链表
    size_t index = FreeListIndex(size);
    node * psuitList =  freeList[index];
    //不为空链表，返回头节点
    if(psuitList){
        freeList[index] = psuitList->next;
        cout << "直接从自由链表中获取" << endl;
        return psuitList;

    }else{
        //否则填充自由链表
        cout << "需要填充自由链表" << endl;
        return reinterpret_cast<void*>(rfill(size));
    }
}

template <typename T>
void *Memory_pool<T>::rfill(size_t size){
    size_t num =  NumberOfAddNoteEverytime;
    //向内存池申请内存块
    char *block =  blockAlloc(size,num);
    node **currentList = nullptr;
    node *currentNode = nullptr;
    node *nextNode = nullptr;

    
    if(num == 1){
        return block;
    }
    //申请完后如果有多出来的内存，就挂到自由链表上
    else{
        currentList = freeList + FreeListIndex(size);
        *currentList = nextNode =  reinterpret_cast<node *>(block+size);
        for(int i=1;;i++){
            currentNode = nextNode;
            currentNode->next =  reinterpret_cast<node *>(nextNode+size);
            nextNode = currentNode->next;
            if(num-1 == i ){
                return block;
            }
        }
    }
}

template <typename T>
char *Memory_pool<T>::blockAlloc(size_t size,size_t &num){
    char *re = 0;
    size_t bytesNeed = size * num;
    size_t bytesLeft = endOfPool - startOfPool;

    if(bytesLeft >= bytesNeed){
        re = startOfPool;
        startOfPool = startOfPool+ bytesNeed;
        return re;
    }else if(bytesLeft > size){
        re = startOfPool;
        num = bytesLeft / size;
        startOfPool = startOfPool + num * size;
        return re;

    }else{
        size_t bytesToGet = bytesNeed + ROUND_UP(pool_size >> 4);
        if(bytesLeft > 0){
            node **suitList = freeList+ FreeListIndex(bytesLeft);
            reinterpret_cast<node *>(startOfPool)->next = *suitList;
            *suitList = reinterpret_cast<node*>(startOfPool);
        }
        startOfPool = (char*)malloc(bytesToGet);
        if(!startOfPool){
            node **currentList = nullptr;
            node *currentNode = nullptr;
            for(int i=size;i<=MaxBytes;i+=Align){
                currentList =  freeList + FreeListIndex(i);
                currentNode = *currentList;
                if(currentNode){
                    *currentList = currentNode->next;
                    startOfPool = reinterpret_cast<char*>(currentNode);
                    endOfPool = reinterpret_cast<char*>(currentNode+i);
                    return blockAlloc(size,num);
                }

            }

            exit(3);
        }
        else{
            pool_size += bytesToGet;
            endOfPool = startOfPool + bytesToGet;
            return blockAlloc(size,num);

        }

    }

}

int main(){

    typedef Memory_pool<int> int_pool;
    int *p = int_pool::allocate();
    int_pool::construct(p,10);
    std::cout << *p << std::endl;
    int_pool::destroy(p);
    int_pool::deallocate(p);

    int *p2 = int_pool::allocate();
    int_pool::construct(p2,30);
    std::cout << *p << std::endl;
    int_pool::destroy(p2);
    int_pool::deallocate(p2);


    typedef Memory_pool<string> string_pool;
    string *pp = string_pool::allocate();
    string_pool::construct(pp,"raohui");
    std::cout << *pp << std::endl;
    string_pool::destroy(pp);
    string_pool::deallocate(pp);
    return 0;
}




