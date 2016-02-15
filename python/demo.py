#! /usr/bin/python

#1 base_chapter_1
'''
1. which python
2. python
3. apt-get install python
4. import math / from math import sqrt
5. #! /usr/bin/python
6. comment: #,''',''',""","""
'''


#2 sequence/raw_input/if/in
"""
database=[
	['adam','1234'],
	['ben','567'],
	]
print "hello",
print "world" #print in the same line
name=raw_input("user name: ")
passwd=raw_input("passwd: ")
if [name,passwd] in database: 
	print "good"
"""




#3 list/sub_list/
'''
#cons
x=[1,2,3]
y=x[1:]#sub_list
#y=x means y & x point to the same list
#y=x[:] Means y got a copy of x

#iter
x.index(2)#index:as iterator
#element
x[0]=100#element modify
#size/empty
x.count(value)#count
len(x);max(x);min(x);
#modify
#design stack: append/pop
#design FIFO: insert(0,value)/pop
x.append(value)#append one
x.extend(y)#extend more
x.insert(index,value)#insert before index
x.pop(2)#pop()->last one && pop(index)
del x[0]#element delete
x.remove(2)

#more
x.reverse()
x.sort()#x is changed
x.sort(reverse=True)
cmp(2,1)
x.sort(cmp)
y= sorted(x)#x not changed
>>> L
[('a', 1), ('c', 3), ('d', 4), ('b', 6)]
>>> L.sort(key=lambda x:x[1],reverse=True)#2nd parameter sort
>>> L
[('b', 6), ('d', 4), ('c', 3), ('a', 1)]
'''




#4 string
'''
#join
lst=['1','2','3']
print "+".join(lst)

#split
print "hello world yes".split(" ")
print "".join("hello world yes".split(" "))#delete space in string

#find/rfind
str="hello ,world HELLO"
print str.find("world")

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
'''


#5 dict - as map
'''
#cons:
phonebook={"adam":"1234",
			"ben":"4567",
			"lisa":"6789",
			"ben":"1111"}
d=dict.fromkeys(['name','age'],'Unknown')

#del/clear/len/copy/deepcopy
if "ben" in phonebook: del phonebook["ben"]
print len(phonebook)
phonebook[123]="1234"
print phonebook

phonebook.clear()
from copy import deepcopy
dd = deepcopy(d);
dc = d.copy()
print d.get("hello","not available")
d.pop("name")#same as del d['ben']
key,value=d.popitem()#ramdon pop
print key, value
phonebook.values()
phonebook.keys()
'''



#6 if/for/while
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



