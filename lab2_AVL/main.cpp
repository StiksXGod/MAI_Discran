#include <iostream>
using ull = unsigned long long;

struct AVLNode{
    AVLNode* left;
    AVLNode* right;
    ull value;
    std::string key;
    short height;
    AVLNode(const std::string& key,ull value):key(std::move(key)),value(value),height(1),left(nullptr),right(nullptr){}
};


class AVLTree{
    public:
    AVLTree(){}
    ~AVLTree();
    bool find(ull value,const std::string& key);
    bool insert(const std::string& key, ull value);
    bool remove(const std::string& key);

    private:
    AVLNode* minValueNode(AVLNode* node);
    AVLNode* insert(AVLNode* node, const std::string& key,ull value);
    AVLNode* remove(AVLNode* node,const std::string& key);
    AVLNode* root;
    ull getBalance(AVLNode* node) const;
    ull getHeight(AVLNode* node) const;
    void clear(AVLNode* root);
    AVLNode* leftRotate(AVLNode* node);
    AVLNode* rightRotate(AVLNode* node);

};

AVLNode* AVLTree::rightRotate(AVLNode* node){
    AVLNode* newRoot = node->left;
    AVLNode* T2 = newRoot->right;

    newRoot -> right = node;
    node->left = T2;

    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right))+1;
    node->height = std::max(getHeight(node->left), getHeight(node->right))+1;

    return newRoot;
}
ull AVLTree::getHeight(AVLNode* node) const{
    return node ? node->height: 0;
}

ull AVLTree::getBalance(AVLNode* node) const{
    return node ? getHeight(node)-getHeight(node): 0;
}



AVLNode* AVLTree::leftRotate(AVLNode* node){
    AVLNode* newRoot = node->right;
    AVLNode* T2 = newRoot->left;

    newRoot -> left = node;
    node->right = T2;

    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right))+1;
    node->height = std::max(getHeight(node->left), getHeight(node->right))+1;

    return newRoot;
}

bool AVLTree::insert(const std::string& key,ull value){
    if (find(value,key)) return false;
    root = insert(root, key,value);
    return true;
}


AVLNode* AVLTree::remove(AVLNode* node,const std::string& key){
    if (!root) return root;

    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->value = temp->value;
            root->right = remove(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

AVLNode* AVLTree::insert(AVLNode* node, const std::string& key,ull value){
    if (!node)
    {
        return new AVLNode(key, value);
    }
    if (key<node->key)
    {
        node->left = insert(node->left, key,value);
    }else if (key>node->key)
    {
        node->right = insert(node->right, key,value);
    }else{
        return node;
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right))+1;

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;

}

AVLNode* minValueNode(AVLNode* node){
    AVLNode* cur = node;
    while(cur->left){
        cur = node->left;
    }
    return cur;
}

bool AVLTree::remove(const std::string& key){
    if (!find(2, key))
    {
        return false;
    }
    root = remove(root,key);
    return true;
}

void AVLTree::clear(AVLNode* root){
    if (root)
    {
        clear(root->left);
        clear(root->right);
        delete root;
    } 
}

AVLTree::~AVLTree(){
    clear(root);
}

bool AVLTree::find(ull value,const std::string& key){
    AVLNode* cur = root;
    while(cur){
        if (cur->key<key)
        {
            cur = cur->right;
        } else if(cur->key>=key){
            cur = cur->left;
        }else{
            value = cur->value;
            return true;
        }
    }
    return false;
}





int main(){


    return 0;
}