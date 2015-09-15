  
  /* splay Tree, one time search may O(n), after
   * M times search, could reach Mlog(n), so average is log(n)
   */
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
#include <memory.h>
using namespace std;

typedef struct node{
    struct node* left;
    struct node* right;
    int data;
}Node;

class Splay{
public:
    Splay();
    ~Splay();
    void insert(int element);
    Node* remove(int element);
    Node* find(int element);
    void inOrder(void);
private:
    Node* root;
    Node* _insert(Node* root, int element);
    Node* _remove(Node* root, int element);
    Node* _find(Node* root, int element);
    Node* _singleToRight(Node* T);
    Node* _singleToLeft(Node* T);
    Node* _doSplay(Node* T,int element);
    void _makeEmpty(Node* root);
    void _inOrder(Node* root);
};

Splay::Splay(){
    root = NULL;
}
Splay::~Splay(){
    _makeEmpty(root);
}

void Splay::insert(int element){
    root = _insert(root,element);
}
Node* Splay::remove(int element){
    root = _remove(root,element);
}
Node* Splay::find(int element){
    root = _find(root,element);
}
void Splay::inOrder(void){
    _inOrder(root);
}
void Splay::_inOrder(Node* root){
    if(root != NULL){
        _inOrder(root->left);
        cout<<root<<"-"<<root->data<<endl;
        _inOrder(root->right);
    }   
}
Node* Splay::_doSplay(Node* T,int element){
    Node n, *l,*r;
    if(T == NULL) return T;

    n.left = n.right = NULL;
    l=r=&n;
    //cout<<"doSplay begin"<<endl;
    while(1){
        if(element < T->data){
            if(T->left == NULL)
                break;
            if(element < T->left->data)
                T = _singleToRight(T);
            if(T->left == NULL)
                break;
            //chop right
            r->left = T;
            r = T;
            T = T->left;
        }
        else if(element> T->data){
            if(T->right == NULL)
                break;
            if(element> T->right->data)
                T = _singleToLeft(T);
            if(T->right == NULL)
                break;
            //left link
            l->right = T;
            l = T;
            T = T->right;
        }
        else
            break;
    }
        //assemble
        l->right = T->left;
        r->left = T->right;
        T->left = n.right;
        T->right = n.left;
    //cout<<"++++++++++++++++++++++"<<endl;
    //cout<<"splay top "<<T->data<<endl;
    //cout<<"---------------------"<<endl;
    return T;
}
Node* Splay::_singleToRight(Node* T){
    Node *p;
    p = T->left;
    T->left = p->right;
    p->right = T;
    return p;
}
Node* Splay::_singleToLeft(Node* T){
    Node *p,*q,*k;
    p = T;
    q = T->right;
    k = q->left;
    p->right = k;
    q->left = p;
    T = q;
    return T;
}

Node* Splay::_insert(Node* T, int element){
    Node* node = new Node;
    node->data = element;
    
    //cout<<"insert "<<element<< endl;

    if(T == NULL){
        node->left = node->right = NULL;
        T = node;
    }
    else{
        T = _doSplay(T,element);
        if(element > T->data){
            node->left = T;
            node->right = T->right;
            T->right = NULL;
            T = node;
        }
        else if(element < T->data){
            node->left = T->left;
            node->right = T;
            T->left = NULL;
            T = node;
        }
        else
            delete node;
    }
    return T;
}
Node* Splay::_remove(Node* T, int element){
    Node* tmp;
    if(T == NULL) return NULL;

    T = _doSplay(T,element);

    if( element == T->data){
        if(T->left == NULL)//find max from
            tmp = T->right;
        else{
            tmp = _doSplay(T->left,element);
            tmp->right = T->right;
        }
        delete T;
        T = tmp;
    }
    return T;
}
Node* Splay::_find(Node* T, int element){
    T = _doSplay(T,element);
    if(element == T->data)
        return T;
    else 
        return NULL;
}
void Splay::_makeEmpty(Node* T){
    if(T != NULL){
        _makeEmpty(T->left);
        _makeEmpty(T->right);
        delete T;
    }
}
int main(){
    Splay *splay = new Splay;
    int i = -1;
    int a[7]={6,4,7,2,5,1,3};
    while(i++<6){
        splay->insert(a[i]);
        splay->inOrder();
        cout<<endl;
    }
    
    splay->remove(3);
    splay->inOrder();
    return 0;  
}  


























