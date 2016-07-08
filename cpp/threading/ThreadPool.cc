#include <ThreadPool.h>
#include <boost/bind.hpp>
#include <stdio.h>

ThreadPool::ThreadPool(const string& name)
	: mutex_(),
	  notEmpty_(mutex_),
	  notFull_(mutex_),
	  name_(name),
	  maxQueueSize_(0),
	  running_(false)
{
}

ThreadPool::~ThreadPool(){
	if (running_)
		stop();
}

void ThreadPool::start(int numThreads){
	running_ = true;
	threads_.reserve(numThreads);
	for(int i=0;i<numThreads;i++){
		char id[32];
		snprintf(id, sizeof id, "%d", i+1);
		threads_.push_back(new Thread(
						boost::bind(&ThreadPool::runInThread, this),name_+id));
		threads_[i]->start();
	}
	if(numThreads == 0 && threadInitCallback_)
		threadInitCallback_();
}
void deleteThread(Thread* th){
	delete th;
}
void ThreadPool::stop(){
	{
		MutexLockGuard lock(mutex_);
		running_ = false;
		notEmpty_.notifyAll();
	}
	for_each(threads_.begin(),
			 threads_.end(),
			 boost::bind(&Thread::join, _1));
	for_each(threads_.begin(),
			 threads_.end(),
			 boost::bind(deleteThread, _1));
}

size_t ThreadPool::queueSize() const{
	MutexLockGuard lock(mutex_);
	return queue_.size();
}

void ThreadPool::run(const Task& task){
	if(threads_.empty())
		task();
	else{
		MutexLockGuard lock(mutex_);
		while(isFull())
			notFull_.wait();

		queue_.push_back(task);
		notEmpty_.notify();
	}
	{
		//MutexLockGuard lock(mutex_);
		//cout<<"task count:"<<queue_.size()<<endl;
	}
}
bool ThreadPool::isFull() const{
	return maxQueueSize_> 0 && maxQueueSize_ == queue_.size();
}
ThreadPool::Task ThreadPool::take(){
	MutexLockGuard lock(mutex_);
	while(queue_.empty() && running_)
		notEmpty_.wait();
	Task task;
	if(!queue_.empty()){
		task = queue_.front();
		queue_.pop_front();
		if(maxQueueSize_>0)
			notFull_.notify();
	}
	return task;
}


void ThreadPool::runInThread(){
	if(threadInitCallback_)
		threadInitCallback_();
	while(running_){
		Task task(take());
		if(task)
			task();
	}
}
