#!/usr/bin/python

from queue import Queue
from queue import LifoQueue
from queue import PriorityQueue
#可以查看queue.py看具体实现，另外，PriorityQueue需要定制，现在只能从小到大
#1. Queue()/LifoQueue()/PriorityQueue()
#2. qsize()/full()/empty()
#3. put(item,timeout)/put_nowait(item)/get(timeout)/get_nowait()
#4. task_done()/join(): join就是在等多线程所有task_done结束

str="abcdefghijk"
import random
#Queue
q=Queue(10)
for i in range(10):
	q.put(random.choice(str))
print("size=",q.qsize())
while not q.empty():
	print(q.get())
	q.task_done()

#Lifo Queue
print("-"*10,"lifo_queue","-"*10)
lifoq=LifoQueue(10)
for i in range(10):
	lifoq.put_nowait(random.choice(str))
while not lifoq.empty():
	print(lifoq.get_nowait())
	lifoq.task_done()

#Priority Queue
print("-"*10,"priority queue","-"*10)
pq=PriorityQueue(10)
for i in range(10):
	pq.put_nowait(random.choice(str))
while not pq.empty():
	print(pq.get_nowait())
	pq.task_done()

