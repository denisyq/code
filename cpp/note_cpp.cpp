###########################################
#CPP basic concepts
###########################################
1. struct class 继承区别
strcut Derived:Base{} //默认是public继承
class Derived : Base{}//默认是private继承

另外，class & struct 的类也有不同
class A{
 int a; //默认私有private
};
struct B{
	int a; //默认公有public
};



2. Cons/copy Cons/pass Cons
class Base{
	public:
		Base(){}//默认构造函数
		Base(const Base&);//拷贝构造函数 copy constructor
		Base& operator=(const Base&);//赋值 copy assignment
		~Base(){}
};
Base base = Base();//默认构造函数
Base base2(base);  //拷贝构造函数
Base base3 = base; //拷贝构造函数
Base base4; base4 = base; //重载 赋值operator


3. 基类派生类　转换 ..多态　继承
Base* base;
Derived *de;
Base *b = de;//派生类赋给基类
Derived *de=base;//错误，不能这样赋值
//派生类是含有两个部分，一部分是基类的内容，一部分是自己独有的内容
//派生类赋给基类指针，让基类指针指向派生类中基类内容，这个过程很重要，
//因为这是实现多态以及“一个接口，不同实现”的办法

//多态是什么？
//多态是基类实现一个虚函数，一般是接口型函数，然后靠派生类自己去重写覆盖
//这里说下重写覆盖　和　重载的区别：
//重写覆盖　override overwrite 是对基类虚函数重写实现方法
//重载　overload　是同一个函数名，但是入参不同，实现了同函数不同入参同时存在
//
//那我们实现了重写覆盖后，就可以用派生类指针赋值给基类指针的方法，实现基类指针调用虚函数接口，
//从而实现不同派生类调用不同实现。完毕。
//那么多态的作用是什么呢，封装可以使得代码模块化，继承可以扩展已存在的代码，他们的目的都是为了代码重用。而多态的目的则是为了接口重用。也就是说，不论传递过来的究竟是那个类的对象，函数都能够通过同一个接口调用到适应各自对象的实现方法。
//最常见的用法就是声明基类的指针，利用该指针指向任意一个子类对象，调用相应的虚函数，可以根据指向的子类的不同而实现不同的方法。

	Base *pb;
	Derived *pd;

	1. 如果用派生类指针给基类指针
	Base *pb = pd;
	pb->foo();//如果foo函数不是虚函数，虽然是派生类指针给的基类，但是调用的是基类的foo函数
	pb->fun();//如果fun是虚函数，好，基类虚函数有虚函数列表，找到实际是pd这个派生类的地址，用pd的fun函数实现
	
	2. 如果用基类指针给派生类指针 
	Derived *pd = pb;//编译不通过

//虚函数
虚函数有虚函数列表，知道偏移地址

//纯虚函数，抽象类，纯接口
virtual void fun() = 0;
纯虚函数是抽象类，不能实例化，对象化
派生类必须实现抽象类接口，如果子类不实现纯虚函数接口，那子类也是抽象类，不能对象化
为什么设计纯虚函数：
１，防止抽象类实例化，抽象类就不应该实例化，Animal这个抽象类实例化是个什么？只能是tiger/Cat/etc才能实例化
２，为了编码的效率



4. 模板
template<typename T>
int cmp(const T& v1, const T& v2){
	if(v1>v2) return 1;
	else return 0;
}


5. 构造函数初始化和赋值的区别
//const变量,引用变量,没有默认构造函数的类对象 = 必须初始化
class A{
	A(int i):index_(i){}//初始化
private:
	int index_;
};

class B{
	B(int i){
		index_ = i;//赋值
	}
private:
	int index_;
};

//什么情况下必须用初始化？在const变量和引用变量的初始化，赋值是会报错或不起作用
//另外，在没有默认构造函数的变量对象进行赋值，是会报错的
//所以，没有赋值构造函数，拷贝构造函数的类对象，不能直接赋值，只能初始化
//最后，按照private变量申请的顺序来初始化最好
class C{
	C(int i):index_(i),para_(i){}
private:
	const int index_;
	int& para_;
};


