JDK 1.8/1.9 Dev Version
JDK 8/9 Product version

JDK/JRE
javac -version
java -version
apt-get install openjdk-9-jdk

javac denisyq.java ==> denisyq.class
java denisyq

java对大小写敏感，类名和文件名一致
public class firstDemo{
	public static void main(String[] args){
		System.out.println("Hello world!");
	}
}
Q:java的main函数为啥是public static void 静态的？
A:http://www.importnew.com/8475.html
静态的不需要实例化，静态的直接变成可执行代码。


int/short/long/byte
float/double 如果一个数字是1.5f，是浮点数，如果不带f，默认是double
char/boolean 
java中都是有符号的，都是signed

final int a = 1; final是指常量赋值，类似const

数学
import static java.lang.Math.*;
Math.sin
Math.cos
Math.abs
Math.sqrt
Math.pow



java.lang.string
String a=""
String s = a.substr(0,3); substr[iterator_start, iterator_end) 前闭后开 substr(1,6) 从1开始，到5结束，不要6
拼接：String a + String b
不可修改内部元素，String a = "HelloWorld"; 你不能修改a变成“denisyq" ; 或者 a[4] = 'b'也是不行的
不可变字符串，编译器是为了让字符串共享。如果字符串经常用来比较，速度是快。

字符串比较：
str1.equals(str2);比较内容
str1 == str2；这个是比较字符串是否放在同一个地方.虽然虚拟机共享相同的字符串，但是用==来比较不保险

字符串null
if(str1 != null && str1.length() != 0)


输入输出
import java.util.*;//Scanner在java.util.*里面
System.out.println
Scanner in = new Scanner(System.in);
String name = in.nextLine();


Array
int[] a = new int[100];
int[] a = new int[] {1,2,3,4,5};
for(int i=0; i<a.length; i++){
	System.out.println("");
}
for(int element : a)
	System.out.println(Arrays.toString(a));

int[] copy = Arrays.copyOf(a, a.length);


命令行参数
public static void main(String[] args);
args[0] 就是后面跟的第一个参数
args.length
for(String s:args) System.out.println(s);

Math.random() ==> return [0,1] value
Arrays.sort(arr);

---
java.util.Arrays 1.2

static String toString(type[] a);
static type copyOf(type[] a, int length);
static type copyOf(type[] a, int start, int end);
static void sort(type[] a); //ascending
static int binarySearch(type[] a, type v);
static int binarySearch(type[] a, int start, int end, type v);
static void fill(type[] a, type v);
static boolean equals(type[] a, type[] b);

---

二维数组
int[][] arr = {
	{1,2,3},
	{2,3,4},
	{2,3,5}
}
System.out.println(Arrays.deepToString(arr));
for(int[] a : arr)
	for(int val : a)
		System.out.println(val)


##类
Date birthday = new Date();//java
Date *birthday = new Date();//c++

所有java对象都存储在堆中。每个文件名需要和public类名一致。然后每个文件里面只能有一个public类，其他的就是非公有类
Employee.java
public class Employee{}
class staff{}

Employee staff = new Employee();//java, 随时伴随着new
Employee staff();//c++, java就不行,没法在栈上

C++可以将类中的函数在外面实现
class A{
	public:
		void getName();
}
void A::getName(){
	return name_;
}
但是java不可以，必须在类内部实现。且，不代表内部实现的都是inline，是否inline由JVM决定.


##静态域static
类中的静态域，属于类，而不属于对象，这个跟C++类似.静态域先于对象生成前存在。
public class Math{
	public static final double PI = 3.1415926;
}
这种，可以直接用类名来访问 Math.PI
如果不是static，那么只能用对象来访问. Math m = new Math(); System.out.print(m.PI);

静态方法：Math.pow(x,a)


##值传递
void swap(int a, int b);//我们知道这样肯定无法swap的，c++中一般是要么指针，要么引用
void swap(Employee staff);//如果修改的是类对象的内部值，只有传递对象进来，才能改变，因为java对象本质上是指针
void swap(Employee staff1, Employee staff2);//也是失败的

##包
import static java.lang.System.*;
out.println();

##继承
class Manager extends Employee{//java中的继承都是公有继承
	private int bonus;
	public Manager(String name, ...){
		super(name,..);//Employee class cons
		bonus=0;
	}
	public getSalary(){
		int baseSalary = super.getSalary();//调用父类的getSalary
		return baseSalary + bonus;
	}
} 

##阻止继承
final class Executive extends Manager{
}//对类的final

class Executive extends Manager{
	final void run(){}//对方法的final,防止多态，子类无法override
}

##强制转换
Employee e = new Manager(); //子类赋给父类，没问题

父类转化成子类：
Manager boss = (Manager) employee[1];//报错
if(employee[1] instanceof Manager){	
	boss = (Manager) employee[1];//这样没问题，主要是确认employee[1]有Manager的特征
	...

}

##抽象类
public abstract String getDescription();
如果类中有抽象方法,类名也要注明abstract.这个观点跟C++纯虚函数类似，有抽象方法，无法实例化。


##Object所有类的超类
也就是所有类，都天生带有Object的方法
1, equals
2, 相等型测试
3, hashCode
4, toString


##泛型数组列表ArrayList
ArrayList<Employee> staff = new ArrayList<Employee>();//类似与C++的vector
1, void set(int index, T obj); //不能直接用[]来赋值
2, T get(int index);
3, void add(int index, T obj);
4, T remove(int index);

##枚举
public enum Size{
	SMALL,
	MEDIUM,
	LARGE
};

##接口
public interface Demo{
	void demo1();
	void demo2();
}
class ABC implements Demo{
}
接口是类似纯虚类，里面只有类似纯虚函数，没有实现，一般设置为public(有且只有public).
它定义的更多的是一个行为，例如Runable.对于接口的实例化，必须实现所有接口的方法.
抽象类可以部分实现某一个方法，但是接口不会实现任何一个方法。

Why需要接口，用抽象类不行吗？
A:java中不允许多继承，也就是说，你不可以
public class ABC extends Demo1, Demo2{} //Error
但是你可以用接口这么实现：
public class ABC extends Demo1 implements Demo2 // OK

##对象克隆
深拷贝和浅拷贝
Obj.clone();

##内部类
public class ABC{
	private int a,b;
	public class innerClass implements ActionListener{
		...	
	}
}
一般，内部类是为了域名控制和访问控制，还有，为了callback回调方便，才使用的。
public class InnerClassTest{
	public static void main(String[] args){
		TalkingClock clock = new TalkingClock(1000,true);
		clock.start();
	}
}
class TalkingClock{
	private int interval;
	private boolean beep;
	public TalkingClock(int interval, boolean beep){
		this.interval = interval;
		this.beep     = beep;
	}
	public void start(){
		ActionListener listener = new TimePrinter();
		Timer t = new Timer(interval, listener);
		t.start();
	}
	public class TimePrinter implements ActionListener{
		public void actionPerformed(ActionEvent event){
			Date now = new Date();
			System.out.println("At the tone, the time is " + now);
			if(beep) Toolkit.getDefaultToolkit().beep();
		}
	}
}









