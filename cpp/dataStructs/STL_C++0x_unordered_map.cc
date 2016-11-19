#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
#include <queue>
#include <memory.h>
#include <unordered_map>
using namespace std;


int main(void){
//cons
	unordered_map<int, int> imap;
	typedef unordered_map<int, int>::iterator ITER;
	imap.insert(make_pair(1,1));
	imap.insert(make_pair(1,2));
	imap.insert(make_pair(2,2));
	imap.insert(make_pair(3,3));

//size/empty/clear/swap
	if(!imap.empty())
		cout<<"size: "<<imap.size()<<" max_size:"<<imap.max_size()<<endl;
//iter - begin/end

//element: []/at(n)
	cout<<"element 1:"<<imap[1]<<endl;
	cout<<"element 1:"<<imap.at(1)<<endl;
	
	//find/count/equal_range
	ITER it = imap.find(1);
	if(it != imap.end() ){
		cout<<"find element:"<<it->first<<" is "<<it->second<<endl;
	}
	cout<<"how many is elemnt 1:"<<imap.count(1)<<endl;
	
//insert/erase
	//imap.erase(imap.begin());	
	it = imap.find(1);
	if(it != imap.end() ){
		cout<<"find element:"<<it->first<<" is "<<it->second<<endl;
	}else{
		cout<<"not find"<<endl;
	}
	
	imap.insert(make_pair(11,11));
	imap.insert(make_pair(12,12));

//bucket: bucket_count/max_bucket_count/bucket_size/bucket(x->first)
	int size = imap.bucket_count();
	cout<<"bucket count:"<<size<<" max bucket count:"<<imap.max_bucket_count()<<endl;
	for(auto i=0;i<size;++i){
		cout<<"bucket size:"<<imap.bucket_size(i)<<" index:"<<i<<" ";
		for(auto ii = imap.begin(i); ii != imap.end(i);++ii){
			cout<<"["<<ii->first<<":"<<ii->second<<"] ";
		}cout<<endl;
	}
	cout<<"which bucket has element 1:"<<imap.bucket(it->first)<<endl;

//hash policy: load_factor/max_load_factor/hash_function
	cout<<"hash policy: load_factor:"<<imap.load_factor()<<endl;
	cout<<"hash policy: max_load_factor:"<<imap.max_load_factor()<<endl;
	
	unordered_map<int,int>::hasher func = imap.hash_function();
	cout<<"hash function:"<<func(10)<<endl;
    return 0;
}



