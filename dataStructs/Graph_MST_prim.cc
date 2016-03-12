#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;

int data[7][7]={
    {0,0,0,0,0,0,0},
    {0,0,1,2,0,0,0},
    {0,1,0,0,1,2,0},
    {0,2,0,0,4,0,6},
    {0,0,1,4,0,5,5},
    {0,0,2,0,5,0,1},
    {0,0,0,6,5,1,0} };

class Prim{
public:
    Prim(int n, int src):vertex_(n),src_(src){
        visited_.assign(vertex_+1,0);
        path_.assign(vertex_+1,0);
        dist_.assign(vertex_+1,INT_MAX);
    }
    void work(){
        visited_[src_]=true;
        path_[src_]=0;
        dist_[src_]=0;
        
        int min,next=src_;
        for(int i=1;i<=vertex_;++i){
            for(int j=1;j<=vertex_;++j){
               if(!visited_[j] && data[next][j]!=0 && data[next][j]<dist_[j]){
                   dist_[j]=data[next][j];
                   path_[j]=next;
               }
            }
            min=INT_MAX;
            for(int k=1;k<=vertex_;++k){
                if(!visited_[k] && dist_[k]<min){
                    min = dist_[k];
                    next = k;
                }
            }
            visited_[next]=true;
        }
    }
    void print(void){
        for(int i=1;i<=vertex_;++i){//need find vertex-1 times
           if(path_[i]) cout<<"from "<<path_[i]<<" to "<<i<<endl;
        }
    }
private:
    vector<int> visited_;
    vector<int> path_;
    vector<int> dist_;
    int vertex_;
    int src_;
};
class Prim_priority_queue{
public:
    Prim_priority_queue(int n, int src):vertex_(n),src_(src){
        dist_.assign(vertex_+1,INT_MAX);
        visited_.assign(vertex_+1,0);
        path_.assign(vertex_+1,0);
    }
    void work(){
        visited_[src_]=true;
        dist_[src_]=0;
        path_[src_]=0;
        Node node;
        for(int i=1;i<=vertex_;++i){
            if(!visited_[i] && data[src_][i] !=0){
                dist_[i]=data[src_][i];
                path_[i]=src_;
                node.v = i;
                node.dist=data[src_][i];
                que.push(node);
            }
        }
        int size=1,next;
        //could use 
        //while(!que.empty()),as when size>=vertex, 
        //visited_[next] will filter them all. The latter in queue is due to relax
        while(size<vertex_){
            node = que.top();//if empty, error
            que.pop();
            next = node.v;
            //prev_dist = node.dist;//use for dijkstra
            if(visited_[next]) continue;
            visited_[next]=true;
            size++;
            for(int i=1;i<=vertex_;++i){
                if(!visited_[i] && data[next][i] !=0 && data[next][i] < dist_[i]){
                    dist_[i] = data[next][i];
                    path_[i] = next;
                    Node tmp;
                    tmp.v=i;tmp.dist=data[next][i];
                    que.push(tmp);
                }
            }
        }
    }
    void print(void){
        for(int i=1;i<=vertex_;++i){//need find vertex-1 times
           if(path_[i]) cout<<"from "<<path_[i]<<" to "<<i<<endl;
        }
    }

private:
    int vertex_;
    int src_;
    vector<int> dist_;
    vector<int> visited_;
    vector<int> path_;
    struct Node{
        int v;
        int dist;
        bool operator < ( const Node a )const {
            return dist > a.dist;
        }
    };
    priority_queue<Node> que;
    /*
       //could paste outside main(),not in class
    struct Node{
        int v;
        int dist;
    };
    bool operator < (Node node1, Node node2){
        return node1.dist > node2.dist;
    }
    priority_queue<Node> ip;

    */

};
int main(void){
    Prim_priority_queue prim(6,5);
    //Prim prim(6,5);
    prim.work();
    prim.print();
    return 0;
}

