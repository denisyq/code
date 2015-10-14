#include <boost/asio.hpp>  
#include <boost/bind.hpp>  
#include <boost/shared_ptr.hpp>  
#include <boost/enable_shared_from_this.hpp>  
#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <stdlib.h>
  
using namespace std;  
  
  
class session: public boost::enable_shared_from_this<session>   
{  
public:  
    session(boost::asio::io_service &io_service);  
    bool started_;  
    bool started() const;  
    void start();  
    void stop();  
      
    void start_send();    
  
      
    boost::asio::ip::tcp::socket &socket();  
    int heartbeat_count_;  
  
       
private:  
    boost::asio::ip::tcp::socket socket_;  
    boost::asio::streambuf sbuf_;  
  
  
    enum{max_msg=4096};   
    unsigned char read_buffer[max_msg];  
    unsigned char write_buffer[max_msg];  
  
    std::size_t check_frame(const boost::system::error_code &ec, std::size_t bytes_transferred);//....  
    void parse_frame(const boost::system::error_code &ec, std::size_t bytes_transferred);//....  
  
  
    void receive_handler(const boost::system::error_code &ec, std::size_t bytes_transferred);  
    void send_handler(const boost::system::error_code &ec);  
};  
  
typedef boost::shared_ptr<session> session_ptr;

session::session(boost::asio::io_service &io_service): socket_(io_service)  
{   
  
}   
  
bool session::started() const  
{  
    return started_;  
}  
  
void session::start() {  
started_=true;  
bzero(read_buffer,sizeof(read_buffer));
bzero(write_buffer,sizeof(write_buffer));
socket_.async_receive(boost::asio::buffer(read_buffer),   
    boost::bind(&session::receive_handler,  
    shared_from_this(),  
    boost::asio::placeholders::error,  
    boost::asio::placeholders::bytes_transferred));  
}   
  
std::size_t session::check_frame(const boost::system::error_code &ec, std::size_t bytes_transferred)//..  
{  
    return 1;  
}  
void session::parse_frame(const boost::system::error_code &ec, std::size_t bytes_transferred)//..  
{  
    if (!ec)  
    {  
  
        socket_.async_receive(boost::asio::buffer(read_buffer),   
            boost::bind(&session::receive_handler,  
            shared_from_this(),  
            boost::asio::placeholders::error,  
            boost::asio::placeholders::bytes_transferred));  
    }  
}  
  
void session::receive_handler(const boost::system::error_code &ec, std::size_t bytes_transferred)   
{   
    if (ec)return;  
    if (!started())return;  
	cout<<"server receive "<<bytes_transferred<<" bytes: "<<read_buffer<<endl;  
	start_send();
    {   
  
	bzero(read_buffer,sizeof(read_buffer));
	bzero(write_buffer,sizeof(write_buffer));
        boost::asio::async_read(socket_,boost::asio::buffer(read_buffer),  
            boost::bind(&session::check_frame,  
            shared_from_this(), boost::asio::placeholders::error,  
            bytes_transferred),  
  
            boost::bind(&session::parse_frame,  
            shared_from_this(),  
            boost::asio::placeholders::error,  
            bytes_transferred));  
  
  
  
        socket_.async_receive(boost::asio::buffer(read_buffer),   
            boost::bind(&session::receive_handler,  
            shared_from_this(),  
            boost::asio::placeholders::error,  
            boost::asio::placeholders::bytes_transferred));  
    }   
  
}  
  
void session::stop()  
{  
  
    if (!started_) return;  
    started_=false;  
  
    socket_.close();  
}  
  
  
void session::start_send()  
{  
    //test  
    string tmp("1123456789abcdefghijklmnopqrstuvwxyz");
    std::copy(tmp.begin(),tmp.end(),write_buffer);  
    socket_.async_write_some(boost::asio::buffer(write_buffer,20),boost::bind(&session::send_handler,  
        shared_from_this(),  
        boost::asio::placeholders::error));  
  
  
}  
  
void session::send_handler(const boost::system::error_code &ec)  
{  
    if (!ec)   
    {   
  
    }  
    else  
    {  
        //........   
  
    }  
}  
boost::asio::ip::tcp::socket &session::socket() {  
    return socket_;  
}



class channel  
{  
public:  
    channel(boost::asio::io_service &io_service, boost::asio::ip::tcp::endpoint &endpoint);   
    void handle_accept(session_ptr new_session, const boost::system::error_code& error);  
    void run();  
  
private:  
    boost::asio::io_service &io_service_;  
    boost::asio::ip::tcp::acceptor acceptor_;  
  
public:  
    typedef boost::system::error_code error_code;  
};


channel::channel(boost::asio::io_service &io_service, boost::asio::ip::tcp::endpoint &endpoint)  
    : io_service_(io_service), acceptor_(io_service, endpoint)  
{  
    session_ptr new_session(new session(io_service_));  
  
    //we need to monitor for the client list change event ,a new client connects or one client gets disconnected,  
    // and notify all clients when this happens.Thus,we need to keep an array of clients,  
    //sessions.push_back(new_session);  
  
    //each new client connection will then trigger another asynchronous wait  
    acceptor_.async_accept(new_session->socket(),  
        boost::bind(&channel::handle_accept,  
        this,  
        new_session,  
        boost::asio::placeholders::error));  
}  
  
void channel::handle_accept(session_ptr new_session, const boost::system::error_code& error) {  
    if (error) {  
        return;  
    }  
  
     
    new_session->start();  
	//wait for new comer 
    session_ptr next_session(new session(io_service_));  
    acceptor_.async_accept(next_session->socket(),  
        boost::bind(&channel::handle_accept,  
        this,  
        next_session,  
        boost::asio::placeholders::error));  
}  
  
void channel::run() {  
  
        boost::thread t(boost::bind(&boost::asio::io_service::run,boost::ref(io_service_)));  
        //boost::thread t(boost::bind(&boost::asio::io_service::run,this,io_service_));  
  
  
        //int thread_count=(std::max)(static_cast<int>(boost::thread::hardware_concurrency()),1);  
        //boost::thread_group tg;  
        //for (int i=0;i<thread_count;i++)  
        //{  
        //  tg.create_thread(boost::bind(&boost::asio::io_service::run,boost::ref(io_service_)));  
        //  boost::this_thread::sleep(boost::posix_time::seconds(5));  
        //}  
      
}
int main(int argc, char** argv){
	boost::asio::io_service g_io_service;  
	boost::asio::io_service::work g_work(g_io_service);  
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(),1234);  
	channel g_c(g_io_service, endpoint);  
	g_io_service.run();
	//g_c.run(); 
}   
