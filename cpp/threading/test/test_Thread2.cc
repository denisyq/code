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
 * 题目：编写一个程序，开启3个线程
 * 这3个线程的ID分别为A、B、C，
 * 每个线程将自己的ID在屏幕上打印10遍，
 * 要求输出结果必须按ABC的顺序显示；
 * 如：ABCABC….依次递推。
 ******************************/
using namespace std;
Mutex mutex;
Condition cond(mutex);
int global=0;

void foo(int index, string name){
	int n=10;//print 10 times
	MutexLockGuard lock(mutex);
	while(n-->0){
		while(global != index) cond.wait();
		cout<<name<<endl;
		++global;
		global %= 3;
		cond.notifyAll();
	}
}

int main(void){
	Thread t1(boost::bind(foo,0,"A"));
	Thread t2(boost::bind(foo,1,"B"));
	Thread t3(boost::bind(foo,2,"C"));
	t1.start();
	t2.start();
	t3.start();
	//foo(0,"");
	t1.join();
	t2.join();
	t3.join();

	return 0;
}

