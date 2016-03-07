#! /usr/bin/python

#python source code is located /usr/lib/python3.2
#python bin is located /usr/bin/python ln -s /usr/bin/python3.2
#change it when you need to switch python2.7

###################
#1 base_rule
###################
1. which python
2. python
3. apt-get install python
4. import math / from math import sqrt
4. import math / from math import *
5. #! /usr/bin/python
6. comment: #
7. comment block: ''',''',""","""
8. dir(list): show list API
#带逗号是显示在同一行
print "hello",
print "world" 


#######################
# if/for/while
#######################
#>, >=, <, <=, ==, !=, is, is not, and, or, not,
#for/while/if/else; continue/break/pass
#in, not in, 
a=10
if a>10:
	print ">10"
elif a>1 and a<10: # && and, || or, ! not
	print "1-10"
else:
	print "10"

words=['hello','little','doudou']
for word in words:
	print word
#for num in range(0,101):#range,num in 0-100
#for num in range(99,81,-1)
while a<100:
	a+=1
	if a>50: 
		break
#assert a>=100
from math import sqrt
for num in range(100,81,-1):
	a=sqrt(num)
	if a == int(a):
		print "%.2f" % a
		break
	elif a < int(a):
		#ddd
		pass
	else:
		print "else"

name=raw_input("user name: ")
passwd=raw_input("passwd: ")
if [name,passwd] in database: 
	print "find it"

###############
# function 函数
###############
def foo():
	print("hello",end='')

#可接受任意参数
def foo(*args):

#只接受关键字参数
def foo(a,*,key)#foo(1,key=2)

#函数返回多个值,其实返回的是tuple
def foo():
	return 1,2,3
a,b,c = foo()

#带有默认参数
def foo(a,b,c=3):

#定义inline函数
add=lambda x,y:x+y
add(1,2)

#定义callback函数
def apply_async(func,args,*,callback):
	result = func(*args)
	time.sleep(2)
	callback(result)

class ResultHandler:
	def __init__(self):
		self.sequence=0
	def handler(self,result):
		self.sequence += 1
		print('sequence={} Got: {}'.format(self.sequence,result))

handler=ResultHandler()
apply_async(add,1,2,callback=handler.handler)

#除了用class来构造回调函数，还可以用闭包来做callback
def make_handler():
	sequence = 0
	def handler(result):
		nonlocal sequence
		sequence += 1
		print('sequence={} Got: {}'.format(sequence,result))
	return handler

handler = make_handler()
apply_async(add,1,2,callback=handler)

####################
#2 data sturcture
####################
#build-in data type:list,tuple,set,dict,string
#standard lib: collections
################
# list
################
#cons
x=[1,2,3]
#sub list
y=x[1:] // y=x[-3:] // y=x[:-1]
#y=x means y & x point to the same list
#y=x[:] Means y got a copy of x

#iter
x.index(value)#index:as iterator

#element
x[index]=100#element modify

#size/empty
x.count(value)#count
len(x);max(x);min(x);

#modify
#design stack: append/pop
#design FIFO: insert(0,value)/pop
x.append(value)#append one
x.extend(y)#extend more
x.insert(index,value)#insert before index

#three ways to delete, pop return the delete value
x.pop(2)#pop()->last one && pop(index)
del x[index]#element delete
x.remove(value)


#reverse/sort
x.reverse()
x.sort()#x is changed
x.sort(reverse=True)
cmp(2,1)
x.sort(cmp)
y= sorted(x)
y= sorted(x,key=lambda x:x[1])#x not changed
>>> L
[('a', 1), ('c', 3), ('d', 4), ('b', 6)]
>>> L.sort(key=lambda x:x[1],reverse=True)#2nd parameter sort
>>> L
[('b', 6), ('d', 4), ('c', 3), ('a', 1)]


##########
# tuple
##########
a=[]
a=tuple(a)
#tuple use as key in dict, list can not
#tuple could be ret from function


#########
#set
#########
#cons:
s=set([1,2,3])
s=set(list)

len(s)
s.clear()

x in s / x not in s
s.add(value)
s.remove(value)
s.discard(value)
ret=s.pop()

s=set([1,2,3])
ss=set([1,2])
ss.issubset(s) -> True
ss <= s -> True
ss < s -> True
s.issuperset(ss)
s >= ss
s > ss



