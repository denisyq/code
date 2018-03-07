# Java 核心技术 卷1
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

##ArrayList等数据结构和基本算法(sort/search)
这部分内容，需要结合具体，类似C++STL，单独来总结。


##多线程
Runnable r = new BallRunnable(b,comp);
Thread t = new Thread(r);
r.start();

public class BallRunnable implements Runnable{
	public BallRunnable(Ball aBall, Component aComponent){
		ball = aBall;
		component = aComponent;
	}
	public void run(){
		try{
			...
		}catch(InterruptedException e){

		}
	}
}
1. Thread t = new Thread(Runnable target);
2. void start();//调用Runnable的run()方法

getState()线程状态 New/Runnable/Blocked/Waiting/Timed waiting/Terminated
new Thread时候是New状态，然后t.start()时候是Runnable状态，什么时候跑起来是CPU说了算。
调度的时候，可能处在Blocked/Waiting/Timed waiting 状态，最后死了就Terminated

import java.util.concurrent.locks.*;
public class Bank{
	private final double[] account;
	private Lock bankLock;
	private Condition sufficientFunds;

	public Bank(){

	}
	public void transfer() throws InterruptedException{
		backLock.lock();
		try{
			while(account[from] < amount)
				sufficientFunds.await();
			
			account[from] -= amount;
			account[to]   += amount;

			sufficientFunds.signalAll();
		}final{
			bankLock.unlock();
		}
	}
}

//synchronized
public class Bank{
	private double[] account;
	public synchronized void transfer(int from, int to, int amount) throws InterruptedException{
		while(account[from] < amount)
			wait();
		account[from] -= amount;
		account[to]   += amount;
		notifyAll();
	}
}


# Effective Java

## 2. 遇到多个构造器
我们需要设计一个类，这个类有多个特征，在类构造时传入。在遇到多个构造器时，我们大抵有三种方法可以选择：
1. 对每个情况，都设计对应的构造器，比如我们有三个特征，我们大抵需要6个构造器。
public class NutritionFacts{
	private final int calories;
	private final int fat;
	private final int sodium;

	public NutritionFacts(int calories, int fat, int sodium){
		this.calories = calories;
		this.fat      = fat;
		this.sodium   = sodium;
	}
	public NutritionFacts(int calories){
		this(calories, 0, 0);
	}
	public NutritionFacts(int fat){
		this(0, fat, 0);
	}
	public NutritionFacts(int sodium){
		this(0, 0, sodium);
	}
	public NutritionFacts(int calories, int fat){
		this(calories, fat, 0);
	}
	public NutritionFacts(int fat, int sodium){
		this(0, fat, sodium);
	}
	public NutritionFacts(int calories, int sodium){
		this(calories, 0, sodium);
	}
}

2. JavaBeans模式：对于第一种情况，我们要写很多构造器，如果参数太多，不现实。那么可以用JavaBeans模式。
public class NutritionFacts{
	public NutritionFacts(){}
	public void setCalories(int val){ this.calories = val; }
	public void setFat( int val )   { this.fat      = val; }
	public void setSodium( int val ){ this.sodium   = val; }
}
这种模式，简单明了，代码读起来很容易看清楚。
缺点是：在构造时出现错误，JavaBeans模式自身的严重缺点，把构造过程分成了几个调用，导致构造过程中状态不一致。

3. Builder模式，有JavaBeans的简洁明了，又保证多构造器的安全性
public class NutritionFacts{
	private final int calories;
	private final int fat;
	private final int sodium;

	public static class Builder {
		private int calories = 0;
		private int fat      = 0;
		private int sodium   = 0;
		public Builder(){}
		public Builder calories(int val){
			calories = val;
			return this;
		}
		public Builer fat(int val){
			fat = val;
			return this;
		}
		public Builder sodium(int val){
			sodium = val;
			return this;
		}
		public NutritionFacts build(){
			return new NutritionFacts(this);
		}
	}
	private NutritionFacts(Builder builder){
		calories = builder.calories;
		fat      = builder.fat;
		sodium   = builder.sodium;
	}
}
NutritionFacts cocaCola = new NutritionFacts.Builder().calories(100).fat(100).sodium(20).build();
缺点：为了创建对象，必须先构造Builder构造器，对于强调性能情况下，不可取。

