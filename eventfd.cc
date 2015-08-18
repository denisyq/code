#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <iostream>

using namespace std;
int efd = -1;
#define CHK(eval) if(eval<0){perror("CHK");	exit(-1);}
#define CHK2(ret,eval) if((ret=eval) <0){ perror("CHK2");exit(-1);}

//event_fd is better than pipe, because of uint64_t is less occupied than char buf[](pipe)
//pipe_fd[2], only one eventfd, pipe has 2 fd
void *read_thread(void* ){
    int count,ret = 0;
    uint64_t data = 0;
    int ep_fd = -1;

	CHK(efd);
	CHK2(ep_fd,epoll_create(1024));
    struct epoll_event read_event,events[10];
	read_event.events = EPOLLHUP | EPOLLERR | EPOLLIN;
	read_event.data.fd = efd;
	CHK2(ret, epoll_ctl(ep_fd, EPOLL_CTL_ADD, efd, &read_event));

	struct timeval start,end;
    while (1){
		gettimeofday(&start,NULL);
        CHK2(count, epoll_wait(ep_fd, &events[0], 10, -1));
		gettimeofday(&end,NULL);
		double timeout = (end.tv_sec-start.tv_sec)*1000+(double)(end.tv_usec-start.tv_usec)/1000;
		cout<<showpoint<<"epoll wait "<<timeout<<endl;
        if (count == 0){/* time out */
            printf("epoll wait timed out.\n");
            break;
        }
		for (int i=0; i <count; i++){
			if (events[i].events & EPOLLHUP){
				printf("epoll eventfd has epoll hup.\n");
				if(ep_fd > 0) ep_fd = -1;
			}
			else if (events[i].events & EPOLLERR){
				printf("epoll eventfd has epoll error.\n");
				if(ep_fd > 0) ep_fd = -1;
			}
			else if (events[i].events & EPOLLIN){
				int event_fd = events[i].data.fd;
				CHK2(ret, read(event_fd, &data, sizeof(data)));
				struct timeval tv;
				gettimeofday(&tv, NULL);
				cout<<"success read from efd, read "<<ret<<" bytes "<<data<<" at "<<tv.tv_sec<<" s "<<tv.tv_usec<<" us "<<endl;
			}
		}
    }
}

int main(int argc, char *argv[])
{
    pthread_t tid = 0;
    int ret = 0;
    int loop = 3;

	CHK2(efd,eventfd(0,EFD_NONBLOCK));	//eventfd init
	CHK2(ret,pthread_create(&tid, NULL, read_thread, NULL));
	while(loop--){
		uint64_t data = 4;
		CHK2(ret,write(efd, &data, sizeof(data)));
		sleep(1);
	}

    return 0;
}
