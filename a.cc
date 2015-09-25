#include <iostream>
#include <unistd.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
using namespace std;

int index_=1;
boost::mutex io_mutex,mu;

void add(void){
	sleep(3);
	{
		//boost::unique_lock<boost::mutex> scoped_lock(mu);
		//typedef boost::unique_lock<boost::mutex> scoped_lock;
		boost::mutex::scoped_lock lock(mu);
		index_++;
	}
	{
		boost::mutex::scoped_lock lock(io_mutex);//cout is not thread safe
		cout<<"add create!!, index=" << index_<<endl;
	}
}
void des(void){
	{
		boost::mutex::scoped_lock lock(mu);
		index_--;
	}
	{
		boost::mutex::scoped_lock lock(io_mutex);//cout is not thread safe
		cout<<"des create!!, index=" << index_<<endl;
	}
}
void foo(void){
}
int main(int argc, char** argv){
	boost::thread thread1(&add);
	boost::thread thread2(&des);
	thread2.detach();
	thread1.join();
	thread2.join();
	{
		boost::mutex::scoped_lock lock(io_mutex);//cout is not thread safe
		cout<<index_<<endl;
	}

	return 0;
}

