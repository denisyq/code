#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace std;
using namespace boost::asio;
using boost::system::error_code;
using ip::tcp;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

class clientSession : public boost::enable_shared_from_this<clientSession>{
public:
	clientSession(io_service& service):
	
};


int main(int argc, char** argv){
	return 0;
}




















#if 0


	io_service service;
	ip::tcp::endpoint ep(ip::tcp::v4(),9999);
	ip::tcp::acceptor acc(service, ep);
void accept_handler(socket_ptr sock, error_code ec);

void start_accept(void){
	socket_ptr sock(new ip::tcp::socket(service));
	acc.async_accept(*sock, boost::bind(accept_handler,sock,_1));
}
void write_handler(string_ptr str, error_code ec, size_t bytes){
	if(ec)
		cout<<"send error!!" <<endl;
	else
		cout<<*str<<" ##send "<<bytes<<" bytes"<<endl;
}
void accept_handler(socket_ptr sock, error_code ec){
	if(ec) return;
	start_accept();
	//handle
		cout<<"hello new client"<<endl;	
		string_ptr str(new string("hello clinet!"));
		cout<<sock->remote_endpoint().address()<<endl;
		sock->async_write_some(buffer(*str),boost::bind(write_handler,str,_1,_2));
		sleep(10);
		while(1){
		}

}
int main(int argc, char** argv){
	start_accept();
	service.run();
	return 0;
}
#endif
#if 0
class echoService{
public:
	echoService(io_service &service):m_ioservice(service),m_acceptor(
			service, ip::tcp::endpoint(ip::tcp::v4(),9999)){};
	void start(){
		socket_ptr socket(new ip::tcp::socket(m_ioservice));
		m_acceptor.async_accept(*socket, boost::bind(&echoService::accept_handler,this,socket,_1));
	}

	void accept_handler(socket_ptr socket, error_code ec){
		if(ec) return;
	}


private:
	io_service &m_ioservice;
	ip::tcp::acceptor m_acceptor;
};
#endif
