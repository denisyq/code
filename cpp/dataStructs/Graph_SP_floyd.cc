#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*int data[7][7]={
    {0,0,0,0,0,0,0},
    {0,0,1,2,0,0,0},
    {0,1,0,0,1,2,0},
    {0,2,0,0,4,0,6},
    {0,0,1,4,0,5,5},
    {0,0,2,0,5,0,1},
    {0,0,0,6,5,1,0} };
    */
int data[7][7]={
    {0,0,0,0,0,0,0},
    {0,100,1,2,100,100,100},
    {0,1,100,100,1,2,100},
    {0,2,100,100,4,100,6},
    {0,100,1,4,100,5,5},
    {0,100,2,100,5,100,1},
    {0,100,100,6,5,1,100} };

class Floyd{
public:
    
    Floyd(int n):num_(n){
        //create 2 dimension array
        //init path_[][]
        path_ = new int *[num_+1];
        for(int i=0;i<=num_;++i){
            path_[i] = new int[num_+1];
            for(int j=0;j<=num_;++j)
                path_[i][j]=i;
        }
    }
    ~Floyd(){
        for(int i=0;i<=num_;++i)
            delete[] path_[i];
        delete[] path_;
    }
    
    /*
    note: data[i][j]>data[i][k]+data[k][j] is typical Dynamic Programming
    */
    void work(void){
        for(int k=1;k<=num_;++k){
            for(int i=1;i<=num_;++i){
                for(int j=1;j<=num_;++j){
                    if(data[i][j]>data[i][k]+data[k][j]){
                        data[i][j] = data[i][k]+data[k][j];
                        path_[i][j] = path_[k][j];
                    }
                }
            }
        }
    }
    void printTotalWeight(void){
        for(int i=1;i<=num_;++i){
            for(int j=1;j<=num_;++j){
                cout<<" "<<data[i][j];
            }
            cout<<endl;
        }
    }
    void printWeight(int src, int dest){
        cout<<"from "<<src<<" to "<<dest<<",the SP is "<<data[src][dest]<<endl;
    }
    void printPath(int src, int dest){
        stack<int> s;
        int i=dest;
        s.push(i);
        while(path_[src][i] != src){
            s.push(path_[src][i]);
            i = path_[src][i];
        }
        s.push(src);
        while(!s.empty()){
            cout<<s.top()<<" ";
            s.pop();
        }
        cout<<endl;
    }
private:
    int num_;
    int** path_;
};


int main(void){
    Floyd floyd(6);
    floyd.work();
    floyd.printWeight(3,5);
    floyd.printPath(3,5);
    return 0;
}

