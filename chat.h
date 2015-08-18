
#ifndef CHAT_H_
#define CHAT_H_

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <list>
#include <string.h>
#include <iostream>

#define BUF_SIZE 1024 //buffer
#define SERVER_PORT 8888 //listen port
#define SERVER_HOST "127.0.0.1" //server IP
#define EPOLL_RUN_TIMEOUT -1 //epoll timeout
#define EPOLL_SIZE 10000 //epoll size

#define STR_WELCOME "Welcome to seChat! You ID is: Client #%d"
#define STR_MESSAGE "Client #%d>> %s"
#define STR_NOONE_CONNECTED "Noone connected to server except you!"
#define CMD_EXIT "EXIT"

//two useful macro
#define CHK(eval) if(eval < 0){perror("CHK eval"); exit(-1);}
#define CHK2(res, eval) if((res = eval) < 0){perror("CHK2 eval"); exit(-1);}

int setnonblocking(int sockfd);
int handle_message(int new_fd);

#endif
