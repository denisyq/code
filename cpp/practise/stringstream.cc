#include <iostream>
#include <unistd.h>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

#if 0
//input file
4
1 2 3 4
aaa bbb ccc ddd
1.2 2.3 4.5 6.7
x y z
#endif

// string stream 
// ## getline(cin,std::string)
// ## stringstream.clear() -> stringstream.str(std::string)
// ## stringstream >> std::string/int/double  --> if(stringstream.fail()) break;

int main(int argc, char** argv){
	freopen("input","r",stdin);
	int n;
	cin>>n;
	cout<<n<<endl;
	vector<string> sv;
	string s;
	stringstream ss;
	for(int i=1;i<=n;i++){
		getline(cin,s);
		ss.clear();
		ss.str(s);
		while(1){
			string tmp;
			ss>>tmp;
			if(ss.fail()) break;
			sv.push_back(tmp);
		}

	}
	for(vector<string>::iterator it=sv.begin(); it!=sv.end(); it++)
		cout<< *it <<endl;
	return 0;
}

