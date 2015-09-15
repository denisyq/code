#include <map>

cons:
map<char,int> first;
map<char,int> second(first.begin(),first.begin()+5);
map<char,int> third(second);


iter:
begin;
end;
rbegin;
rend;

capacity:
size;
empty;


element_access:
map<int,string> map;
map[0]="hello"
cout<<map[0]<<endl;

map.at(0);

modify:

insert:
map<char,int> map={
    {'a',1},
    {'b',2},
    {'c',3} };

map,insert(pair<char,int>('d',4));
pair<map<char,int>::iterator,bool >ret;
ret = map.insert(pair<char,int>('e',5));
ret.second == false, already exist
ret.second == true; insert sucess
ret.first is map

2.efficiency insert, after iter
map.insert(iter,pair<char,int>('f',6) );

3. insert range
map.insert(first.begin(), first.begin()+4);


erase:
1. map.erase(iter);
2. map.erase('c');
3. map.erase(iter1, iter2);

swap:
map.swap(first);

clear:
map.clear();


more:
find:
iter = map.find('e');

count:
n = map.count('e');

lower_bound:
upper_bound: upper usually point to 99 latter
iter1 = map.lower_bound(88);
iter2 = map.upper_bound(99);

equal_range:
pair<map<char,int>::iterator,map<char,int>::iterator> ret;
ret = map.equal_range(99);










