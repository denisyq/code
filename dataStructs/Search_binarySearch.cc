#include <iostream>
using namespace std;
int main(void){
    class Solution{
    public:
        int binary_search(const int A[], int N, int target){
            int left,right,mid;
            left=0;right=N-1;
            while(left<=right){
                mid=(left+right)/2;
                if(target == A[mid]) return mid;
                else if(target<A[mid]) right = mid-1;
                else left = mid+1;
            }
            return -1;
        }
    };

    Solution solution;
    int a[7] = {1,2,3,4,5,6,7};
    cout<<solution.binary_search(a,7,7)<<endl;
    cout<<solution.binary_search(a,7,9)<<endl;
    


    return 0;
}

