#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
#include <memory.h>
using namespace std;

typedef struct Node{
    int dest;
    int weight;
    Node* next;
}Node;

class Topo{
public:
    Topo(int vertex, int edge):n_(vertex),edge_num_(edge){
        visited_ = new bool [n_];
        memset(visited_,0,sizeof(visited_));
        node_ = new Node* [n_];
        for(int i=0;i<n_;++i)
            node_[i]=NULL;
        indegree = new int [n_];
        for(int i=0;i<n_;++i)
            indegree[i]=0;
    }
    ~Topo(){
        delete[] visited_;
        delete[] node_;
    }
    void buildData(){
        int src,dest,weight;
        for(int i=0;i<edge_num_;++i){
            cin>>src>>dest>>weight; 
            Node *tmp = new Node;
            tmp->dest = dest;
            tmp->weight = weight;
            tmp->next = NULL;

            if(node_[src] != NULL){
                Node*  a = node_[src];
                while(a->next != NULL) a=a->next;
                a->next = tmp;
                    
            }else{
                node_[src] = tmp;
            }
        }
    }
    void work(){
        //init indegree
        for(int i=0;i<n_;++i){
            Node* tmp = node_[i];
            while(tmp != NULL){
                indegree[tmp->dest]++;
                tmp =  tmp->next;
            }
        }
        for(int i=0;i<n_;i++)
            if(indegree[i] == 0)
                is_.push(i);

        int size=0;
        while(!is_.empty()){
            int tmp = is_.top();
            is_.pop();
            cout<<tmp<<endl;
            size++;
            
            Node* node = node_[tmp];
            while(node != NULL){
                indegree[node->dest]--;
                if(indegree[node->dest] == 0)
                    is_.push(node->dest);
                node = node->next;
            }
        }
        if(size == n_) cout<<"no loop"<<endl;
        else if(size<n_) cout<<"loop find" <<endl;
    }
    void printAdjList(void){
        for(int i=0;i<n_;++i){
            Node* tmp = node_[i];
            cout<<"____"<<i<<"____"<<endl;
            while(tmp != NULL){
                cout<<"->"<<tmp->dest<<":"<<tmp->weight<<endl;
                tmp = tmp->next;
            }
        }

    }
private:
    bool *visited_;
    int n_,edge_num_;
    Node** node_;
    int* indegree;
    stack<int> is_;

};

int main(void){
    int vertex,edge;
    cin>>vertex>>edge;
    Topo topo(vertex,edge);
    topo.buildData();
    //topo.printAdjList();
    topo.work();
    return 0;
}




























