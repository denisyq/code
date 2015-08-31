#include "chat.h"

using namespace std;

char msg_out[BUF_SIZE];
char msg_in[BUF_SIZE];

int main(int argc, char *argv[])
{
    int client_fd, pid, epfd;

    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_HOST);
    CHK2(client_fd,socket(PF_INET, SOCK_STREAM, 0));					//socket

	fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFL, 0)|O_NONBLOCK);
	// if stdin is blocking, client will always wait for input done, then could show other client's msg
	fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL, 0)|O_NONBLOCK); 

    int ret = connect(client_fd, (struct sockaddr *)&addr, sizeof(addr));	//connect
	if(errno == EINPROGRESS) cout<<"connect nonblocking"<<endl;


    //flag to stop
    int continue_to_work = 1;

    static struct epoll_event ev, events[2]; 
    ev.events = EPOLLIN | EPOLLOUT | EPOLLERR;
    CHK2(epfd,epoll_create(EPOLL_SIZE));
    ev.data.fd = client_fd;
    CHK(epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev));
    ev.data.fd = STDIN_FILENO;
    CHK(epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev));

	while(continue_to_work){
		int epoll_events_cnt,res;	
		CHK2(epoll_events_cnt,epoll_wait(epfd,events,3,EPOLL_RUN_TIMEOUT));
		for(int i=0;i<epoll_events_cnt;i++){
			if(events[i].data.fd == client_fd){
				bzero(msg_out,BUF_SIZE);
				int error;
				socklen_t len=static_cast<socklen_t>(sizeof error);
				CHK(getsockopt(client_fd, SOL_SOCKET, SO_ERROR, &error, &len));//make sure nonBlocking connect works now
				res=recv(client_fd,msg_out,BUF_SIZE,0);
				if(res < 0){
					cout<<"recv nothing "<<errno<<endl;
				}
				else if(res == 0){
					cout<<"server close"<<endl;
					continue_to_work = 0;	
				}else{
					cout<<msg_out<<endl;		
				}
			}
			else if(events[i].data.fd == STDIN_FILENO){
				bzero(msg_in,BUF_SIZE);
				res=read(STDIN_FILENO, msg_in, BUF_SIZE);//did not include res<0 scenario
				if(res == 0){
					cout<<" time out "<<endl;
					continue_to_work = 0;
				}else{
					if(res >= 1)
						CHK2(res,send(client_fd,msg_in,BUF_SIZE,0));
				}
			}
		}
	}
	close(client_fd);
}
