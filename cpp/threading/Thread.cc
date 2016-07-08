#include <iostream>
#include <Thread.h>
#include <boost/static_assert.hpp>
#include <boost/weak_ptr.hpp>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/prctl.h>
namespace detail{

	pid_t gettid(){
		return static_cast<pid_t>(::syscall(SYS_gettid));
	}
	struct ThreadData{
		typedef boost::function<void ()> ThreadFunc;
		ThreadFunc func_;
		string name_;
		boost::weak_ptr<pid_t> wkTid_;
	
		ThreadData(const ThreadFunc& func,
					const string& name,
					const boost::shared_ptr<pid_t>& tid)
		: func_(func),
		  name_(name),
		  wkTid_(tid)
		{}
	
		void runInThread(){
			pid_t tid = gettid();
			boost::shared_ptr<pid_t> ptr(wkTid_.lock());
			if(ptr){//make sure shared_ptr pass through, not NULL
				*ptr = tid;
				ptr.reset();
			}
			func_();
		}
	};
	//pid_t tid =0;
	//string& name = "";
	
	void* startThread(void* obj){
		ThreadData* data = static_cast<ThreadData*>(obj);
		data->runInThread();
		//std::cout<<"in ThreadData: startThread: name:"<<data->name_<<std::endl;
		//std::cout<<"in ThreadData: startThread: tid :"<<data->tid_<<std::endl;
		delete data;
		return NULL;
	}
}//namespace detail

AtomicInt32 Thread::numCreated_;
Thread::Thread(const ThreadFunc& func, const string& name)
	:started_(false),
	joined_(false),
	pthreadId_(0),
	tid_(new pid_t(0)),
	func_(func),
	name_(name){
		setThreadName();
		tid();
}

Thread::~Thread(){
	if(started_ && !joined_)
		pthread_detach(pthreadId_);
}

void Thread::setThreadName(){
	int num = numCreated_.incrementAndGet();
	if(name_.empty()){
		char buf[32];
		snprintf(buf, sizeof buf, "Thread%d", num);
		name_ = buf;
	}
}
pid_t Thread::tid() const {
	//*tid_ = static_cast<pid_t>(syscall(SYS_gettid));
	return *tid_;
}
void Thread::start(){
	assert(!started_);
	started_ = true;
	detail::ThreadData* data = new detail::ThreadData(func_,name_,tid_);
	if(pthread_create(&pthreadId_,NULL, &detail::startThread, data)){
		started_ =  false;
		delete data;
		//LOG_OUT_ERROR
	}
}

int Thread::join(){
	assert(started_);
	assert(!joined_);
	joined_ = true;
	return pthread_join(pthreadId_, NULL);
}