//引申　＝＝＝＝＝默认构造函数？
//谁会没有默认构造函数，这不是系统自带的吗？
//==>系统会在类没有申明任何构造函数的前提下，自带默认构造函数。什么意思，就是一个构造函数都没有
//如果我有个构造函数，哪怕一个，系统就不再提供默认构造函数
//好，问题来了

class A{
	A(int a){}
};
class B{
	B();
	A a;
};
B b;
//b在无参数构造时，带着A一起构造，但是A有一个int的构造函数，所以就没有无参数的默认构造函数，这个最后是要报错的。
//在来一个例子
class A{
	A(int a){}
};
class B: A{
	
};
B b;//同样A的默认构造函数又没了,只能手动写上A的默认构造函数

6. 默认实参
void foo(int a, int b, int c =100);
在入参中，默认实参应该放在最后面
foo(1,2);

7. explicit
在构造函数之前使用，防止构造函数被隐式转换
class Foo{
	public:
		Foo(int a);
		explicit Foo(string name);
};


8. static
设计初衷：C++防止全局变量影响封装，所以使用static
static在类中表现：属于类，不属于对象
非static成员变量是属于各个对象的，static是属于整个类A

static 成员函数
因为这种函数属于类，不是属于对象，所以没有this形参
只能只用static变量，不能用非static变量
static成员函数不能是const,也不能是虚函数




#######################################################
# Note of "Effective C++"
# Written on Feb 20th, 2017
#######################################################
1. C++是C的升级版

- C++是以C为基础的，数据类型，语法，语句等
- C++是面向对象的：有类（构造和析构函数）封装，继承，多态，虚函数的动态绑定
- C++是Template C++　泛型编程，也是大部分程序员缺少的一部分。template的考虑与设计，已经弥漫这个C++
- C++的STL: STL是template程序库,里面有容器，迭代器，算法以及函数对象等

2. 尽量以const enum inline 替换#define
	另可相信编译器错误,而不是预处理器
	class GamePlayer{
		enum { num = 5 };
	};

	WHY?
	#define CALL_WITH_MAX(a,b) f((a)>(b)?(a):(b))
	CALL_WITH_MAX(++a,b); //a被累加了2次

	建议：对于单纯的常量，最好以const / enum 来代替#define。对于类似函数的宏，用inline代替

3. 尽可能用const
	const char* p ="hello";//const data, non-const pointer
	char* const p ="hello";//non const data, const pointer
	const char* const p = "hello";//const data, const pointer

	const vector<int>::iterator iter=vec.begin();
	*iter = 10;
	++iter; //--------- iter is const, can not be modified
	vector<int>::const_iterator cIter = vec.begin();
	*cIter = 10; //--------------cIter 指向的值是const,不能修改
	cIter++;

	const成员函数：不改变成员变量，最好的例子是直接return某个成员变量值
	const getValue() const;

4. 使用前初始化
	初始化尽量写在构造函数的冒号后面，不要在函数体内赋值
	class A:{
		A(int a):a_(a){}
	}
	记得这样比在函数体内赋值好的是：const, 引用对象，没有默认构造函数的对象 -> Item 5
	按照次序初始化

5. C++自动构造四个函数：默认构造函数，拷贝构造，拷贝赋值copy assignment，析构函数
6. 如果不希望class实现某些功能，就手动显式的disable. 比如不需要copy assignment 和copy cons, 那就不要让编译器自己生成。
	在private里面自己写一个。boost::noncopyable就是这样的例子

