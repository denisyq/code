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
    void unionSet(int x, int y){
        x = findSet(x);
        y = findSet(y);
        if(x==y) return; //x,y all in union
        if(p_[x]<p_[y]){ //union x has more members
            p_[x] += p_[y];
            p_[y] = x;
        }else{//union y has more members
            p_[y] += p_[x];
            p_[x] = y;
        }
    }
private:
    int n_;
    int *p_;
};
int main(void){
    disjointSet uni(10);
    uni.makeSet();

    int tmp;
    while(1){
        cin>>tmp;
        if(uni.findSet(1) != uni.findSet(tmp)){ 
            cout<<"not in union!"<<endl;
            uni.unionSet(1,tmp);
        }else{
            cout<<"already in union!"<<endl;
        }
    }
    return 0;
}




























