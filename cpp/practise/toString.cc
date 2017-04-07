#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char* argv){
	/*************************
	  * int/float --> string
	  ************************/
	
	//snprintf
	char string[100];
	int inter=1001;
	snprintf(string, 100, "%d", inter);

	//string stream
	stringstream ss;
	string s;
	ss<<1001;
	ss>>s;
	cout<<s<<endl;

	//g++0x to_string
	string s = to_string(1001);
}
