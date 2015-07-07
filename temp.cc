#include <iostream>
#include <cstdlib>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <boost/bind.hpp>
using namespace std;
void onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime){
	muduo::string msg(buf->retrieveAllAsString());
	conn->send(msg);
}
int main(int argc, char** argv){
	muduo::net::EventLoop loop;
	muduo::net::TcpServer server(&loop,InetAddress(1027);"echo server");
	server.setMessageCallback(onMessage);
	server.start();
	loop.loop();
    return 0;
}
