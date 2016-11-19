#include <iostream>
#include <sys/time.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <memory.h>
#include <queue>
#include <map>
#include <tr1/unordered_map>
using namespace std;

class Person{
public:
	//if hash is the same, different from the other
	bool operator==(const Person& p) const{
		return memcmp(this, &p, sizeof(Person)) == 0? true:false;	
	}
public:
	string name;
	int age;
	string addr;
	bool gender;
};
/* 
 * global method to over-write operator ==
 */
/*
bool operator==(const Person &p1, const Person &p2){
	return memcmp(&p1, &p2, sizeof(Person)) == 0 ? true:false;
}
*/
struct Person_hash_func{
	size_t operator()(const Person& per) const{
		int hash = 7;
		//use Person::name as hash key
		for (int i = 0; i < per.name.size(); i++) {
			    hash = hash*31 + per.name[i];
		}
		return hash;
	}
};
int main(void){
	/*
	 * tr1::unordered_map APIs: refet to /usr/include/c++/4.8/tr1/hashtable.h
	 */

	//tr1::unordered_map<Person*, string, Person_hash_func> pmap;

	/* basic int/string/... has its own hash in unordered_map
	 * but if self-defined struct as map.key like:
	 * tr1::unordered_map<Person*, string> pmap
	 * that will definitely need hash_func as above example
	 */
	tr1::unordered_map<string, Person*> pmap;
	//Iterator: begin(),end()
	typedef tr1::unordered_map<string, Person*>::iterator ITER;
	ITER it;
	Person man;
	man.name = "alex";
	man.age  = 18;
	man.addr = "king's avenue";
	man.gender = true;
	Person woman;
	woman.name = "juli";
	woman.age  = 19;
	woman.addr = "queen's avenue";
	woman.gender = false;

	//insert(v), insert(iter,v), insert(iter,iter);
	//erase(iter),erase(v),erase(iter,iter);
	pair<ITER,bool> ret_insert;
	ret_insert = pmap.insert(make_pair<string,Person*>("alex",&man));
	ret_insert = pmap.insert(make_pair<string,Person*>("juli",&woman));
	ret_insert = pmap.insert(make_pair<string,Person*>("juli",&man));
	//size/empty/clear/swap
	//bucket_count(like reserve)
	cout<<pmap.size()<<endl;
	pair<ITER,ITER> ret1 = pmap.equal_range("juli");
	for(ITER it = ret1.first; it!= ret1.second;it++){
		cout<<it->second->name<<endl;
	}

	//find/count/equal_range(unordered_multimap)
	it = pmap.find("juli");
	cout<<it->second->name<<" "<<it->second->addr<<endl;

	/**************************************************/
	tr1::unordered_multimap<int,int> imap;
	imap.insert(make_pair<int,int>(1,1));
	imap.insert(make_pair<int,int>(1,2));
	imap.insert(make_pair<int,int>(1,3));
	cout<<imap.size()<<endl;

	


		


}


