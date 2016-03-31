#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

class Heap{
public:
    Heap(int n):n_(n){
        p = new int [n_];
        buildData();
    }
    ~Heap(){
        for(int i=0;i<n_;++i) cout<<p[i]<<" ";
        cout<<endl;
        delete[] p;
    }
    void buildData(void){
        int i=0;
        //while(i++<n_) p[i-1]=i;
        while(i++<n_) cin>>p[i-1];
    }
    void heapAdjust(int i,int size){
        int lchild = i*2+1;
        int rchild = lchild+1;
        int max = i;
        //root is max
        if(i<=size/2){//not leaf node
            //lchild,rchild,max is sequence number, range from (0--size-1)
            if(lchild<size && p[lchild]>p[max])
                max=lchild;
            if(rchild<size && p[rchild]>p[max])
                max=rchild;
            if(i!=max){
                swap(p[i],p[max]);
                heapAdjust(max,size);
            }
        }
    }
    void heapBuild(int size){
        for(int i=size/2-1;i>=0;--i){
            heapAdjust(i,size);
        }
    }
    void heapSort(void){
        int size=n_;
        while(size){
           heapBuild(size);
           swap(p[0],p[size-1]);
           size--;
        }
    }

private:
    int n_;
    int* p;
    

};
int main(void){
    Heap heap(10);
    //heap.heapBuild(10);
    heap.heapSort();
    return 0;
}

