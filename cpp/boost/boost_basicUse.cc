/******************************
  单一实例 noncopyable
  **************************/
#include <boost/noncopyable.hpp>
class FOO : boost::noncopyable {

};

class noncopyable{
protected:
  noncopyable(){}
  ~noncopyable(){}
private:
  noncopyable(const noncopyable&);
  noncopyable& operator=(const noncopyable&);
};



/***************************************************/
/* shared_ptr */
#include <boost/shared_ptr.hpp>
boost::shared_ptr<int> sp(new int(4));

/* weak_ptr */
#include <boost/weak_ptr.hpp>
boost::weak_ptr<int> wkSp;

1. boost::shared_ptr　是否线程安全？
http://blog.csdn.net/solstice/article/details/8547547
基本不是线程安全的，多线程同时读取一个shared_ptr需要加锁
boost::shared_ptr<int> ptr1;
boost::shared_ptr<int> ptr2(new int);
shared_ptr里面有两个指针要管理，一个是指向内容的int，一个是指向cnt。第一个指针（指向内容）不能原子化，第二个是原子化增加
ptr1 = ptr2;这个操作中，也是需要分成两步来做，先把指向内容的指针赋值，再赋值指向cnt的指针，同时cnt++
在步骤一完成后，如果ptr2发生改变，则ptr1也可能变成野指针，所以需要加锁。

2. weak_ptr 弱引用，不控制生命周期，只想知道对象是否还活着。可以升级成强引用，失败了就返回空的shared_ptr. 

3. shared_ptr/weak_ptr　的线程安全性级别和std::string 和STL容器一致。




/***************************************************/
/* ptr_container */
#include <boost/ptr_container/ptr_vector.hpp>
//in directory boost/ptr_container/*, we have \
ptr_vector.hpp \
ptr_deque.hpp \
ptr_inserter.hpp \
ptr_list.hpp \
ptr_map.hpp \
ptr_set.hpp \
ptr_unordered_map.hpp \
ptr_unordered_set.hpp

// ptr_vector stored pointer, no need to delete the pointer's memory allocated
// if vector stored pointer, we need to delete pointer's memory allocated manually.
boost::ptr_vector<int> sp;
sp.push_back(new int(1));
sp.push_back(new int(2));
cout<<sp.back()<<endl;

boost::ptr_set<int> ps;
ps.insert(new int(3));
ps.insert(new int(4));
cout<<*ps.begin()<<endl;






/***************************************************/
/* boost static assert */
#include <boost/static_assert.hpp>
BOOST_STATIC_ASSERT(2>=1);
//this assert used for check in compile state \
false will cause compilation stop
//std::assert() used for running state \
false will cause system fault, compilation will pass.

//BOOST_ASSERT similar to assert
#include <boost/assert.hpp>
BOOST_ASSERT(2>1);
BOOST_ASSERT(2>1,"boost assert");
////////////////////////////////////////////////////////











/* boost::string */
#include <boost/algorithm/string/case_conv.hpp>
std::string str_lower = boost::to_lower_copy(str1)
std::string str_upper = boost::to_upper_copy(str1)

boost::to_lower(str1);
boost::to_upper(str1);
//boost has other api, but python is better to handle string
////////////////////////////////////////////////////////////





/*********
 function 
 *********/
#include <boost/function.hpp>
typedef boost::function<void ()> ThreadFunc;
ThreadFunc func_;




/********************** 
  Boost::bind
 **********************/
#include <boost/bind.hpp>

//boost::bind - usage 1
void print(int i, int j){
	cout<<"i "<<i <<" j "<<j<<'\n';
}
//usage 1
int i=2,j=3;
boost::bind(&print,20,3)();



//boost::bind - usage 2
class Temp{
public:
	void printTemp(int x){
		cout<<"Temp class print "<<x<<endl;
	}
};
//usage 2
Temp* t=new Temp;
boost::bind(&Temp::printTemp,t,4)();
boost::bind(&Temp::printTemp,_1,5)(t);

