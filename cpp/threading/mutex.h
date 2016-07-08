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
	friend class Condition;
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
