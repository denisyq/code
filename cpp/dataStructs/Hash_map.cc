#include <iostream>
#include <cstdlib>
#include <string>
#include <ext/hash_map>
#include <unordered_map>

using namespace __gnu_cxx;
using namespace std;
int main(int argc, char** argv){

	/* HASH_MAP 
	 * designed by GNU, not standard, replaced by unordered_map (0x11)
	 * compared with STL::map: hash VS. RBTree -> O(1) VS. O(logN)
	 * memory needs > STL::map and slower hash constructor
	 * 
	 */
	hash_map<int,string> hashmap(10);
	hashmap.insert(pair<int,std::string>(1,"hello"));
	//data_type& operator[](const key_type& k)
	hashmap[2] = "i donot know";
	//const interator find(const key_type& k) const
	hash_map<int,std::string>::iterator it = hashmap.find(4);
	if( it != hashmap.end()){
		std::cout<<"find"<<std::endl;
		hash_map.erase(it);
	}else 
		std::cout<<"not find"<<std::endl;

//TODO
// how to realize hash_map by hash function and map
// http://cache.baiducontent.com/c?m=9f65cb4a8c8507ed4fece763105392230e54f73260878e482a958448e435061e5a32b0e76f784b528e99292c49ff0241a8ed3773340627b49fdf883d87fdcd763bcd7a742613dc1253890eaebb5122b537912ab6fc5b&p=c2769a479f8002ff57ee947f505c82&newp=882a9645d78717dd0be296261641c4231610db2151d7d2106b82c825d7331b001c3bbfb423231204d9c5796200aa4d59ebf13277300421a3dda5c91d9fb4c57479cc7146&user=baidu&fm=sc&query=hash_map&qid=a9d2eb0f00291603&p1=3


	/* unordered_map
	 * build: g++ a.cc -std=c++0x -o a
	 */
	unordered_map<int,string> unmap;


	return 0;
}