//boost::bind - usage 3
class Personal_Info{
	int age_;
	string name_;
public:
	Personal_Info(int age, string name):age_(age),name_(name){}
	int get_age() const{ 
		return age_;
	}
	string name() const{ 
		return name_;
	}
	void print_age(){cout<<"Personal_Info age:"<<age_<<endl;}
	void print_name(){cout<<"Personal_Info name:"<<name_<<endl;}
};
//usage 3
typedef vector<Personal_Info> PersonInfo;
PersonInfo pv;
Personal_Info p1(25,"dennis");
Personal_Info p2(26,"royce");
Personal_Info p3(18,"fendi");
pv.push_back(p1);
pv.push_back(p2);
pv.push_back(p3);
pv.push_back(Personal_Info(33,"lucy"));
sort(pv.begin(),pv.end(),boost::bind(less<int>(),
										boost::bind(&Personal_Info::get_age,_1),
										boost::bind(&Personal_Info::get_age,_2)));
for_each(pv.begin(),pv.end(),boost::bind(&Personal_Info::print_age,_1));

sort(pv.begin(),pv.end(),boost::bind(greater<string>(),
										boost::bind(&Personal_Info::name,_1),
										boost::bind(&Personal_Info::name,_2)));
for_each(pv.begin(),pv.end(),boost::bind(&Personal_Info::print_name,_1));



//boost::bind - usage 4
void printString (string s){
	cout<<s<<endl;
}
//usage 4
map<int,string> mm;
mm.insert(make_pair<int,string>(0,"boost"));
mm.insert(make_pair<int,string>(1,"bind"));
mm.insert(make_pair(2,"fine"));

for_each(mm.begin(),mm.end(),boost::bind(&printString,
											boost::bind(&map<int,string>::value_type::second,_1)));

//usage 5 
//if(x>5 && x<=10)
/*
int count = count_if(iv.begin(),iv.end(),boost::bind(logical_and<bool>(),
														boost::bind(greater<int>(),_1,5),
														boost::bind(less_equal<int>(),_1,10)));
*/
		
	



/*********************************
 * boost_bind & boost_function
 * bind & function　组合成回调函数
 *********************************/
Example 1:

class Thread{
	public:
		typedef boost::function<void()> ThreadCallback;
		Thread(ThreadCallback cb): cb_(cb){}
		void start();
	private:
		void run(){cb_();}
		ThreadCallback cb_;
};
class Foo{
	public:
		void runInThread();
		void runInAnotherThread(int);
};

Foo foo;
Thread t1(boost::bind(&Foo::runInThread(), &foo));
Thread t1(boost::bind(&Foo::runInAnotherThread(), &foo, 43));
t1.start();
t2.start();

/*****************/
Example 2:
class Connection;
class NetServer : boost::noncopyable{
	public:
		typedef boost::function<void(Connection*)> ConnectionCallback;
		typedef boost::function<void(Connection*, const void*, int len)> MessageCallback;

		NetServer(int port);
		~NetServer();
		
		void registerConnectionCallback(const ConnectionCallback&);
		void registerMessageCallback(const MessageCallback&);
		void sendMessage(Connection*, const void*, int len);

};

class EchoService{
	public:
		typedef boost::function<void(Connection*, const void*, int)> SendMessageCallback;
		EchoService(const SendMessageCallback& sendMsgCb): sendMessageCb_(sendMsgCb){}
		void onMessage(Connection* conn, const void* buf, int size){
			sendMessageCb_(conn,buf,size);
		}
		void onConnection(Connection* conn){}
	private:
		SendMessageCallback sendMessageCb_;
};

int main(){
	NetServer server(7);
	EchoService echo(boost::bind(&NetServer::sendMessage, &server, _1, _2, _3));
	server.registerMessageCallback(boost::bind(&EchoService::onMessage, &echo, _1, _2, _3));
	server.registerConnectionCallback(boost::bind(&EchoService::onConnection, &echo, _1));
}


/*****************/
经典问题，如果企鹅不能飞，能否继承bird类
用boost::bind & boost::function来解决
class Penguin{
	public:
		void run();
		void swim();
};
class Sparrow{
	public:
		void fly();
		void run();
};

typedef boost::function<void()> FlyCallback;
typedef boost::function<void()> RunCallback;
typedef boost::function<void()> SwimCallback;

class Foo{
	public:
		Foo(FlyCallback flyCb, RunCallback runCb): flyCb_(flyCb), runCb_(runCb){}
	private:
		FlyCallback flyCb_;
		RunCallback runCb_;
};

int main(){
	Sparrow s;
	Penguin p;
	Foo foo(boost::bind(&Sparrow::fly, &s), boost::bind(&Sparrow::run, &s));
}
