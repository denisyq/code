#include <set>

//cons
set<int> first;
set<int> second(iter1, iter2);
set<int> third(first);


//iter
begin();
end();
rbegin();
rend();

//capacity
size:
empty:

//element access
find:
find(99); iterator=find(99);
count:
count(99); n=count(99);

lower_bound:
upper_bound:
iter1=set.lower_bound(10);
iter2=set.upper_bound(20);

equal_range:
pair<set<int>::const_iterator, set<int>::const_iterator> ret;
ret=set.equal_range(99);
lower_iter = *ret->first;
upper_iter = *ret->second;

//modify
insert:
pair<set<int>::iterator, bool> ret;
ret = set.insert(20);
iter = ret.first; //point to 20
ret.second == true; //true, insert success; false,already exist

set.insert(iter,20); //20 will insert after iter, has iter aim to enhance efficiency
set,insert(first.begin(),first.begin()=4);

erase:
set.erase(iter1);
set.erase(iter1, iter2);
set.erase(99);

swap:
set.swap(first);

clear:
set.clear();
