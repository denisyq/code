#include <iostream>
#include <unistd.h>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <deque>
#include <list>
using namespace std;

void print(int a){
	cout<<a<<" ";
}
void printChar(char a){
	cout<<a<<" ";
}
void printstring(string& s, const char* name){
	cout<<name<<": "<<s<<endl;
}
int main(int argc, char** argv){
	vector<char> vec_char;
	for(int i=0;i<=10;i++)
		vec_char.push_back(i+'a');
	//for_each(vec_char.begin(),vec_char.end(),printChar);
	string s1(vec_char.begin(),vec_char.end());
	string s2(s1);
#if 0
	//iterator
	string::iterator it=s1.begin();
	for(;it!=s1.end();it++)
		cout<<*it<<endl;

	//size/capacity
	cout<<s1.size()<<" "<<s1.capacity()<<endl;
	string temp;
	temp.swap(s2);
	temp.clear();
	cout<<temp<<endl;
	cout<<s2<<endl;

	//assign
	string tmp;
	tmp.assign(s1.begin()+2,s1.end());
	cout<<tmp<<endl;

	//insert/erase
	s1.insert(s1.begin(),s2.begin(),s2.end());
	s1.erase(s1.begin(),s1.begin()+s1.size()/2);
	cout<<s1<<endl;
	cout<<s2<<endl;
#endif
	//more
	
	//append/substr
	s1.append(s2);
	string tmp = s1.substr(0,s1.size()/2);
	printstring(tmp,"tmp_substr");

	s1.erase(s1.begin());
	size_t pos = s1.find(s2);
	if(pos != string::npos)
		cout<<"pos "<<pos<<endl;
	s1 = s1.substr(pos,s2.size());
	cout<<"compare ret "<<s1.compare(s2)<<endl;

	s1.replace(s1.begin(),s1.end(),s2);
	s1.replace(s1.begin(),s1.end(),"hello",4);
	//s1.replace(s1.begin(),s1.end(),s2.begin(),s2.begin()+3);


	





	printstring(s1,"s1");	
	printstring(s2,"s2");	
	return 0;
}

