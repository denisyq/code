#include <iostream>
#include <string>
#include <stack>
using namespace std;
stack<string> stack_str;
int main(void){

    class Solution{
    public:
        inline int max2(int a, int b){
            return a>=b?a:b;
        }
        inline int max3(int a,int b,int c){
            return max2(max2(a,b),c);
        }
        int max(const int A[],int left, int right){
            int maxLeftSum, maxRightSum;
            int maxLeftBorder,maxRightBorder;
            int center;
            if(left==right)
                return A[left]>0?A[left]:0; 
            center = (left+right)/2;
            maxLeftSum  = max(A,left,center);
            maxRightSum = max(A,center+1,right);
            maxLeftBorder=maxRightBorder=0;
            int tmp=0;
            for(int i=center;i>=left;--i){
                tmp += A[i];
                if(tmp>maxLeftBorder) maxLeftBorder=tmp;
            }
            tmp=0;
            for(int i=center+1;i<=right;++i){
               tmp+=A[i];
               if(tmp>maxRightBorder) maxRightBorder=tmp;
            }
            return max3(maxLeftSum,maxRightSum,maxLeftBorder+maxRightBorder);
        }
        int algorithm3(const int A[], int N){
            return max(A,0,N-1);   
        }
        int algorithm4(int A[], int N){
            int tmp=0,sum=0;
            for(int i=0;i<N;++i){
               tmp += A[i];
               if(tmp>sum)
                   sum = tmp;
               else if(tmp<0)
                   tmp = 0;
            }
            return sum;
        }
    };

    Solution solution;
    int a[7]={-1,2,3,4,5,6,-2};
    cout<<solution.algorithm3(a,7)<<endl;
    cout<<solution.algorithm4(a,7)<<endl;
    


    return 0;
}

