#include <muduo/net/TcpServer.h>
using namespace std;

class EchoServer{
public:
	EchoServer(muduo::net::Eventloop* loop,
				const muduo::net::InetAddress& listenAddr);
	void start();
private:
	void onConnection(const muduo::net::TcpConnectionPtr& conn);
	void onMessage(const muduo::net::TcpConnectionPtr& conn,
					muduo::net::Buffer* buf,
					muduo::Timestamp time);
	muduo::net::EventLoop* loop_;
	muduo::net::TcpServer server_;
};


#if 0
int main(int argc, char** argv){
	LOG_INFO << "pid = " << getpid();
	muduo::net::EventLoop loop;
	muduo::net::InetAddress listenAddr(2007);
	EchoServer server(&loop, listenAddr);
	server.start();
	loop.loop();
    return 0;
}
#endif
