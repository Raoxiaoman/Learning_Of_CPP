#include <cstdint>
#include <vector>
#include <unordered_map>

using namespace std;
class lru_key{
    public:
        uint32_t blk;
        uint16_t page;
        lru_key(){
            this->blk = 0;
            this->page = 0;
        }
        // overload operator==
        bool operator==(const lru_key& key) const {
            return this->blk == key.blk && this->page == key.page;  
        }
};

namespace std {
    template <>
        struct hash<lru_key>
        {
            std::size_t operator()(const lru_key& k) const
            {
                using std::size_t;
                using std::hash;

                // Compute individual hash values for first,
                // second and third and combine them using XOR
                // and bit shifting:

                return ((hash<uint32_t>()(k.blk)
                            ^ (hash<uint16_t>()(k.page) << 1)) >> 1);
            }
        };
}


class lru_value{
    public:
        void* page;
        lru_value(){
            this->page = NULL;
        }
};


template <class K, class T>
struct Node{
    K key;
    T data;
    Node *prev, *next;
};

template <class K, class T>
class LRUCache{
    public:
        LRUCache(size_t size);
        ~LRUCache();

        void Put(K key, T data);
        T Get(K key);

    private:
        // 分离结点
        void detach(Node<K,T>* node){
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        // 将结点插入头部
        void attach(Node<K,T>* node){
            node->prev = head_;
            node->next = head_->next;
            head_->next = node;
            node->next->prev = node;
        }
    private:
        unordered_map<K, Node<K,T>*> hashmap_;
        vector<Node<K,T>* > free_entries_; // 存储可用结点的地址
        Node<K,T> *head_, *tail_;
        Node<K,T> *entries_; // 双向链表中的结点
};


template <class K, class T>
LRUCache<K,T>::LRUCache(size_t size){
    entries_ = new Node<K,T>[size];
    for(size_t i=0; i<size; ++i)// 存储可用结点的地址
        free_entries_.push_back(entries_+i);
    head_ = new Node<K,T>;
    tail_ = new Node<K,T>;
    head_->prev = NULL;
    head_->next = tail_;
    tail_->prev = head_;
    tail_->next = NULL;
}

template <class K, class T>
LRUCache<K,T>::~LRUCache(){
    delete head_;
    delete tail_;
    delete[] entries_;
}

template <class K, class T>
void LRUCache<K,T>::Put(K key, T data){
    Node<K,T> *node = hashmap_[key];
    if(node){ // node exists
        detach(node);
        node->data = data;
        attach(node);
    }
    else{
        if(free_entries_.empty()){// 可用结点为空，即cache已满
            node = tail_->prev;
            detach(node);
            hashmap_.erase(node->key);
        }
        else{
            node = free_entries_.back();
            free_entries_.pop_back();
        }
        node->key = key;
        node->data = data;
        hashmap_[key] = node;
        attach(node);
    }
}

template <class K, class T>
T LRUCache<K,T>::Get(K key){
    Node<K,T> *node = hashmap_[key];
    if(node){
        detach(node);
        attach(node);
        return node->data;
    }
    else{// 如果cache中没有，返回T的默认值。与hashmap行为一致
        return T();
    }
}

