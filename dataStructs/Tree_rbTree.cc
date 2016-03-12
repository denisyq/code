#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
#include <memory.h>
using namespace std;

const int RED = 1;
const int BLACK = 2;

typedef struct node{
    int key;
    int color;
    struct node *left;
    struct node *right;
    struct node *parent;
}Node;

class RBTree{
    public:
        RBTree();
        ~RBTree();
        void inOrder(void);
        void print(void);
        void insert(int key);
    private:
        Node* _root;
        void _print(Node* node);
        void _insert(Node* node, Node* parent, int key);
        void _makeEmpty(Node* node);
        void _inOrder(Node* node);
        void _rebalance(Node* node);
        void _leftRotate(Node* node);
        void _rightRotate(Node* node);
        //delete has 4 modes, did not write down
};
RBTree::RBTree(){
    _root = NULL;
}
RBTree::~RBTree(){
    _makeEmpty(_root);
}
void RBTree::_inOrder(Node* root){
    if(root != NULL){
        _inOrder(root->left);
        cout<<" "<<root<<"-"<<root->key<<endl;
        _inOrder(root->right);
    }
}
void RBTree::inOrder(void){
    //cout<<"InOrder+++++++++++++"<<endl;
    _inOrder(_root);
}
void RBTree::_print(Node* node){
    queue<Node*> iq;
    if(node != NULL) iq.push(node);
    while(!iq.empty()){
        Node* data = iq.front();
        cout<<data->color<<"  " <<data->key<<endl;
        iq.pop();
        if(data->left != NULL)
            iq.push(data->left);
        if(data->right != NULL)
            iq.push(data->right);
    }

}
void RBTree::print(void){
    //cout<<"per depth+++++++++++++"<<endl;
    _print(_root);
}
void RBTree::_makeEmpty(Node* root){
    if(root == NULL) return;
    else{
        _makeEmpty(root->left);
        _makeEmpty(root->right);
    }
    delete root;
}
void RBTree::insert(int key){
    _insert(_root,NULL,key);
}

//similar to STL
void RBTree::_leftRotate(Node* x){
    Node* y = x->right;
    x->right = y->left;
    if(y->left != NULL)
        y->left->parent = x;
    if(x == _root) _root=y;
    else if( x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}
void RBTree::_rightRotate(Node* x){
    Node* y = x->left;
    x->left = y->right;
    if(y->right != NULL)
        y->right->parent = x;
    if(x == _root) _root=y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}
void RBTree::_rebalance(Node* node){
    while(node != _root && node->parent->color == RED){
        if(node->parent == node->parent->parent->left){//left branch
            Node* uncle = node->parent->parent->right;
            if(uncle && uncle->color == RED){//double RED-->change parent,uncle,grandpa, grandpa recursive
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }else{//parent RED, uncle BLACK, grandpa BLACK-->change parent/grandpa,rotate
                if(node == node->parent->right)
                   // node->parent->parent->left = _leftRotate(node->parent);
                   _leftRotate(node->parent);
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                Node* grandpa = node->parent->parent;
                _rightRotate(grandpa);
            }   
        }else{//right branch,similar action
            Node* uncle = node->parent->parent->left;
            if(uncle && uncle->color == RED){
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }   
            else{
                if(node == node->parent->left)
                    _rightRotate(node->parent);
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                Node* grandpa = node->parent->parent;
                _leftRotate(grandpa);
            }   
        }   
    }   
    _root->color = BLACK;

}

void RBTree::_insert(Node* node, Node* parent, int key){
    while(node != NULL){
        parent = node;
        if(key<node->key){
            node = node->left;
        }else if(key>node->key){
            node = node->right;
        }else
            return ;
    }
    if(node == NULL){
        node = new Node;
        node->left = node->right = NULL;
        node->parent = parent;
        node->color = RED;
        node->key = key;
        if(parent == NULL) _root=node;
        else{
            if(node->key < node->parent->key)
                node->parent->left = node;
            else
                node->parent->right = node;
        }
    }
    _rebalance(node);
}

int main(void){
	RBTree bst;
    int i=-1;
    int a[7]={6,4,7,2,5,1,3};
    //int a[7]={1,2,3,4,5,6,7};
    //int a[7]={7,6,5,4,3,2,1};
    while(i++<6){
        bst.insert(a[i]);
        //bst.inOrder();
        bst.print();
        cout<<endl;
    }
//        bst.inOrder();
        //bst.print();
    return 0;
}




























