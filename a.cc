#include <iostream>
#include <unistd.h>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
#include <boost/bind.hpp>
#include <algorithm>
using namespace std;

void print(int a){
	cout<<a<<" ";
}
int main(int argc, char** argv){
	//typedef boost::shared_ptr<foo_class> ptr;

	vector<int> iv;
	iv.assign(9,5);
	for_each(iv.begin(),iv.end(),boost::bind(print,boost::bind(plus<int>(),10,_1)));
	cout<<endl;



	

	return 0;
}