7. 为多态基类申明一个virtual析构函数
	为什么需要virtual 析构函数？
	Scenario 是这样：
	class TimeKeeper{};
	class WaterClock : public TimeKeeper{}
	TimeKeeper* getTimeKeeper();

	一般在代码中，我们会申明一个Derived并指向Base指针
	TimeKeeper* base = getTimeKeeper();//这个里面是Derived对象
	...
	delete base;

	如果让Base指针来删除Derived对象，一般是Derived中的Base部分都析构了，但是Derived自己独有的那部分就没有被析构，也就是说，如果Derived自己那部分有内存申请，可能就没有被delete掉，内存泄露。
	如何解决：给Base的析构函数加上virtual，这样就可以调用Derived的析构函数了，你可以在Derived析构函数内做delete
	经验：一般在类中，如果有virtual接口函数，只要有一个virtual函数，一般都要将析构函数设置成virtual。为啥？因为子类可能在这个virtual接口函数里面申请内存，那子类的析构函数必须要删掉内存，所以Base的析构必须virtual.
	如果这个类不准备作为基类，就没必要设置virtual函数。因为virtual对象要带虚函数表virtual table，比较占空间
	不要继承没有虚析构函数的类
	如果基类准备当做多态来使用，就应该为其申明一个virtual 析构函数，如果基类带有任何virtual 函数，他就应该拥有一个virtual析构函数

8. 别让异常逃离析构函数
	析构函数不要吐出异常，这样会导致后续工作无法销毁
	如果实在要吐出异常，那就自己捕获
	~A::A(){
		try{ db.close(); }
		catch (...){
		//记下close调用失败
		}
	}

9. 决不在构造函数和析构里面调用virtual函数
	为什么：因为在构造函数里调用，结果可能不是你想要的那样
	class Base{
		public:
			virtual void log() const = 0;
	};
	Base::Base(){
		log();
	}
	class Derived : public Base{
		public:
			Derived(){
				virtual void log() const =0;
			}
	};
	
	Derived d;
	这个时候构造子类，先要调用基类的构造，基类的构造函数里有个虚函数log,这就是引发惊奇的起点，这时候调用的log是基类自己的log实现，并不是子类的
	所以在基类函数的构造期间，virtual函数并不是virtual 函数，并不会下降到Derived阶层
	OK, 为啥？为啥不能下降到子类。。。。。
	如果假设我们下降到子类，那log的实现是子类的实现，如果期间调用了子类的各个local variable,子类的成员变量都还没有初始化了，这不就是有问题吗？？
	所以这个假设不能成立
	
	析构函数里也不能有虚函数？因为子类先析构，到最上面的基类析构时，如果有虚函数，子类都析构完了，虚函数用子类的还是基类的？用子类的就是未定义状态的混沌数据空间，这样会造成不可预知的结果。所以析构也不能用虚函数。
	构造函数是先基类 -- > 子类
	析构函数是先子类 -- > 基类


10. 令operator=返回一个reference to *this

	Widget& operator=(const Widget& rhs){
		...
		return *this;
	}

11. 在operator= 中处理“自我赋值”

12. 复制对象时，勿忘其每一个成分

	class Base{
		public:
		Base(const Base& rh);
		Base& operator=(const Base& rh);
		private:
		string name_;
	};
	
	Base::Base(const Base& rh):name_(rh.name){}
	Base& Base::operator=(const Base& rh){
		...;
		name_ = rh.name;
		return *this;
	}
	
	//这个时候上述代码都是没问题的
	//如果后来再加上一个string date;这样的赋值拷贝就不全了
	
	
13. 对象的资源管理
	以前用new delete 来管理资源，但是很容易在new后某处返回，造成delete没有执行，造成资源泄露。
	如何管理资源？第一用RAII的思想，在构造里申请内存，在析构里销毁，这样保证不泄露。第二是用智能指针来管理内存。
	智能指针能管理一个对象，有时不太容易管理一个数组，顺序存储空间，这时一般用vector或者boost::scoped_array/shared_array
	同样是智能指针，auto_ptr　有一个特性，是他在赋值给别人后，自己就成NULL,这样是保证一个指针指向一个对象，避免重复释放
	shared_ptr 就没有这个问题，他使用的是计数器
	最后的总结就是，不要手动设置new delete，因为很可能会忘记释放。尽量用vector/shapred_ptr/shared_array等

