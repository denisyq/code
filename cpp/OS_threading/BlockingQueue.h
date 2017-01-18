#ifndef _BLOCKING_QUEUE_H
#define _BLOCKING_QUEUE_H
#include <vector>
#include <deque>
#include <mutex.h>
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <assert.h>

template<typename T>
class BlockingQueue : boost::noncopyable{
public:
	explicit BlockingQueue(int max_size):
						capacity_(max_size),
						mutex_(),
						notEmpty_(mutex_),
						notFull_(mutex_){}

	void put(const T& t){
		MutexLockGuard lock(mutex_);
		while(capacity_ == task_.size()){
			notFull_.wait();	
		}
		task_.push_back(t);
		notEmpty_.notify();
	}

	T take(){
		MutexLockGuard lock(mutex_);
		while(task_.empty()){
			notEmpty_.wait();
		}
		assert(!task_.empty());
		T t(task_.front());
		task_.pop_front();
		notFull_.notify();
		return t;
	}
	size_t size() const{
		MutexLockGuard lock(mutex_);
		return task_.size();
	}
private:
	int capacity_;
	mutable Mutex mutex_;
	Condition notEmpty_;
	Condition notFull_;
	deque<T> task_;
};


#endif
