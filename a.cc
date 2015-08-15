#include <sys/time.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

int main(int argc, char** argv){
	struct timeval tv1,tv2;
	gettimeofday(&tv1,NULL);
	sleep(2);
	gettimeofday(&tv2,NULL);
	cout<<showpoint<<(double)(tv2.tv_sec-tv1.tv_sec)<<endl;
}
