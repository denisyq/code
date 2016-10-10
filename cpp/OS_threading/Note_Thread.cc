/**************
* OS::threading
***************/
> #include <pthread.h>

# pthread_t
1. pthread_self()
pthread_t pthread_self()

2. pthread_equal(pthread_t, pthread_t)
pthread_t tid = pthread_self()
pthread_equal(pthread_self, tid)


# 创建
	- int pthread_create(pthread_t*, *attr, void*(void*), void* arg)
		void* foo(void*);
		pthread_create(&tid, NULL, foo, NULL) == 0 //OK
	
# 主动销毁自己
	- pthread_exit()

# 主动分离自己，让系统回收自己
	- pthread_detach()

# 等别的线程结束
	- pthread_join(pthread_t)//blocking IO, wait until it done

# 终止别的线程
	- pthread_cancel(pthread_t)//去终止别的线程，别的线程要可cancel
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
		//这个是自己调用的，这样别人才可以把我给cancel掉
	
# threading attributes
	- 内容蛮多的，接触少

/**********
* mutex
***********/
- pthread_mutex_init()
- pthread_mutex_destroy()
- pthread_mutex_lock()
- pthread_mutex_unlock()
- pthread_mutex_trylock()

/************
* condition
*************/
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
int pthread_cond_destory(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t *cond,pthread_mutex_t *mutex, const timespec *abstime);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond)

//mutex and condition has existing code "mutex.h" in my github
#ifndef MUTEX_H
#define MUTEX_H

#include <iostream>
#include <stdio.h>
#include <pthread.h>
using namespace std;

/* Note:2015/06/24, the first time debug class Mutex/MutexLockGuard/Condition and find it is not easy to write correctly
 * all at one time even I have @chenshuo muduo library open source /muduo/base/Mutex.h 
 * One bug when write MutexLockGuard constructor, should use Mutex& mutex in pass-in parameter, I used Mutex mutex(line 41)
 * that cause when you call MutexLockGuard lock(mutex), we got a temp mutex copy and is not the mutex itself.
 * The same to Condition cons and both MutexLockGuard/Condition private variable.
 */
class Mutex{
public:
	Mutex(){
		pthread_mutex_init(&mutex_,NULL);
	}
	~Mutex(){
		pthread_mutex_destroy(&mutex_);
	}
	void lock(void){
		pthread_mutex_lock(&mutex_);
	}
	void unlock(void){
		pthread_mutex_unlock(&mutex_);
	}
	pthread_mutex_t* getMutex(){
		return &mutex_;
	}

private:
	//friend class Condition;
	pthread_mutex_t mutex_;
};


class MutexLockGuard{
public:
	explicit MutexLockGuard(Mutex& mutex):mutex_(mutex){
		mutex_.lock();
	}
	~MutexLockGuard(){
		mutex_.unlock();
	}
private:
	Mutex& mutex_;
};



class Condition{
public:
	explicit Condition(Mutex& mutex):mutex_(mutex){
		pthread_cond_init(&cond_,NULL);
	}
	~Condition(){
		pthread_cond_destroy(&cond_);
	}
	void wait(){
		pthread_cond_wait(&cond_,mutex_.getMutex());
	}
	void notify(){
		pthread_cond_signal(&cond_);
	}
	void notifyAll(){
		pthread_cond_broadcast(&cond_);
	}
	pthread_cond_t* getCondition(){
		return &cond_;
	}
private:	
	Mutex& mutex_;
	pthread_cond_t cond_;
};
#endif


