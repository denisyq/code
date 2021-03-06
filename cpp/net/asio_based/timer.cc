#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/ref.hpp>
using namespace std;
using namespace boost::asio;

//#define NUM1 0
#define NUM2 0

/**********************************/
//simple timer
/**********************************/
#ifdef NUM1
void handleTimeout(const boost::system::error_code ec){
	cout<<"timer run out"<<endl;
}
void firstCallback(void){
	cout<<"1st to add into service run"<<endl;
}
int main(int argc, char** argv){
	io_service service;	
	io_service::work iwork(service);
	service.post(firstCallback);	//register and wait for async call
	deadline_timer timer(service, boost::posix_time::seconds(2));
#if 0
	// sync mode
	// timer wait equals to sleep(2), it is blocking operation
	timer.wait();
	cout<<"wait n sec and then print"<<endl;
#else
	// async mode
	timer.async_wait(handleTimeout);
	boost::this_thread::sleep(boost::posix_time::seconds(5));	
	service.run();	//if forget this, async function handle will not be called.
#endif
	return 0;	
}
#endif
/**********************************/
//deadline_timer API
//--deadline_timer timer(io_service)
//--timer.expires_from_now(posix_time)
//--timer.expires_at();
//--timer.async_wait(handle)
//--timer.cancel()
/**********************************/
#ifdef NUM2
void handleTimeout(const boost::system::error_code ec){
	// ec is important to check 1. timeout 2.cancelled
	if(ec != boost::asio::error::operation_aborted)
		cout<<"timer run out"<<endl;
	else
		cout<<"timer cancelled"<<endl;
}
int main(int argc, char** argv){
	io_service service;	
	io_service::work iwork(service);
	deadline_timer timer(service);

	timer.expires_from_now(boost::posix_time::seconds(5)); //start timing
	boost::this_thread::sleep(boost::posix_time::seconds(2));
	cout<<"sleep done and cancel"<<endl;	
	timer.async_wait(boost::bind(&handleTimeout,boost::asio::placeholders::error));
	size_t ret = timer.cancel(); //cancel how many async tasks
	service.run();	//if forget this, async function handle will not be called.
	return 0;	
}
#endif