#########
# string
#########
#contants
"2" in string.digits #True
string.hexdigits
string.octdigits
string.whiltespace
string.ascii_letters
string.ascii_lowercase
string.ascii_uppercase

#join
lst=['1','2','3']
print "+".join(lst)

#split
print "hello world yes".split(" ")
print "".join("hello world yes".split(" "))#delete space in string

#find/rfind
str="hello ,world HELLO"
print str.find("world")

#index/rindex
str.index("he")

#lower/upper/title
print str.lower()#islower(),upper(),isupper()
if str.lower().islower(): print "lower"
print str.title()#istitle

#replace
print "hello,world,hello".replace("hello","yes")

#strip/rstrip/lstrip
print "###     hello  ###".strip('#')
print "        hello     ".rstrip().lstrip()

#translate
from string import maketrans
table=maketrans('abc','xyz')
print "abc efg abc".translate(table)
print "abc efg abc".translate(table,' ')

#reverse,string does not have str.reverse() API
str="Hell o,world!"
str1= sorted(str)
d= list(reversed(str))#reversed(str) needs list
print ''.join(d)

str.capitalize()
str.endswith("abc")
str.startswith("abc")
str.swapcase()
str.title()
#isalpha(), isdecimal(), isdigit(), isnumeric(), islower(), isupper(), istitle()
#str.splitlines()->split \r \n etc.



# check not string
def notString(notstr):
	try: notstr + ''
	except TypeError: pass
	else: raise TypeError

# format显示
print('{},{}'.format(a,b))

################
# dict - as map
################
#cons:
phonebook={"adam":"1234",
			"ben":"4567",
			"lisa":"6789",
			"ben":"1111"}
d=dict.fromkeys(['name','age'],'Unknown')

key=['a','b','c']
value=['aaaa','bbb','cccc']
d=dict(zip(key,value))
d.setdefault("d")


#len/clear
len(dict)
dict.clear()

#element access
phonebook["adam"] #is adam is not in phonebook, will raise KeyError
dict.get("adam","not available")
phonebook.values()
phonebook.keys()

#setdefault/del/copy/deepcopy
dict.setdefault(key) #if key in dict, return its value, if not, add it
dict.update(dict)
if "ben" in phonebook: del phonebook["ben"]
#if "ben" not in phonebook:
d.pop("name")#same as del d['ben']
key,value=d.popitem()#ramdon pop, for destruction
phonebook[123]="1234"

from copy import deepcopy
dd = deepcopy(d);
dc = d.copy()

#traverse
pairs=[(k,v) for k,v in d.items()] #for traverse

#sort
sorted(d.items(),key=lambda d:d[1],reverse=True)


####################
#collections::deque
####################
d=deque([1,2,3,])
dd=deque('string')
ddd=deque(maxlen=5)

#element
dd[1]='s'

#len/clear
len(d)
d.clear()
d.count(value)

#append/appendleft/extend/extendleft/remove/pop
d.append('s')
d.append(dd)
d.appendleft('s')
d.extend(dd)/d.extendleft(dd)
d.insert(index,value)

d.pop()/d.popleft()
d.remove(value)
del d[0]

d.index(value)
d.reverse()
d.rotate(n)


def tail(file, len):
	with open("filename") as f:
		d=deque(f,maxlen=len)

#############################
#heapq
############################
h=[]
heapq.heappush(h,1)
heapq.heappush(h,2)
heapq.heappush(h,0)
heapq.heappop(h)
l=[1,3,2,4,2]
heapq.heapify(l)
heapq.nlargest(n,l,key=lambda x:x[0])
heapq.nsmallest(n,l,key=lambda x:x[0])


##################
#3 class/OO
##################
__metaclass__=type #super needs

class bird():
	def __init__(self,name):
		self.name=name
		self.hungry=True
	#private func, __name(self)
	#not safe, you can use instance=bird("bird"),instance._bird__eat()
	def __eat(self):
		if self.hungry:
			print self.name +": eat and full"
			self.hungry=False
		else:
			print self.name +": no thanks"
	#public func
	def eat(self):
		self.__eat()

class songbird(bird):
	def __init__(self,name):
		#init father class
		super(songbird, self).__init__(name)#name should be pass into class bird
		self.name=name
	def sing(self):
		print self.name + ": sing songs"

