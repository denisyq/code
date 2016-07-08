#include <iostream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <deque>
#include <string>
#include <list>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <Thread.h>
#include <boost/bind.hpp>
#include <sys/syscall.h>
#include <ThreadPool.h>
#include <boost/static_assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/function.hpp>
#include <mutex.h>
#include <stdlib.h>
#include <countDownLatch.h>
/******************************
 * 子线程循环 10 次，接着主线程循环 100 次，
 * 接着又回到子线程循环 10 次，接着再回到主线程又循环 100 次，
 * 如此循环50次，试写出代码
 ******************************/
 
 //compile: ccbuild a.cc Thread.cc

using namespace std;
Mutex mutex;
Condition cond(mutex);
int global=10;

void loop(int num){
	for(int i=1;i<=50;i++){
		MutexLockGuard lock(mutex);
		while(global != num) cond.wait();
		
		int tmp = global;
		while(tmp-->0)
			cout<<i<< " "<<tmp<<endl;
		global = (global == 10)? 100:10;
		//if(global == 10) global=100;
		//else global =10;
		cond.notify();
	}
}

int main(void){
	Thread t1(boost::bind(loop,10),"child");
	t1.start();
	loop(100);
	t1.join();


	return 0;
}

