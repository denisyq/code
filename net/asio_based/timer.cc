#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <boost/thread/thread.hpp>
using namespace std;
using namespace boost::asio;

void handle(const boost::system::error_code ec){
	cout<<"timer run out"<<endl;
}
void oneMore(void){
	cout<<"1st to register to asyncRecall"<<endl;
}
int main(int argc, char** argv){
	io_service service;	
	io_service::work iwork(service);
	service.post(oneMore);	//register and wait for async call
	deadline_timer timer(service, boost::posix_time::seconds(2));
#if 0
	// sync mode
	// timer wait equals to sleep(2), it is blocking operation
	timer.wait();
	cout<<"wait n sec and then print"<<endl;
#else
	// async mode
	timer.async_wait(handle);
	cout<<"print me first"<<endl;
	boost::this_thread::sleep(boost::posix_time::seconds(5));	
	service.run();	//if forget this, async function handle will not be called.
#endif
	return 0;	
}
