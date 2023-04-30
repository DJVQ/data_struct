_Pragma("once")
#include "head.h"

//二叉树节点
template<typename T>
struct binary_node{
    T val;
    binary_node* left;
    binary_node* right;
    binary_node() : left(nullptr), right(nullptr) {};
    binary_node(T val_) : val(val_), left(nullptr), right(nullptr) {};
    binary_node(T val_, binary_node* left_, binary_node* right_) : val(val), left(left_), right(right_) {};
};

//二叉树
template<typename T>
class binary_tree{
    private:
        int count;
        void pre_order_traverse(binary_node<T>* node,void (*visit)(T));
        void mid_order_traverse(binary_node<T>* node,void (*visit)(T));
        void last_order_traverse(binary_node<T>* node,void (*visit)(T));
        void layer_order_traverse(void (*visit)(T));
    public:
        binary_node<T>* root;
        binary_tree() : root(nullptr), count(0) {};
        binary_tree(binary_node<T>*& root_) : root(root_), count(0) {};
        binary_tree(binary_node<T>*& root_, int count_) : root(root_), count(count_) {};
        bool empty_();
        void create_note_layer(auto it_b, auto it_e);
        void traverse(int key, void (*visit)(T));
};

//层序遍历创建节点
template<typename T>
void binary_tree<T>::create_note_layer(auto it_b, auto it_e) {
    if(it_b == it_e) return;
    queue<binary_node<T>*> nodes_;
    this->root = new binary_node<T>(*it_b++);
    ++this->count;
    nodes_.push(this->root);
    binary_node<T>* node_temp;
    while(it_b != it_e && !nodes_.empty()) {
        node_temp = nodes_.front();
        node_temp->left = new binary_node<T>(*it_b++);
        ++this->count;
        nodes_.pop();
        nodes_.push(node_temp->left);
        if(it_b == it_e) return;
        node_temp->right = new binary_node<T>(*it_b++);
        ++this->count;
        nodes_.push(node_temp->right);
    }
}

//节点访问模板函数
template <typename T>
void visit(T data) {
    cout << "node:\t";
}

//判断二叉树是否为空
template<typename T>
bool binary_tree<T>::empty_() {
    return this->root == nullptr;
}

//遍历二叉树
template<typename T>
void binary_tree<T>::traverse(int key, void (*visit)(T)) {
    cout<<endl;
    switch(key) {
        case 1:
            pre_order_traverse(this->root, visit);
            break;
        case 2:
            mid_order_traverse(this->root, visit);
            break;
        case 3:
            last_order_traverse(this->root, visit);
            break;
        default:
            layer_order_traverse(visit);
            break;
    }
}

//先序遍历
template<typename T>
void binary_tree<T>::pre_order_traverse(binary_node<T>* node,void (*visit)(T)) {
    if(node) {
        visit(node->val);
        pre_order_traverse(node->left, visit);
        pre_order_traverse(node->right, visit);
    }
}

//中序遍历
template<typename T>
void binary_tree<T>::mid_order_traverse(binary_node<T>* node,void (*visit)(T)) {
    if(node) {
        mid_order_traverse(node->left, visit);
        visit(node->val);
        mid_order_traverse(node->right, visit);
    }
}

//后序遍历
template<typename T>
void binary_tree<T>::last_order_traverse(binary_node<T>* node,void (*visit)(T)) {
    if(node) {
        last_order_traverse(node->left, visit);
        last_order_traverse(node->right, visit);
        visit(node->val);
    }
}

//层序遍历
template <typename T>
void binary_tree<T>::layer_order_traverse(void (* visit)(T)) {
    cout<<"total: "<<count<<endl;
    binary_node<T>* queue[this->count];
    binary_node<T>* tmp;
    int l = 0,r = 0;
    queue[r++] = this -> root;
    while (l < r) {
        tmp = queue[l++];
        visit(tmp -> val);
        if (tmp -> left != nullptr) {
            queue[r++] = tmp -> left;
        }
        if (tmp -> left != nullptr) {
            queue[r++] = tmp -> right;
        }
    }
}