---
总结：如果在能够知道有几个必须构造的参数时，第一个首选，保证安全和性能。第二也可选，一般构造时没问题。为了万无一失，用Builder。

## 4. 通过私有化构造器强化不可实例化
public class UtilityClass{
	private UtilityClass(){
		throw new AssertionError();
	}
}

## 6. 消除过期的对象引用
public class Stack{
	private Object[] elements;
	private int size = 0;

	public void push(Object e){
		ensureCapacity();
		elements[size++] = e;
	}
	public Object pop(){
		if (size == 0)
			throw new EmptyStackException();

		//wrong behavior
		return elements[--size];

		//right behavior
		Object result = elements[--size];
		elements[size] = null;
		return result;
	}
	private void ensureCapacity(){
		if(elements.length == size)
			elements = Arrays.copyOf(elements, 2*size+1);
}
从栈里弹出来的对象，即使程序不再引用他们，他们也不会被当作垃圾回收掉，栈内部会维护着对这些对象的过期引用。所以这些对象的内存泄漏是比较隐蔽的。
对策：一旦一个对象不再需要，对他们清空引用。
java的内存泄漏，一般发生在一个类自己管理内存的情况。

## 7. 避免使用finalizer
C++的析构器一般用来回收内存资源，在java中，一般使用try-finally块来完成类似的工作
但是finalizer的缺点，在于，不能保证会被及时的执行。比如用finalizer来关闭已经打开的文件描述符。因为JVM可能会延迟执行finalizer.
而且，finalizer有个非常严重的性能损失。
对策：用try-finally
Foo foo = new Foo();
try{
	...
}finally{
	foo.terminate();
}

## 19. 接口只能用于定义类型
如果你要定义常量，不应该用接口来定义，可以用类。
public class Constant{
	private Constant(){}
	public static final double AAA = 1;
	public static final double BBB = 2;
}

## 36. 坚持使用Override注释
public class Bigram{
	...
	public boolean equals(Bigram b){
		return b.first == first && b.second == second;
	}
	//对于这个equals方法，他是override父类Object的equals,但是Override父类方法需要传入Object
	//如果在方法名前加入 @Override public boolean equals(), 编译时就能发现错误,所以@Override能帮助发现问题
	//应该是 
	@Override public boolean equals(Object o){
		if (!(o instanceof Bigram)) return false;
		Bigram b = (Bigram) o;
		return b.first == first && b.second == second;
	}
}

# 类库

主要两个方面:Collection和Map.

Collection包含了List和Set两大分支

List是一个有序的队列，每一个元素都有它的索引。第一个元素的索引值是0。List的实现类有LinkedList, ArrayList, Vector, Stack
List: ArrayList(Vector), Stack(继承于Vector) 都是顺序容器，基于数组.当然Stack本身也可以用链表形式来实现。
	  LinkedList,双向链表，随机访问弱,随机增减快

Set是一个不允许有重复元素的集合. Set的实现类有HastSet和TreeSet。HashSet依赖于HashMap，它实际上是通过HashMap实现的；TreeSet依赖于TreeMap，它实际上是通过TreeMap实现的。
Map是一个映射接口，即key-value键值对。Map中的每一个元素包含“一个key”和“key对应的value”。
AbstractMap是个抽象类，它实现了Map接口中的大部分API。而HashMap，TreeMap，WeakHashMap都是继承于AbstractMap。
Hashtable虽然继承于Dictionary，但它实现了Map接口。

Iterator:我们说Collection依赖于Iterator，是因为Collection的实现类都要实现iterator()函数，返回一个Iterator对象。ListIterator是专门为遍历List而存在的

##ArrayList 
顺序容器，底层是数组实现，不是list. ArrayList不是线程安全的，单个线程可以用，多线程用Vector.
随机访问高，随机增减效率低
add(E e);
addAll(ArrayList a);
clear()/clone()/isEmpty/resize
E get(int index);
int indexOf(E e);
E remove(int index);
boolean remove(E e);
E set(int index);
toArray();
sort();
//遍历
for(int i:size) ArrayList.get(i);
Integer value = null;
Iterator iter = list.iterator();
while (iter.hasNext()) {
    value = (Integer)iter.next();
}

##LinkedList 
双向链表，随机访问慢，顺序访问快
addFirst(E object)
addLast(E object)
E getFirst();
E getLast();
E get(int location);
E peekFirst();
E peekLast();
E pollFirst();
E pollLast();

E remove(int index);
boolean remove(E e);
E set(int index, E e);

int indexOf(E e);
int lastIndexOf(E e);

size/toArray/

for(Integer i : LinkedList){;}//遍历
如果遍历可以删除元素,每次遍历都删除removeFirst/removeLast类似,速度更快.


##Stack
push/pop/
peek/empty/
##Queue
Queue<int> q =  new Queue<int>();
q.add(int i); == q.offer(i);
q.remove();   == q.poll();
q.element();  == q.peek();
##PriorityQueue
PriorityQueue<String> pq = new PriorityQueue<String>();
pq.add(E e);
pq.remove(E e);
pq.peek();//拿出第一个，但是不移除
pq.poll();//拿出第一个，且移除
contains/size/clear/toArray/isEmpty/



##HashMap
void                 clear()
boolean              containsKey(Object key)
boolean              containsValue(Object value)
Set<Entry<K, V>>     entrySet()
V                    get(Object key)
boolean              isEmpty()
Set<K>               keySet()
V                    put(K key, V value)
void                 putAll(Map<? extends K, ? extends V> map)
V                    remove(Object key)
int                  size()

Map<String, Integer> m = new HashMap<>();
m.put("hello",1);
m.put("hello2", 2);
m.put("hello",3);
System.out.println(m.get("hello"));//get()
//遍历一
for(Map.Entry<String,Integer> entry: m.entrySet()){
    System.out.println(entry.getKey() + ": " + entry.getValue());
}
//遍历二
Integer integ = null;
Iterator iter = map.entrySet().iterator();
while(iter.hasNext()) {
    Map.Entry entry = (Map.Entry)iter.next();
    key = (String)entry.getKey();
    integ = (Integer)entry.getValue();
}
##Hashtable
所有用法跟HashMap一样，区别在：
1. HashMap是线程不安全的，Hashtable是线程安全的
2. HashMap可以存null，Hashtable不可以存null作为key
3. HashMap的迭代器是fail-fast，有线程修改HashMap的结构元素，将抛出异常。
4. 遍历顺序不同：通过迭代器遍历时，HashMap是前-后遍历，Hashtable是后-前遍历。

##TreeMap
基于RBTree，是非同步的，线程不安全，迭代器是fail-fast。

Entry<K, V>                ceilingEntry(K key)
K                          ceilingKey(K key)
void                       clear()
Object                     clone()
Comparator<? super K>      comparator()
boolean                    containsKey(Object key)
NavigableSet<K>            descendingKeySet()
NavigableMap<K, V>         descendingMap()
Set<Entry<K, V>>           entrySet()
Entry<K, V>                firstEntry()
K                          firstKey()
Entry<K, V>                floorEntry(K key)
K                          floorKey(K key)
V                          get(Object key)
NavigableMap<K, V>         headMap(K to, boolean inclusive)
SortedMap<K, V>            headMap(K toExclusive)
Entry<K, V>                higherEntry(K key)
K                          higherKey(K key)
boolean                    isEmpty()
Set<K>                     keySet()
Entry<K, V>                lastEntry()
K                          lastKey()
Entry<K, V>                lowerEntry(K key)
K                          lowerKey(K key)
NavigableSet<K>            navigableKeySet()
Entry<K, V>                pollFirstEntry()
Entry<K, V>                pollLastEntry()
V                          put(K key, V value)
V                          remove(Object key)
int                        size()

SortedMap<K, V>            subMap(K fromInclusive, K toExclusive)
NavigableMap<K, V>         subMap(K from, boolean fromInclusive, K to, boolean toInclusive)
NavigableMap<K, V>         tailMap(K from, boolean inclusive)
SortedMap<K, V>            tailMap(K fromInclusive)

HashMap<String,String> map=new HashMap<String, String>();
map.put("DA","11");
map.put("b", "22");
map.put("c","c1111");
map.put("d", "33");
for (Map.Entry<String,String> entry: map.entrySet()) {
    System.out.println("排序之前:"+entry.getKey()+" 值"+entry.getValue());
}
SortedMap<String,String> sort=new TreeMap<String,String>(map);
Set<Map.Entry<String,String>> entry1=sort.entrySet();
Iterator<Map.Entry<String,String>> it=entry1.iterator();
while(it.hasNext()){
    Map.Entry<String,String> entry=it.next();
    System.out.println("排序之后:"+entry.getKey()+" 值"+entry.getValue());
}

treeMap.put("one",rnd.nextInt(10));
Iterator it = treeMap.entrySet().iterator();
while(it.hasNext()){
	Map.Entry entry = (Map.Entry)it.next();
	entry.getKey();
	entry.getValue();
}
treeMap.size();
treeMap.containsKey("one");
treeMap.containsValue(new Integer(0));
treeMap.remove("one");
treeMap.clear();
treeMap.isEmpty();

treeMap.headMap(toKey,true/false);
treeMap.subMap(fromKey, toKey);
treeMap.tailMap(fromKey,true/false);//带不带fromKey


##HashSet
HashSet 是一个没有重复元素的集合.HashSet允许使用 null 元素。HashSet是非同步的。HashSet通过iterator()返回的迭代器是fail-fast的.

boolean         add(E object)
void            clear()
Object          clone()
boolean         contains(Object object)
boolean         isEmpty()
Iterator<E>     iterator()
boolean         remove(Object object)
int             size()

遍历
Iterator it = set.iterator();
while(it.hasNext()){ it.next();}

String[] arr = (String[])set.toArray(new String[0]);


##TreeSet
boolean                   add(E object)
boolean                   addAll(Collection<? extends E> collection)
void                      clear()
Object                    clone()
boolean                   contains(Object object)
E                         first()
boolean                   isEmpty()
E                         last()
E                         pollFirst()
E                         pollLast()
E                         lower(E e) //小于
E                         floor(E e) //小于等于
E                         ceiling(E e)//大于等于
E                         higher(E e) //大于
boolean                   remove(Object object)
int                       size()
Comparator<? super E>     comparator()
Iterator<E>               iterator()
Iterator<E>               descendingIterator()
SortedSet<E>              headSet(E end)
NavigableSet<E>           descendingSet()
NavigableSet<E>           headSet(E end, boolean endInclusive)
SortedSet<E>              subSet(E start, E end)
NavigableSet<E>           subSet(E start, boolean startInclusive, E end, boolean endInclusive) //tSet.subSet("aaa", true, "ccc", true));
NavigableSet<E>           tailSet(E start, boolean startInclusive)
SortedSet<E>              tailSet(E start)

Iterator it = set.iterator();
while(it.hasNext()) it.next();

TreeSet不支持快速随机遍历，只能通过迭代器进行遍历！



##StringBuffer
StringBuffer stringBuffer =  new StringBuffer();
stringBuffer.append("abc").append('d');
StringBuffer.insert(int pos, String s);
StringBuffer.delete(int start, int end);
StringBuffer.deleteCharAt(int index);
StringBuffer.replace(int start, int end, String str)
StringBuffer.reverse();
StringBuffer.substring(int start, int end);
StringBuffer.toString();
另外，StringBuilder类库比StringBuffer效率快，但是不是线程安全的。

##Math

##ArrayDeque
head & tail
head 指向第一个元素，tail指向最后一个元素+1的位置

增加head: elements[--head] = e;
删减head: elements[head] = null; head = head+1;
增加tail: elements[tail] = e; tail++;
删减tail: elements[tail-1] = null; tail--;

addFirst(E e);
addLast(E e);
E removeFirst);
E removeLast();

E getFirst();
E getLast();

size/isEmpty/clear

public Iterator<E> iterator();
public Iterator<E> descendingIterator();
boolean hasNext();
E next();
void remove();

toArray();
boolean contains(E e);
boolean remove(E e);




##Random
Random rnd =  new Random();
rnd.doubles();
rnd.ints();
rnd.setSeed(long seed);

