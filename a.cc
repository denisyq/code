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
class session{
public:
	session(io_service& service):socket_(service){}
	ip::tcp::socket& socket(){ return socket_;}
	void start(){
		socket_.async_read_some(buffer(data_,max_len),
			boost::bind(&session::handle_read,this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
private:
	void handle_read(const boost::system::error_code& ec, size_t bytes_transferred){
		if(!ec)
			boost::asio::async_write(socket_, boost::asio::buffer(),
				boost::bind(&session::handle_write, this,
				boost::asio::placeholders::error));
		else
			delete this;
	}
	void handle_write(const boost::system::error_code& ec){
		if(!ec)
			socket_.async_read_some(boost::asio::buffer(data_,max_len),
				boost::bind(&session::handle_read, this, boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred))
	}
	char data_[max_len]
	
};
class chat_server{
publib:
	chat_server(io_service service, endpoint& ep):
		service_(service),acceptor_(service_,ep){
			start_server();
		}	
	void start_server(){
		session* se(new session);
		acceptor_.async_accept(se->socket(),
			boost::bind(&chat_server::handle_accept, this,se, boost::asio::placeholders::error))
	}
	void handle_accept(session* se, boost::system::error_code& ec){
		if(!ec)
			se->start();
		start_server();
	}
}

class sessin{
public:
	session(io_service)
		: socket(service){}
	
}

boost::asio::dealine_timer timer(service, boost::posix_time::seconds(1));
timer.async_wait(handle);
service.run();