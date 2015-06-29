#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <boost/bind.hpp>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//boost::bind - usage 1
void print(int i, int j){
	cout<<"i "<<i <<" j "<<j<<'\n';
}

//boost::bind - usage 2
class Temp{
public:
	void printTemp(int x){
		cout<<"Temp class print "<<x<<endl;
	}
};

//boost::bind - usage 3
class Personal_Info{
	int age_;
	string name_;
public:
	Personal_Info(int age, string name):age_(age),name_(name){}
	int get_age() const{ 
		return age_;
	}
	string name() const{ 
		return name_;
	}
	void print_age(){cout<<"Personal_Info age:"<<age_<<endl;}
	void print_name(){cout<<"Personal_Info name:"<<name_<<endl;}
};

//boost::bind - usage 4
void printString (string s){
	cout<<s<<endl;
}
int main(int argc, char** argv){
	//usage 1
	int i=2,j=3;
	boost::bind(&print,20,3)();

	//usage 2
	Temp* t=new Temp;
	boost::bind(&Temp::printTemp,t,4)();
	boost::bind(&Temp::printTemp,_1,5)(t);

	//usage 3
	typedef vector<Personal_Info> PersonInfo;
	PersonInfo pv;
	Personal_Info p1(25,"dennis");
	Personal_Info p2(26,"royce");
	Personal_Info p3(18,"fendi");
	pv.push_back(p1);
	pv.push_back(p2);
	pv.push_back(p3);
	pv.push_back(Personal_Info(33,"lucy"));
	sort(pv.begin(),pv.end(),boost::bind(less<int>(),
											boost::bind(&Personal_Info::get_age,_1),
											boost::bind(&Personal_Info::get_age,_2)));
	for_each(pv.begin(),pv.end(),boost::bind(&Personal_Info::print_age,_1));

	sort(pv.begin(),pv.end(),boost::bind(greater<string>(),
											boost::bind(&Personal_Info::name,_1),
											boost::bind(&Personal_Info::name,_2)));
	for_each(pv.begin(),pv.end(),boost::bind(&Personal_Info::print_name,_1));


	//usage 4
	map<int,string> mm;
	mm.insert(make_pair<int,string>(0,"boost"));
	mm.insert(make_pair<int,string>(1,"bind"));
	mm.insert(make_pair(2,"fine"));

	for_each(mm.begin(),mm.end(),boost::bind(&printString,
												boost::bind(&map<int,string>::value_type::second,_1)));
	
	
	return 0;
}
