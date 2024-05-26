#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

const int up_limit = 1000000;
const int lw_limit = 0;


struct Node final{ 
    int priority;
    std::string key;
    std::string value;
    Node* left;
    Node* right;

    Node(const std::string& key, const std::string& value):key(key),priority(lw_limit+ rand()%up_limit),value(value),left(nullptr),right(nullptr){}
};

Node* merge(Node* tree_1, Node* tree_2){
    if(tree_1 == nullptr) return tree_2 ;
    if(tree_2 == nullptr) return tree_1 ;
    if(tree_1->priority > tree_2->priority){
        tree_1->right = merge(tree_1->right, tree_2);
        return tree_1;
    }else{
        tree_2->left = merge(tree_1, tree_2->left);
        return tree_2;
    }
}

void split(Node* root, const std::string& key, Node*& left, Node*& right){
    if (root==nullptr){
        left=right=nullptr;
        return;
    }
    if(root->key < key){
        split(root->right,key,root->right,right);
        left = root;

    }else{
        split(root->left,key,left,root->left);
        right = root;
    }
}

std::string to_lower(const std::string& str) {
    std::string res = str;
    std::transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

Node* insert(Node* root, const std::string& key,const std::string& value){
    Node* insertNode = new Node(key, value);
    if(root==nullptr) return insertNode;
    Node* left = nullptr;
    Node* right = nullptr;

    split(root, key, left, right);
    Node* tempNode = merge(left, insertNode);

    return merge(tempNode, right);
}

Node* search(Node* root, const std::string& key){
    if(root==nullptr) return nullptr;
    if(root->key==key) return root;
    if(root->key<key){
        return search(root->right,key);
    }
    return search(root->left,key);
}

void printDecartTree(Node* root, int level = 0, char direction = '-') {
    if (root != nullptr) {
        printDecartTree(root->right, level + 1, 'R');
        for (int i = 0; i < level; ++i) {
            std::cout << "   ";
        }
        std::cout << direction << " (" << root->key << "," << root->priority << ")" << std::endl;
        printDecartTree(root->left, level + 1, 'L');
    }
}


Node* erase(Node* root, const std::string& key){
    if(root==nullptr) return nullptr;
    if (root->key==key)
    {
        Node* temp = merge(root->left,root->right);
        delete root;
        return temp;
    }else if(key < root->key){
        root->left = erase(root->left,key);
    }else{
        root->right = erase(root->right,key);
    }
    return root;
    
}

class DecartDictionary final{
    private:
    Node* root;

    void destroyer(Node* root){
        if (root!=nullptr)
        {
            destroyer(root->left);
            destroyer(root->right);
            delete root;
        }
        
    }
    public:

    DecartDictionary():root(nullptr){
        std::srand(std::time(0));
    }

    ~DecartDictionary(){
        destroyer(root);
    }

    void find(const std::string& key){
        std::string keyLow = to_lower(key);
        // std::cout << keyLow << std::endl;
        Node* searchNode = search(root, keyLow);
        if(searchNode==nullptr){
            std::cout << "NoSuchWord"<< std::endl;
            return ;
        }
        std::cout << "OK: " << searchNode->value << std::endl; 
    }

    void add(const std::string& key,const std::string& value){
        std::string keyLow = to_lower(key);
        Node* searchNode = search(root, keyLow);
        if(searchNode!=nullptr){
            std::cout << "Exist"<< std::endl;
            return ;
        }
        root = insert(root, keyLow, value);
        std::cout << "OK" << std::endl;
        // printDecartTree(root);
    }
    void remove(const std::string& key){
        std::string keyLow = to_lower(key);
        Node* searchNode = search(root, keyLow);
        if(searchNode==nullptr){
            std::cout << "NoSuchWord"<< std::endl;
            return ;
        }
        root = erase(root,keyLow);
        std::cout << "OK" << std::endl;
    }
    void printTree(){
        printDecartTree(root);
    }
};

int main(){
    std::string enter;
    DecartDictionary tree;
    while(std::getline(std::cin,enter)){
        if (enter[0]=='+')
        {
            auto it_end  = std::find(enter.begin()+2,enter.end()-2, ' ');
            std::string key = enter.substr(2, std::distance(enter.begin()+2,it_end));
            std::string value = enter.substr(key.size()+3, enter.size()-key.size());
            // std::cout << key << "2" << std::endl;
            // std::cout << value << std::endl;
            tree.add(key,value);
            continue;

        }else if(enter[0] == '-'){
            std::string key = enter.substr(2, enter.size()-2);
            tree.remove(key);
            continue;
        }else if(enter=="print"){
            tree.printTree();
            continue;
        }
        tree.find(enter);
        
    }


    return 0;
}