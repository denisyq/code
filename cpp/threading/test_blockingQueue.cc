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
#include <boost/static_assert.hpp>
#include <boost/function.hpp>
#include <mutex.h>
#include <stdlib.h>
#include <BlockingQueue.h>
#include <sstream>
using namespace std;

Mutex mutex;//for cout 
BlockingQueue<string> queue(10);

void foo(void){
	while(1){
		string out(queue.take());
		MutexLockGuard lock(mutex);
		cout<<out<<endl;
	}
}

int main(void){
	Thread t1(foo);
	Thread t2(foo);
	t1.start();
	t2.start();
	for(int i=1;i<=100;i++){
		stringstream ss;
		string tmp;
		ss<<i;
		ss>>tmp;
		string s("***********"+tmp);
		queue.put(s);
	}
	t1.join();
	t2.join();


	return 0;
}

