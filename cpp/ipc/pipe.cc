#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
using namespace std;
#define CHK(eval) if(eval<0){perror("CHK");exit(-1);}
#define CHK2(ret,eval) if((ret=eval)<0){perror("CHK2");exit(-1);}
int main(int argc, char** argv){
	int pipe_fd[2];
	pid_t id;
	char data[100];
	char welcome[]="welcome";
	bzero(data,sizeof(data));

	CHK(pipe(pipe_fd));
	CHK2(id,fork());
	switch(id){
		case 0:
			cout<<"Child process!"<<endl;
			close(pipe_fd[1]);
			CHK(read(pipe_fd[0],data,sizeof(data)));//blocking here, if father not write complete
			cout<<"child read:"<<data<<endl;
			exit(1);
		default:
			cout<<"Father:child id:"<<id<<endl;
			close(pipe_fd[0]);
			CHK(write(pipe_fd[1],welcome,sizeof(welcome)));
			cout<<"father write done"<<endl;

	}
	exit(1);
	return 0;
}
