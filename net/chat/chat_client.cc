#include "chat.h"

using namespace std;

char message[BUF_SIZE];

//	fork to 2 process, IPC via PIPE
//	child process : wait for client stdin, pipe to father process
//	father process: recv server message and show && 
//	recv child process msg and send
int main(int argc, char *argv[])
{
    int client_fd, pid, pipe_fd[2], epfd;

    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr = inet_addr(SERVER_HOST);
    CHK2(client_fd,socket(PF_INET, SOCK_STREAM, 0));						//socket
    CHK(connect(client_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0);	//connect


    //flag to stop
    int continue_to_work = 1;
    CHK(pipe(pipe_fd));

    static struct epoll_event ev, events[2]; 
    ev.events = EPOLLIN | EPOLLET;
    CHK2(epfd,epoll_create(EPOLL_SIZE));
    ev.data.fd = client_fd;
    CHK(epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev));
    ev.data.fd = pipe_fd[0];	//pipe fd, pipe_fd[0]=read, pipe_fd[1]=write
    CHK(epoll_ctl(epfd, EPOLL_CTL_ADD, pipe_fd[0], &ev));

    // ..fork......
    CHK2(pid,fork());			  //when fork, pipe_fd has fork in both father/child process
    switch(pid)
    {
        case 0:                   // child process, watch stdin of user
            close(pipe_fd[0]);    // close read 
            printf("Enter 'exit' to exit\n");
            while(continue_to_work)
            {
                bzero(&message, BUF_SIZE);
                fgets(message, BUF_SIZE, stdin); //blocking here to read stdin??

                // when get exist signal,exist
                if(strncasecmp(message, CMD_EXIT, strlen(CMD_EXIT)) == 0)
                {
                    continue_to_work = 0;
                }
                else
                {            
                    CHK(write(pipe_fd[1], message, strlen(message) - 1));//write msg to pipe_fd[1]
                }
            }
            break;
        default:                 // father process, show msg from server and recv msg from child
            close(pipe_fd[1]);   // close write fd
            int epoll_events_count, res;
            while(continue_to_work) 
            {
                CHK2(epoll_events_count,epoll_wait(epfd, events, 2, EPOLL_RUN_TIMEOUT));	//maxSize=2

                for(int i = 0; i < epoll_events_count ; i++)
                {
                    bzero(&message, BUF_SIZE);
                    if(events[i].data.fd == client_fd)   //msg from server
                    {
                        CHK2(res,recv(client_fd, message, BUF_SIZE, 0));
                        if(res == 0)               //server close
                        {
                            CHK(close(client_fd));
                            continue_to_work = 0;
                        }
                        else 
                        {
                            printf("%s\n", message);	//server send your msg, just print
                        }
                    }
                    else        //msg from child process, client user input stdin
                    {
                        CHK2(res, read(events[i].data.fd, message, BUF_SIZE));
                        if(res == 0)
                        {
                            continue_to_work = 0; 
                        }
                        else
                        {
                            CHK(send(client_fd, message, BUF_SIZE, 0));	//send to server
                        }
                    }
                }
            }
    }
    if(pid){//father close
        close(pipe_fd[0]);
        close(client_fd);
    }else{	//why child not close client_fd
        close(pipe_fd[1]);
    }

    return 0;
}
