#include <iostream>
#include <unistd.h>
#include <boost/thread/thread.hpp>
#include <boost/shared_ptr.hpp>
using namespace std;

void createThread(void){
	cout<<"thread create!!" <<endl;
}
int main(int argc, char** argv){
	boost::thread thread(&createThread);
	thread.join();
	//boost::shared_ptr<int> i = &x;

	return 0;
}

