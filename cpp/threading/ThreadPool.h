#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <mutex.h>
#include <Thread.h>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <deque>
#include <vector>
//using namespace std;
class ThreadPool : boost::noncopyable{
public:
	typedef boost::function<void ()> Task;
	ThreadPool(const string& name = string("ThreadPool"));
	~ThreadPool();

	void setMaxQueueSize(int maxSize) { maxQueueSize_ = maxSize;}
	void setThreadInitCallback(const Task& cb) { threadInitCallback_ = cb; }
	void start(int numThreads);
	void stop();

	const string& name() const { return name_; }
	size_t queueSize() const;

	void run(const Task& f);

private:
	bool isFull() const;
	void runInThread();
	Task take();
	mutable Mutex mutex_;
	Condition notEmpty_;
	Condition notFull_;
	string name_;
	Task threadInitCallback_;
	vector<Thread*> threads_;
	deque<Task> queue_;
	size_t maxQueueSize_;
	bool running_;

};
#endif
