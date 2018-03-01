#include <iostream>

using namespace std;
template <typename T>
class Binary_search_Tree{
public:
    // constructors, destructor
    Binary_search_Tree();
    ~Binary_search_Tree();
    //插入节点，按二叉查找树的规则插入!!!
    void insert_node(T data);
    //前序遍历
    void PreOrderTravel();
    //中序遍历
    void InOrderTravel();
    //后续遍历
    void PostOrderTravel();
    
    //二叉树的节点数
    size_t count(){
        return _count(root);
    }
    //二叉树叶子节点数
    size_t leaf_count(){
        return _leaf_count(root);
    }
    //二叉树度为一的节点数
    size_t degree1_node(){
        return _degree1_node(root);
    }
    //二叉树高度
    size_t height(){
        return _height(root);
    }

private:

    typedef struct  BiTPnode{
        T data;
        BiTPnode* right;
        BiTPnode* left;
    }BiTPnode;

    BiTPnode * root;
    void _PreOrderTravel(BiTPnode *travel);
    void _InOrderTravel(BiTPnode *travel);
    void _PostOrderTravel(BiTPnode *travel);
    void _deleteBinary_search_Tree(BiTPnode *travel);
    size_t _count(BiTPnode *travel);
    size_t _leaf_count(BiTPnode *travel);
    size_t _degree1_node(BiTPnode *travel);
    size_t _height(BiTPnode *travel);
    BiTPnode * construct_node(T data);
};

template <typename T>
size_t Binary_search_Tree<T>::_count(BiTPnode *travel){
    if(travel == nullptr){
        return 0;
    }else{
        return _count(travel->left)+_count(travel->right)+1;
    }
}

template <typename T>
size_t Binary_search_Tree<T>::_leaf_count(BiTPnode *travel){
    if(travel==nullptr){
        return 0;
    }
    else {
        if(travel->left ==nullptr && travel->right ==nullptr){
            return 1;
        }else{
            return (_leaf_count(travel->left)+_leaf_count(travel->right));
        }

    }
}

template <typename T>
size_t Binary_search_Tree<T>::_degree1_node(BiTPnode *travel){
    if(travel==nullptr){
        return 0;

    }else{
        if(travel->left !=nullptr && travel->right !=nullptr){
            return _degree1_node(travel->left)+_degree1_node(travel->right);
        }else if(travel->left!=nullptr && travel->right==nullptr){
            return _degree1_node(travel->left)+1;
        }else if(travel->left==nullptr && travel->right!=nullptr){
            return _degree1_node(travel->right)+1;
        }else{
            return 0;
        }

    }

}

template <typename T>
size_t  Binary_search_Tree<T>::_height(BiTPnode *travel){
    size_t i,j;
    if(travel==nullptr){
        return 0;
    }
    if(travel->left){
        i = _height(travel->left);
    }else{
        i=0;
    }
    if(travel->right){
        j = _height(travel->right);
    }else{
        j=0;
    }
    return i>j?i+1:j+1;
}

template <typename T>
Binary_search_Tree<T>::~Binary_search_Tree(){
    _deleteBinary_search_Tree(root);
}
template <typename T>
//删除整棵树，需要释放所有开辟的内存
void Binary_search_Tree<T>::_deleteBinary_search_Tree(BiTPnode *travel){
    BiTPnode *node = travel;
    if(node){
        if(node->left !=nullptr){
            _deleteBinary_search_Tree(node->left);
        }
        if(node->right !=nullptr){
            _deleteBinary_search_Tree(node->right);
        }
        delete travel;
        travel = nullptr;
    }
}

template <typename T>
Binary_search_Tree<T>::Binary_search_Tree(){
    root = nullptr;
}


template <typename T>
void Binary_search_Tree<T>::insert_node(T data){
    BiTPnode *newnode = construct_node(data);
    if(root == nullptr){
        root = newnode;
    }else{
        BiTPnode *back = nullptr;
        BiTPnode *current = root;

        while(current != nullptr){
            back = current;
            if(current->data > data){
                current = current->left;
            }else if(current->data < data){
                current = current->right;
            }else{
                break;
            }
        }

        if(back->data > data){
            back->left = newnode;
        }else if(back->data < data){
            back->right = newnode;
        }// back->data == data nothing to do

    }
}

template <typename T>
typename Binary_search_Tree<T>::BiTPnode * Binary_search_Tree<T>::construct_node(T data){
    BiTPnode *node = new BiTPnode();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;

}

template <typename T>
void Binary_search_Tree<T>::PreOrderTravel(){
    _PreOrderTravel(root);
}

template <typename T>
void Binary_search_Tree<T>::_PreOrderTravel(BiTPnode *travel){
    if(travel != nullptr){
        cout << travel->data << endl;
        _PreOrderTravel(travel->left);
        _PreOrderTravel(travel->right);
    }

}
template <typename T>
void Binary_search_Tree<T>::InOrderTravel(){
    _InOrderTravel(root);
}

template <typename T>
void Binary_search_Tree<T>::_InOrderTravel(BiTPnode *travel){
    if(travel != nullptr){
        _InOrderTravel(travel->left);
        cout << travel->data << endl;
        _InOrderTravel(travel->right);
    }

}


int main()
{
    Binary_search_Tree<int> bt;
    bt.insert_node(4);
    bt.insert_node(5);
    bt.insert_node(6);
    bt.insert_node(6);
    bt.insert_node(1);
    bt.insert_node(2);
    bt.insert_node(3);
    bt.PreOrderTravel();
    cout << "----------------" << endl;
    bt.InOrderTravel();
    cout << "----------------" << endl;
    cout << bt.count() <<endl;
    cout << "----------------" << endl;
    cout << bt.leaf_count() <<endl;
    cout << "----------------" << endl;
    cout << bt.height() <<endl;
    cout << "----------------" << endl;
    cout << bt.degree1_node() <<endl;
    return 0;
}
