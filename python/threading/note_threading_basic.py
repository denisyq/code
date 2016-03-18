#!/usr/local/bin/python


import time	
import threading

#####################
# threading
#1. threading.active_count()
#2. threading.current_thread()
#3. threading.get_ident()
#4. threading.enumerate()
#5. threading.main_thread()
#########################
# threading::Thread:
#threading.Thread(target=foo,args=(),name="",deamon=False)
#1. start()
#2. join(timeout) 主线程会堵塞等待回收，最好加上timeout
#3.	getName()/setName() 
#4. ident:id num
#5. is_alive()
#6. isDaemon()/setDaemon():call it before thread start()
#7. 因为GIL存在，python Thread不适合做CPU密集型操作，适合IO密集型，有等待IO阻塞操作的并发任务
###########################
#threading :: Lock
#threading :: RLock
#mLock=RLock()
#1. mLock.acquire()
#2. mLock.release()
###########################
#threading::Condition
#1. con = Condition(lock)
#2. con.acquire()
#3. con.release()
#4. con.wait(timeout)
#5. con.wait_for(pred,timeout)
#6. con.notify(n=1)
#7. con.notify_all()
###########################
num = 0
mLock = threading.Lock()
class countdown():
	def __init__(self,name):
		self.name=name
	def count(self):
		global num, mLock
		while True:
			if mLock.acquire():
				if num < 10:
					num += 1
					print("{} {}".format(self.name,num))
					mLock.release()
				else:
					mLock.release()
					break

def main_1():
	for i in range(3):
		c = countdown("thread "+str(i))
		t=threading.Thread(target=c.count)
		t.start()
		
	print("active_count",threading.active_count())
	for i in threading.enumerate():
		print('enumerate-',i.getName())
	
import queue
import time
class taskQueue():
	def __init__(self,size):
		global mLock
		self.q=queue.Queue(size)	
		self.cond = threading.Condition(mLock)
	def addTask(self):#def addTask(self,task,*args,**kwargs)
		if mLock.acquire():
			while self.q.full():
				self.cond.wait()
			import random
			tmp = random.randrange(100)
			self.q.put(tmp)
			#self.q.put((task,args,kwargs))
			print(threading.current_thread().getName(),"put in ",tmp)
			self.cond.notify_all()
			mLock.release()
	
	def getTask(self):
		time.sleep(5)#let producer work first
		while True:
			if mLock.acquire():
				while self.q.empty():
					self.cond.wait()
				tmp=self.q.get_nowait()
				#tuple=self.q.get() ... task,args,kwargs = self.q.get() .....task(*args,**kwargs)
				if tmp:
					print(threading.current_thread().getName(),"get out ",tmp)
					self.cond.notify_all()
					self.q.task_done()
				mLock.release()

def main_2():
	q=taskQueue(10)
	consumer = threading.Thread(target=q.getTask)	
	consumer.start()
	for i in range(10):
		time.sleep(1)
		q.addTask()	




