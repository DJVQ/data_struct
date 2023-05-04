_Pragma("once")
#include "head.h"

//二叉树节点
template<typename T>
struct binary_node{
    T val;
    bool is_red;
    binary_node* parent;
    binary_node* left;
    binary_node* right;
    binary_node() : 
                is_red(true), left(nullptr), right(nullptr), parent(nullptr) {};
    binary_node(T val_) : 
                val(val_), is_red(true), left(nullptr), right(nullptr), parent(nullptr) {};
    binary_node(T val_, binary_node* left_, binary_node* right_) : 
                val(val_), is_red(true), left(left_), right(right_), parent(nullptr) {};
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
        void insert_node_BST(binary_node<T>* &parent, binary_node<T>* &node, T val_, bool (* cmp)(T, T));
        binary_node<T>* left_rotate(binary_node<T>* &node);
        binary_node<T>* right_rotate(binary_node<T>* &node);
        binary_node<T>* left_right_rotate(binary_node<T>* node);
        binary_node<T>* right_left_rotate(binary_node<T>* node);
        void rebalance(binary_node<T>* &node);
    public:
        binary_node<T>* root;
        binary_tree() : root(nullptr), count(0) {};
        binary_tree(binary_node<T>*& root_) : root(root_), count(0) {};
        binary_tree(binary_node<T>*& root_, int count_) : root(root_), count(count_) {};
        bool empty_();
        void create_node_layer(auto it_b, auto it_e);
        void traverse(int key, void (*visit_)(T));
        void create_BST(vector<T> &elements_, bool (*cmp_)(T, T));
        void trans_BST_to_AVL(binary_node<T>* &node);
        void trans_BST_to_RBT(binary_node<T>* &node);
        void trans_AVL_to_RBT(binary_node<T>* &node);
};

//层序遍历创建节点
template<typename T>
void binary_tree<T>::create_node_layer(auto it_b, auto it_e) {
    if(it_b == it_e) return;
    queue<binary_node<T>*> nodes_;
    this->root = new binary_node<T>(*it_b++);
    ++this->count;
    nodes_.push(this->root);
    binary_node<T>* node_temp;
    while(it_b != it_e && !nodes_.empty()) {
        node_temp = nodes_.front();
        node_temp->left = new binary_node<T>(*it_b++);
        node_temp->left->parent = node_temp;
        ++this->count;
        nodes_.pop();
        nodes_.push(node_temp->left);
        if(it_b == it_e) return;
        node_temp->right = new binary_node<T>(*it_b++);
        node_temp->right->parent = node_temp;
        ++this->count;
        nodes_.push(node_temp->right);
    }
}

//节点访问模板函数
template <typename T>
void visit(T data) {
    cout << "node:\t";
}

