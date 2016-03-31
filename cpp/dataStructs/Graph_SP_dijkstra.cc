#include <iostream>
#include <vector>
#include <stack>
using namespace std;

    int data[7][7]={
        {0,0,0,0,0,0,0},
        {0,0,1,2,0,0,0},
        {0,1,0,0,1,2,0},
        {0,2,0,0,4,0,6},
        {0,0,1,4,0,5,5},
        {0,0,2,0,5,0,1},
        {0,0,0,6,5,1,0} };

//NOTE:
//1. Dijkstra dij(vertex,src);
//2. dij.work();
class Dijkstra{
public:
    Dijkstra(int n, int src):vertex_(n),src_(src){
        visited_.assign(vertex_+1,0);
        path_.assign(vertex_+1,0);
        dist_.assign(vertex_+1,999);//999 could be INF
    }
    void work(){
        //init src_ data
        visited_[src_]=true;
        path_[src_]=src_;
        dist_[src_]=0;

        int min,next=src_;
        for(int i=1;i<=vertex_;++i){
            //go through around, update dist_ using minimun distance
            for(int j=1;j<=vertex_;++j){
                if(!visited_[j] && data[next][j] != 0 && dist_[next]+data[next][j]<dist_[j]){
                    dist_[j]=dist_[next]+data[next][j];
                    path_[j]=next;
                }
            }
            min=999;
            //find the next stop 
            for(int k=1;k<=vertex_;++k){
                if(!visited_[k] && dist_[k]<min){
                    min=dist_[k];
                    next=k;
                }
            }
            //found next and enable visited
            //"next" is the another source stop
            visited_[next]=true;
        }
    }
    void getDistance(vector<int> &tmp){
        tmp.assign(dist_.begin(),dist_.end());
    }
    void printDistance(int index){
        cout<<"distance["<<index<<"]:"<<dist_[index]<<endl;
    }
    void printPath(int index){
        stack<int> s;
        int i = index;
        s.push(i);
        while(path_[i]!=src_){
            s.push(path_[i]);
            i = path_[i];
        }
        s.push(src_);
        //data ready, print the stack
        while(!s.empty()){
            cout<<"->"<<s.top();
            s.pop();
        }
        cout<<endl;
    }
    void printVec(vector<int> vec){
        vector<int>::iterator it=vec.begin()+1;
        for(;it!=vec.end();++it)
            cout<<*it<<" ";
        cout<<endl;
    }
private:
    vector<int> visited_;
    vector<int> path_;
    vector<int> dist_;
    int vertex_;//how many vertex
    int src_;//fron src
};


    

int main(void){
    Dijkstra dij(6,1);
    dij.work();
    
    dij.printDistance(6);
    dij.printPath(6);
   
    return 0;
}

