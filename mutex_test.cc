#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <mutex.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/syscall.h>
using namespace std;


/*
class Task{
public:
	Task(int n):size_(n){}
	//int take(void);
	//void put(int data);

private:
	int size_;
	Mutex mutex_;
	//Condition cond_(mutex_);
};
int Task::take(void){
	MutexLockGuard lock(mutex_);

} 
*/
pid_t gettid(){
	return syscall(SYS_gettid);
}
Mutex mutex;
Condition cond(mutex);
int i=0;
void* func(void*){
	cout<<"thread 2 tid "<<gettid()<<endl;
	{
		MutexLockGuard lock(mutex);
		while(i<10){
			cout<<"thread 2 is waiting"<<endl;
			cond.wait();
		}
		//do sth
		assert(i>=10);
		cout<<"i==10 and then reset"<<endl;
		i=0;
	}
	cout<<"pthread 2 pthread_self "<<pthread_self()<<endl;
}
int main(int argc, char** argv){
	pthread_t pid;
	pthread_create(&pid,NULL,func,NULL);
	cout<<"pid "<<pid<<endl;

	{
		MutexLockGuard lock(mutex);
		while(i!=10){
			i++;
			cout<<"thread 1 is adding i=="<<i<<endl;
		}
		cout<<"thread 1 notify"<<endl;
		cond.notify();//do not move in MutexLockGuard scope
		//pthread_cond_signal(cond.getCondition());
	}

	cout<<"thread 1 is waiting to join"<<endl;
	pthread_join(pid,NULL);
	
	return 0;
}












