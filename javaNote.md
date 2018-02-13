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