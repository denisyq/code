#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
#include <memory.h>
#include <unordered_map>
#include <random>
using namespace std;

void print(int i){
	cout<<i<<" ";
}
struct isOdd{
	bool operator()(int a){
		return (a%2 == 1)? true:false;
	}
};
int main(void){
	int arr[] = {1,2,3};
	vector<int> iv(arr,arr+3);
	vector<int> dest(10,0);
	typedef vector<int>::iterator ITER;


	/*************
	  NO MODIFY - for_each/find/
	  ************/
	for_each(iv.begin(), iv.end(), print);cout<<endl;
	vector<int>::iterator it = find(iv.begin(), iv.end(), 3);




	/********************
	 MODIFY_SEQUENCE - copy/copy_backward/replace/remove/unique/reverse/reverse_copy/shuffle
	 ********************/
	vector<int> ivv(10,0);
	copy(iv.begin(),iv.end(),ivv.begin());//1 2 3 0 0 0 0 0 0 0
	copy_backward(iv.begin(), iv.end(), ivv.end());//1 2 3 0 0 0 0 1 2 3

	//replace(iter1, iter2, const T& old_value, const T& new_value);
	replace(ivv.begin(), ivv.end(), 3, 30);//1 2 30 0 0 0 0 1 2 30

	//remove: 30后面的前移，最后两个是原数据，为erase(remove)做基础
	//remove 返回值是在倒数第二个iter
	remove(ivv.begin(), ivv.end(), 30);//1 2 0 0 0 0 1 2 2 30

	//跟remove一样，返回值是最后一个iter	
	//unique, 只跟前值比较
	it = unique(ivv.begin(),ivv.end());//1,2,0,1,2,30
	ivv.erase(it, ivv.end());

	//reverse
	reverse(ivv.begin(), ivv.end());
	reverse_copy(ivv.begin(), ivv.end(), dest.begin());

	//for_each(dest.begin(), dest.end(), print);cout<<endl;
	srand((unsigned)time(0));
	shuffle(iv.begin(), iv.end(), default_random_engine(rand()));

	/*******************
	  SORT
	  *****************/
	//partition > nth_element > partial_sort > sort > stable_sort
	partition(ivv.begin(), ivv.end(), isOdd());
	nth_element(ivv.begin(), ivv.begin()+3, ivv.end(), greater<int>());
	partial_sort(ivv.begin(), ivv.begin()+3, ivv.end(), greater<int>());
	sort(ivv.begin(),ivv.end(), greater<int>());
	stable_sort(ivv.begin(),ivv.end(), greater<int>());

	/****************
	  BINARY_SEARCH
	  **************/
	//Must be ordered, random accessed
	bool ret = binary_search(ivv.begin(), ivv.end(), 30);
	ITER iter_lower = lower_bound(ivv.begin(), ivv.end(), 30);
	ITER iter_upper = upper_bound(ivv.begin(), ivv.end(), 30);
	pair<ITER, ITER> ret1 = equal_range(ivv.begin(), ivv.end(), 30);


	/*************
	  MERGE - set_union / set_intersection
	  ************/
	//set_union(iter_first1, iter_last1, iter_first2, iter_last2, iter_result,comp)
	//set_intersection(iter_first1, iter_last1, iter_first2, iter_last2, iter_result,comp)


	//HEAP - make_heap/push_heap/pop_heap/sort_heap
	//if greater, add greater<int>() in every API
}
