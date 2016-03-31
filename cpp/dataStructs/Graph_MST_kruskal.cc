#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;


class disjointSet{
public:
    disjointSet(int n):n_(n){
        p_ = new int [n_];
    }
    ~disjointSet(){
        delete[] p_;
    }
    //default set to -1 and p_[root] is negative data
    void makeSet(void){
        for(int i=0;i<n_;++i)
            p_[i] = -1;
    }
    int findSet(int x){
        if(p_[x] < 0) return x;
        p_[x] = findSet(p_[x]);
        return p_[x];
        /*
        //method 2
        int t=x;
        while(p_[t]>=0) t=p_[t];
        while(x != t){
            int tmp=p_[x];
            p_[x] = t;
            x = tmp;
        }
        return x;
        */
    }
    //p_[root] equals how many units he has, -p_[root] is positive
    //who smaller, who change father point
    int unionSet(int x, int y){
        x = findSet(x);
        y = findSet(y);
        if(x==y) return 0; //x,y all in union
        if(p_[x]<p_[y]){ //union x has more members
            p_[x] += p_[y];
            p_[y] = x;
        }else{//union y has more members
            p_[y] += p_[x];
            p_[x] = y;
        }
        return 1;
    }
    friend class kruskal;
private:
    int n_;
    int *p_;
};


typedef struct node{
    int src;
    int dest;
    int weight;
}Node;

bool cmp(const Node& x, const Node& y){
    return x.weight > y.weight;
}

class kruskal{
public:
    kruskal(int n,int m):vertex_(n),edge_(m){
        v_.clear();
    }
    void buildData(void){
        int x,y,w;
        int edge=edge_;
        while(edge--){
            cin>>x>>y>>w;
            node_.src=x;
            node_.dest=y;
            node_.weight = w;
            v_.push_back(node_);
        }
    }
    void work(void){
        sort(v_.begin(), v_.end(), cmp);
        disjointSet set(vertex_+1);
        set.makeSet();
        int time=0;
        while(edge_--){
            node_=v_.back();
            v_.pop_back();
            if(set.unionSet(node_.src,node_.dest)){
                cout<<"from "<<node_.src<<" to "<<node_.dest<<" weight "<<node_.weight<<endl;
                time++;
            }
            if(time == vertex_-1) break;
        }
    }
    void printVector(){
        vector<Node>::iterator it;
        for(it=v_.begin();it!=v_.end();++it)
            cout<<it->weight<<endl;
    }

private:
    Node node_;
    vector<Node> v_;
    int vertex_;
    int edge_;

};
int main(void){
    kruskal k(3,3);
    k.buildData();
    k.work();
    
    return 0;
}




























