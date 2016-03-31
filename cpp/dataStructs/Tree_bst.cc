#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
#include <memory.h>
using namespace std;

typedef struct node{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
}Node;

class BST{
    public:
        BST();
        ~BST();
        void inOrder(void);
        void insert(int key);
        Node* find(int key);
        Node* remove(int key);
    private:
        Node* _root;
        Node* _insert(Node* node, int key);
        Node* _find(Node* node, int key);
        Node* _remove(Node* node, int key);
        void _makeEmpty(Node* node);
        void _inOrder(Node* node);
		Node* _findMin(Node* node);
		Node* _findMax(Node* node);

};
BST::BST(){
    _root = NULL;
}
BST::~BST(){
    _makeEmpty(_root);
}
void BST::_inOrder(Node* root){
    if(root != NULL){
        _inOrder(root->left);
        cout<<" "<<root<<"-"<<root->key<<" left="<<root->left<<" right="<<root->right<<endl;
        _inOrder(root->right);
    }
}
void BST::inOrder(void){
    _inOrder(_root);
}
void BST::_makeEmpty(Node* root){
    if(root == NULL) return;
    else{
        _makeEmpty(root->left);
        _makeEmpty(root->right);
    }
    delete root;
}
void BST::insert(int key){
    _root = _insert(_root,key);
}
Node* BST::_insert(Node* node, int key){
    if(node == NULL){
        node = new Node;
        node->left = node->right = NULL;
        node->key = key;
    }
    else if( key < node->key){
        node->left  = _insert(node->left,key);
    }
    else if( key > node->key){
        node->right = _insert(node->right,key);
    }
    return  node;
}

Node* BST::find(int key){
    return _find(_root,key);
}
Node* BST::_find(Node* node, int key){
    if(node == NULL) return NULL;
    if(key < node->key)
        return _find(node->left,key);
    else if(key > node->key)
        return _find(node->right,key);
    else
        return node;
}
Node* BST::_findMin(Node* node){
    if(node == NULL) return node;
    else if(node->left == NULL) return node;
    else
        return _findMin(node->left);
}
Node* BST::_findMax(Node* node){
    if(node != NULL){
        while(node->right != NULL)
            node = node->right;
    }
    return node;
}
Node* BST::remove(int key){
	_root = _remove(_root,key);
	return _root;
}
//remove using recursive, can avoid node->parent config
//basiclly, do not forget node->parent config.
Node* BST::_remove(Node* node, int key){
	if(node == NULL) return NULL;
	else if( key < node->key)
		node->left = _remove(node->left,key);
	else if(key > node->key)
		node->right = _remove(node->right,key);
	else{
		if(node->left != NULL && node->right != NULL){
			Node* tmp = _findMin(node->right);
			node->key = tmp->key;
			node->right =  _remove(node->right,node->key);
		}
		else{
			Node* tmp = node;
			if(node->left == NULL)
				node = node->right;
			else
				node = node->left;
			delete tmp;
		}
	}
	return node;
}
int main(void){
	BST bst;
    int i=-1;
    //int a[7]={6,4,7,2,5,1,3};
    //int a[7]={1,2,3,4,5,6,7};
    int a[7]={7,6,5,4,3,2,1};
    while(i++<6){
        bst.insert(a[i]);
        bst.inOrder();
        cout<<endl;
    }

    int j;
    cout<<"delete one number"<<endl;
    cin>>j;
    Node* tmp = bst.remove(j);
    if(tmp != NULL)
        cout<<tmp->key<<endl;
    bst.inOrder();

    return 0;
}




























