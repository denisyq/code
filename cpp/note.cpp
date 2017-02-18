#CPP basic concepts

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
		Base(const Base&);//拷贝构造函数
		Base& operator=(const Base&);//赋值
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
