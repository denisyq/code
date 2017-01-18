#ifndef COUNT_DOWN_LATCH_H
#define COUNT_DOWN_LATCH_H
#include <mutex.h>
#include <stdlib.h>
#include <boost/noncopyable.hpp>

class CountDownLatch : boost::noncopyable{
public:
	CountDownLatch(int num): cond_(mutex_),count_(num){}
	void wait(){
		MutexLockGuard lock(mutex_);
		while( count_ > 0){
			cond_.wait();
		}
	}
	void countDown(){
		MutexLockGuard lock(mutex_);
		count_--;
		if( count_ == 0){
			cond_.notifyAll();
		}
	}
private:
	Mutex mutex_;
	Condition cond_;
	int count_;
};
#endif

/**************** 
 * how to use it
 ****************/
 // in main thread, CountDownLatch latch(2); pass latch to other threads
 // then in other threads' runInThread(), latch->countDown()
 // main thread use latch.wait(), this api is blocking api
 // if other threads count down to 0, main thread will be restored.
 // 1.主线程用latch.wait() 堵塞等待，另外线程做完事情latch.countDown()，
 // 相当于notify,然后唤醒主线程的wait
 // 一般用于主线程等子线程的初始化完成
 // 2.主线程发起子线程，子线程等主线程完成后，再由主线程通知其开始执行
 // 类似于主线程向子线程发起 起跑 命令

 /*
 54 void printString(CountDownLatch* latch){
 55     cout<<"in other thread, print String " <<endl;
 56     latch->countDown();
 57 }
 58 int main(void){
 59     CountDownLatch latch(1);
 60     Thread t1(boost::bind(printString, &latch),"thread-1");
 61     cout<<"main thread wait for latch"<<endl;
 62     t1.start();
 63     latch.wait();
 64     t1.join();
 65     cout<<"main thread is done"<<endl;
*/
