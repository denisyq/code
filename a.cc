#include <iostream>
#include <unistd.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

// 1. std::cout is not thread safe, need io_mutex protect to print
// 2. use lock guard: 
//			boost::mutex::scoped_lock lock(mutex)  
//			boost::unique_lock<boost::mutex> lock(io_mutex) ##type could change to boost::timed_mutex


using namespace std;

int index_=1;
boost::mutex io_mutex,mu;

void add(void){
	//sleep(3);
	boost::this_thread::sleep(boost::posix_time::seconds(10));
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