//节点访问模板函数
template <typename T>
bool cmp_(T data_1, T data_2) {
    return data_1 < data_2;
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

// //左旋
// template<typename T>
// binary_node<T>* binary_tree<T>::left_rotate(binary_node<T>* &node){
//     binary_node<T>* node_ = node->right;
//     if(!node_) return node_;
//     node->right = node_->left;
//     if (node_->left != nullptr) node_->left->parent = node;
//     node_->parent = node->parent;
//     if (node->parent == nullptr) {
//         root = node_;
//     } else if (node == node->parent->left) {
//         node->parent->left = node_;
//     } else {
//         node->parent->right = node_;
//     }
//     node_->left = node;
//     node->parent = node_;
//     swap(node->is_red, node_->is_red);
//     return node_;
// }

// //右旋
// template<typename T>
// binary_node<T>* binary_tree<T>::right_rotate(binary_node<T>* &node){
//     binary_node<T>* node_ = node->left;
//     if(!node_) return node_;
//     node->left = node_->right;
//     if (node_->right != nullptr) node_->right->parent = node;
//     node_->parent = node->parent;
//     if (node->parent == nullptr) {
//         root = node_;
//     } else if (node == node->parent->right) {
//         node->parent->right = node_;
//     } else {
//         node->parent->left = node_;
//     }
//     node_->right = node;
//     node->parent = node_;
//     swap(node->is_red, node_->is_red);
//     return node_;
// }

//左旋
template<typename T>
void change_parent(binary_node<T>* &node, binary_node<T>* &node_){
    if(node->parent)
        if(node->parent->left == node)
            node->parent->left = node_;
        else
            node->parent->right = node_;
}

//左旋
template<typename T>
binary_node<T>* binary_tree<T>::left_rotate(binary_node<T>* &node){
    binary_node<T>* node_ = node->right;
    node->right = node_->left;
    node_->left = node;
    change_parent(node, node_);
    return node_;
}
//右旋
template<typename T>
binary_node<T>* binary_tree<T>::right_rotate(binary_node<T>* &node){
    binary_node<T>* node_ = node->left;
    node->left = node_->right;
    node_->right = node;
    change_parent(node, node_);
    return node_;
}

//左右旋
template<typename T>
binary_node<T>* binary_tree<T>::left_right_rotate(binary_node<T>* node){
    node->left = right_rotate(node->left);
    return left_rotate(node);
}
//右左旋
template<typename T>
binary_node<T>* binary_tree<T>::right_left_rotate(binary_node<T>* node){
    node->left = left_rotate(node->left);
    return right_rotate(node);
}

//向二叉排序树插入一个节点
template <typename T>
void binary_tree<T>::insert_node_BST(binary_node<T>* &parent_, binary_node<T>* &node, T val_, bool (* cmp)(T, T)) {
    if (node) {
        if(cmp(val_, node->val))
            insert_node_BST(node, node->left, val_, cmp);
        else
            insert_node_BST(node, node->right, val_, cmp);
    } else {
        node = new binary_node<T>(val_); 
        node->parent = parent_;
        ++(this->count);
    }
}

//转化为二叉排序树
template <typename T>
void binary_tree<T>::create_BST(vector<T> &elements_, bool (* cmp)(T, T)) {
    for(int i = 0; i < elements_.size(); ++i) 
        insert_node_BST(this->root, this->root, elements_[i], cmp);
}

//以当前节点为根节点，获取高度
template<typename T>
int get_height(binary_node<T>* node) {
    if(node == nullptr) return -1;
    return max(get_height(node->left), get_height(node->right)) + 1;
}

//计算节点左右子树的高度差
template<typename T>
int balance_factor(binary_node<T>* node) {
    return get_height(node->left) - get_height(node->right);
}

//通过左旋或者右旋使二叉树平衡
template<typename T>
void binary_tree<T>::rebalance(binary_node<T>* &node){
    int bf = get_height(node->left) - get_height(node->right);
    if(bf > 1) {
        if(balance_factor(node->left) < 0) 
            left_rotate(node->left);
        right_rotate(node);
    } else if(bf < -1) {
        if(balance_factor(node->right) > 0)
            right_rotate(node->right);
        left_rotate(node);
    }
}

//将二叉排序树转化为二叉平衡树
template<typename T>
void binary_tree<T>::trans_BST_to_AVL(binary_node<T>* &node){
    if(node == nullptr) return;
    trans_BST_to_AVL(node->left);
    trans_BST_to_AVL(node->right);
    rebalance(node);
}

//将二叉排序树转化为红黑树
template<typename T>
void binary_tree<T>::trans_BST_to_RBT(binary_node<T>* &node) {
    trans_BST_to_AVL(node);
    trans_AVL_to_RBT(root);
    root->is_red = true;
}

template<typename T>
void binary_tree<T>::trans_AVL_to_RBT(binary_node<T>* &node){
    if (node == nullptr) return;
    root->parent = nullptr;
    binary_node<T>* curr = node;
    while (curr->parent != nullptr) curr = curr->parent;
    curr->is_red = false;
    while (curr != nullptr) {
        if (curr->left != nullptr && curr->left->is_red && curr->right != nullptr && curr->right->is_red) {
            curr->is_red = true;
            curr->left->is_red = false;
            curr->right->is_red = false;
        } else if (curr->left != nullptr && curr->left->is_red && curr->left->left != nullptr && curr->left->left->is_red) {
            curr = right_rotate(curr);
            curr->is_red = false;
            curr->right->is_red = true;
        } else if (curr->left != nullptr && curr->left->is_red && curr->left->right != nullptr && curr->left->right->is_red) {
            curr = right_left_rotate(curr);
            curr->is_red = false;
            curr->right->is_red = true;
        } else if (curr->right != nullptr && curr->right->is_red && curr->right->left != nullptr && curr->right->left->is_red) {
            curr = left_right_rotate(curr);
            curr->is_red = false;
            curr->left->is_red = true;
        } else if (curr->right != nullptr && curr->right->is_red && curr->right->right != nullptr && curr->right->right->is_red) {
            curr = left_rotate(curr);
            curr->is_red = false;
            curr->left->is_red = true;
        } else {
            curr = curr->parent;
        }
    }
}
