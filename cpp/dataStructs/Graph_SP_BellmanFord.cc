#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

int dataDirection[7][7]={
    {0,0,0,0,0,0,0},
    {0,0,1,1,0,0,0},
    {0,0,0,0,1,1,0},
    {0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0},
};
typedef struct node{
    int u;
    int v;
    int cost;
}Node;

const int NUM_EDGE=7;
Node edge[NUM_EDGE];

void initData(void){
    edge[0].u=1;edge[0].v=2;edge[0].cost=1;
    edge[1].u=1;edge[1].v=3;edge[1].cost=1;
    edge[2].u=2;edge[2].v=4;edge[2].cost=1;
    edge[3].u=2;edge[3].v=5;edge[3].cost=1;
    edge[4].u=5;edge[4].v=3;edge[4].cost=-3;
    edge[5].u=3;edge[5].v=6;edge[5].cost=1;
    edge[6].u=6;edge[6].v=5;edge[6].cost=6;//cause negative loop
}
//BellmanFord algorithm aims to edge while dijkstra aims to vertex.
//BellmanFord adjacent matrix form will cause O(V*V*V)
//BellmanFord adjacent list form will cause O(V*E)
//Be sure understand vertex-1 times to get the relax results 
//and up to V*E times, one more relax will get negative loop.
class BellmanFord{
public:
    BellmanFord(int n,int src):vertex_(n),src_(src){
        dist_.assign(vertex_+1,999);
        visited_.assign(vertex_+1,0);
        path_.assign(vertex_+1,0);
    }
    bool work(){
        dist_[src_]=0;
        bool relax=false;
        /* except the src, has vertex-1 times to relax
           every time, relax every edge if any, O(V*E)
           'relax' flag is set to find when no relax happens
           which means no need to relax any more,then break
           will cause flexibility decrease.
        */
        for(int i=1;i<=vertex_-1;++i){
            cout<<"i="<<i<<"-----"<<endl;
            relax=false;
            for(int j=0;j<NUM_EDGE;++j){
                if(dist_[edge[j].u]+edge[j].cost < dist_[edge[j].v]){
                    dist_[edge[j].v] = dist_[edge[j].u]+edge[j].cost;
                    path_[edge[j].v] = edge[j].u;
                    relax=true;;
                    cout<<edge[j].u<<"------>"<<edge[j].v<<endl;
                }
            }
            if(!relax) break;
        }
        //check whether negative loop
        bool flag=true;
        for(int i=1;i<=NUM_EDGE;++i){
            if(dist_[edge[i].u]+edge[i].cost < dist_[edge[i].v]){
                flag=false;
                break;
            }
        }
        return flag;
        
    }

    void printPath(int index){
        stack<int> s;
        int i = index;
        s.push(i);
        while(i!=src_){
            s.push(path_[i]);
            i = path_[i];
        }   
        //data ready, print the stack
        while(!s.empty()){
            cout<<"->"<<s.top();
            s.pop();
        }   
        cout<<endl;
    }   
 
private:
    int vertex_;
    int src_;
    vector<int> dist_;
    vector<int> visited_;
    vector<int> path_;
};


int main(void){
    cout<<"------------"<<endl;
    initData();
    BellmanFord bell(6,1);
    if(bell.work())
        bell.printPath(5);
    else 
        cout<<"negative loop"<<endl;
    return 0;
}

