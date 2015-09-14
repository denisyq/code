#include "chat.h"
using namespace std;

list<int> clients_list;
int setnonblocking(int sockfd){
	fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK);
	return 0;
}
int main(int argc, char **argv){
	//socket
	int listener;   //listen socket
    struct sockaddr_in addr, their_addr;  
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_HOST);
    socklen_t socklen = sizeof(struct sockaddr_in);

    CHK2(listener, socket(AF_INET, SOCK_STREAM, 0));             //socket
    setnonblocking(listener);                                    //set nonblocking
	int val = 1;												 //reuse addr/port in time_wait
	CHK(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)));
    CHK(bind(listener, (struct sockaddr *)&addr, sizeof(addr))); //bind
    CHK(listen(listener, SOMAXCONN));                            //listen
	
	//epoll 
    static struct epoll_event ev, events[EPOLL_SIZE];
    ev.events = EPOLLIN | EPOLLET; //event set to EPOLLIN and ET mode
    int epfd,epoll_events_count;   //epoll fd

    CHK2(epfd,epoll_create(EPOLL_SIZE));                         //epoll create
    ev.data.fd = listener;
    CHK(epoll_ctl(epfd, EPOLL_CTL_ADD, listener, &ev));			 //epoll ctl
   
	//loop - epoll_wait
    char message[BUF_SIZE];
    clock_t tStart;  //the time code runs
    int client, res;
	while(1){
        CHK2(epoll_events_count,epoll_wait(epfd, events, EPOLL_SIZE, EPOLL_RUN_TIMEOUT)); //epoll wait
        tStart = clock();
        for(int i = 0; i < epoll_events_count ; i++){
            if(events[i].data.fd == listener){                    //new connection
                CHK2(client,accept(listener, (struct sockaddr *) &their_addr, &socklen)); //accept
                setnonblocking(client);
                ev.data.fd = client;
                CHK(epoll_ctl(epfd, EPOLL_CTL_ADD, client, &ev));

                clients_list.push_back(client);                  //add new connection into list
                bzero(message, BUF_SIZE);
                res = sprintf(message, STR_WELCOME, client);
                CHK2(res, send(client, message, BUF_SIZE, 0));	 //send

            }else{
                CHK2(res,handle_message(events[i].data.fd)); 	 //epoll_ctl does not change event type, still can receive msg
            }
        }
        printf("Statistics: %d events handled at: %.2f second(s)\n", epoll_events_count, (double)(clock() - tStart)/CLOCKS_PER_SEC);
    }	
	close(listener);
    close(epfd);

    return 0;
}
int handle_message(int client)  
{
    char buf[BUF_SIZE], message[BUF_SIZE];
    bzero(buf, BUF_SIZE);
    bzero(message, BUF_SIZE);

    int len;

    CHK2(len,recv(client, buf, BUF_SIZE, 0));  //receive msg

    if(len == 0){   //client error/close, close socket and remove from list
        CHK(close(client));
        clients_list.remove(client);
    }else{          //client msg is good
        if(clients_list.size() == 1){
            CHK(send(client, STR_NOONE_CONNECTED, strlen(STR_NOONE_CONNECTED), 0));//one client
            return len;
        }
		//TODO rcv message has header to who, no need to send msg to all 
        sprintf(message, STR_MESSAGE, client, buf);
        list<int>::iterator it;
        for(it = clients_list.begin(); it != clients_list.end(); it++)
        {
           if(*it != client)
           { 
                CHK(send(*it, message, BUF_SIZE, 0));
           }
        }
    }

    return len;
}