14. 在资源管理中注意copy行为
	在RAII的类中，如果有copy行为，会造成不可预期的局面
	一般通过禁止copy constructor 或者赋值构造, 继承boost::noncopyable
	或者通过增加计数器。。。这个一般用的少

15. new 配队 delete, new[] => delete[]
	int *p = new int(4);
	delete p;

	int *p = new int[4];
	delete[] p;

20. 宁可传递pass-by-reference-to-const代替pass-by-value
	值传递，有个很大的问题就是需要拷贝。拷贝出副本，如果是类，就会涉及到构造函数和析构，如果这个类还有继承，就还有涉及基类的构造，代价很大。
	如果是const reference传递，可以避免这些个问题。
　　另外，如果是子类用值传递的方式入参，入参的类型是基类，那么在副本构造时，子类会面临切割掉部分，因为会调用基类的构造，子类的部分功能没有了。
　　
	引用和指针的区别：
	第一，引用需要初始化，赋初始值。所以在类的构造初始化时，不要在构造函数里赋值，要在初始化的方式赋值
	第二，引用不能被修改

	所以入参传递const引用，是个很好的选择。
	但是入参是内置类型int char什么的，或者是STL的迭代器或函数对象，可以用pass-by-value,因为那个副本开销不大，也不需要担心类的切割。

21. 必须返回对象时，别妄想返回reference
	如果这个返回引用指向一个local stack 变量，那在函数结束时，该变量即销毁了，如何返回这个local变量的引用了？
    如果是local-heaped 变量，那谁来销毁这个内存？如果后期调用多了，很容易管理混乱。
	对于类对象返回问题，如果在单线程里面考虑，用static变量且返回值，而不是引用，可能好点。
	const Rational operator * (const Rational& lh, const Rational& rh){
		return Rational(lh.n * rh.n, lh.d * rh.d);
	}

22. 将成员变量申明为private
	WHY 为啥要把成员变量设置成private? 我们一直都这么写，可都不知道为什么
	因为如果成员变量是public, protected, 派生类内部函数实现是可以用基类的这些变量，如果需要改动或者删除了基类的这些public变量，影响了很多类。
	但是如果是private变量，子类都看不见也没法用它来函数实现，所以影响的只是基类，这样就易于管理。

23. 拿non-member函数替代member函数
	因为non-member函数都访问不到private成员变量，所以他的封装性更好
	什么是封装性更好？因为这个函数实现能访问public，那public变量有改动，这个函数就废了。封装性好，是提供了更好的独立性。

26. 尽量延后变量定义的时间
	用的时候再定义，这样如果定义了忘记用，也不会再一开始就有开销，这个一般是针对有构造和析构的类对象来讲。
	不止延后变量定义的时间，直到非得使用他的前一刻。甚至应该尝试延后这份定义到能够给他初始实参为止。
	string passwd(old_passwd);
	要比下面更有效
	string passwd;
	passwd = old_passwd;

27. 尽量少做转型动作
	const_cast<T>()   -> 将const 转型成 non-const
	static_cast<T>()  -> 用处最广，隐形转型
	dynamic_cast<T>() -> 这个一般是这样用，子类对象赋给基类指针，这是想把基类指针往下转型到子类
	reinterpret_cast<T>() 这两种用的少

28. 避免返回的是指向内部私有的引用
	如果有个函数返回的是个引用，而这个引用又是这个类的私有成员变量，那这个私有变量就可能被修改。

30. inline的里里外外
	inline的机理是，凡是在inline函数的调用处，都用inline函数来代替。缺点，会造成程序的体积变大。

31. 将文件间的编译依存关系降到最低
	












