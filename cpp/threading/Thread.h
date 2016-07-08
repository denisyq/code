//Author: Dennis LU
#ifndef DELU_BASE_THREAD_H
#define DELU_BASE_THREAD_H

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <pthread.h>
#include <string>
#include <stdint.h>
#include "Atomic.h"
using std::string;

class Thread : boost::noncopyable{
public:
	typedef boost::function<void ()> ThreadFunc;
	Thread(const ThreadFunc&, const string& name=string());
	~Thread();
	void start();
	int join();
	bool started() const{ return started_; }
	pid_t tid() const;
	const string& name() const { return name_; }
	static int numCreated() { return numCreated_.get(); }

private:
	bool started_;
	bool joined_;
	pthread_t pthreadId_;
	boost::shared_ptr<pid_t> tid_;
	ThreadFunc func_;
	string name_;
	void setThreadName();
	static AtomicInt32 numCreated_;
};
#endif
