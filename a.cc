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
#define SIZE (sizeof(array)/sizeof(array[0]));
int array[10]={1,1,2,3,4};

int main(int argc, char** argv){
	vector<int> iv(10,1);
	vector<int> iv2(iv);
	iv2.insert(iv2.begin()+1,iv.begin(),iv.end());
	
	return 0;
}