#python not guarantee private function
def foo():
	print 'foo'	
instance=bird("bird")
instance._bird__eat=foo #private __eat() is changed
instance.eat()


#################
# iterator
#################
class iterator():
	def __init__(self):
		self.base = 1
		self.increase = 2

	def next(self):
		self.base += self.increase
		return self.base
	
	def __iter__(self):
		return self
	
it=iterator()
for i in it:
	if i < 20:
		print i
	else:
		break


#################
#standard lib
#################


################
##search:bisect
################
##sorted ascending;array better than list, binary search should need ramdon access

data=[1,2,3,4,5,7,8]
##API:
bisect.bisect(data,4)
bisect.bisect_right(data,4)
bisect.bisect_left(data,4)

bisect.insort(data,4)
bisect.insort_left(data,4)
bisect.insort_right(data,4)

#bisect will return index for insertion
#support collections::deque, maybe better than list
#insert and keep ordered
#if array or sequence container, insert is not efficient api
#insort has insert(), not support collections::deque(3.5 above support)



################
##file:fileinput
################
#API:
fileinput.filename()		#
fileinput.fileno()			#fd number
fileinput.lineno()			#line increase after next file
fileinput.filelineno()		#line increasa in one file
fileinput.isfirstline()	
fileinput.isstdin()
fileinput.close()

#Example:
import fileinput
import sys
for line in fileinput.input(sys.argv[1:]):
	if fileinput.isfirstline():
		print("*"*10,fileinput.filename(),fileinput.filelineno(),line,end='')

##############
#file IO
##############
fp=open("filename",r) #with open() as f:
fp.read()
fp.readline()
fp.readlines()
fp.write()
fp.writelines()
fp.flush()
fp.seek()
fp.tell()
fp.close()


###############
#file:linecache
###############
#API:
linecache.getline("filename",lineno)
linecache.getlines("filename")[0:4]
linecache.checkcache("filename")
linecache.updatecache("filename")
linecache.clearcache("filename")


##############
#os
#shutil
##############
#API:
os.listdir(path='.')            #ls
os.chdir("/home/")              #cd
os.getcwd()                     #pwd
os.getlogin()                   #who am i
os.uname()                      #uname
os.system("ls")                 #run linux command

#dir
os.path.dirname("/home/luyq/note.py")               #get dir name /home/luyq##could use os.path.split()[1]
os.mkdir("home")                #mkdir one dir
os.makedirs("home/luyq")        #mkdir -p dir
os.rmdir("home")                #rm dir without -r
shutil.rmtree("home")           #rm dir with -r
os.rename(src,dest)             #mv dir
shutil.copytree("old_dir","new_dir_not_existed")
shutil.copy("old_file","new_dir/new_file")
#file
os.path.dirname("home/luyq/note.py") #get filename: note.py/could use os.path.split("home/luyq/note.py")[0]
os.mknod("filename")            #touch
os.access("filename",os.R_OK)   #check file could Read/os.W_OK/os.X_OK
os.stat("filename")             #get file status
shutil.copyfile("oldfile","newfile")  #copy file
shutil.copy("olddir","newfile")   #olddir
os.rename(src, dest)            #mv file
os.remove(filename)             #rm file
shutil.move("filename","newPosition")  #move file

os.path.isfile()                #check is file
os.path.isdir()                 #check is dir
os.path.isabs()                 #check is absolute dir
os.path.exists()                #check path exist
os.path.split()                 #return dir and file/os.path.split("home/lu.py"), return ["home","lu.py"] 
os.path.splitext()

#demo1:
if os.access("filename",os.R_OK):
	with open("filename") as f:
		f.readline()

#demo2:
#modify *.cpp files
import os
import os.path
for f in os.listdir():
	if f.endswith("txt"):
		new_file=os.path.splitext(f)[0]+".cpp"
		#new_file=f.rstrip("txt")+"cpp"
		os.rename(f,new_file)


################
#time
################
start=time.time()
time.sleep(4)
gap=time.time()-start

################
#闭包
################
def make_add(addend):
    def adder(base):
        print('base={},addend={}'.format(base,addend))
        return base+addend
    return adder

a=make_add(10)
b=make_add(20)

print(a(100),b(100))
#result:
base=100,addend=10
base=100,addend=20
110 120
