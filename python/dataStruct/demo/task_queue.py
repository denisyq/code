#!/usr/bin/python
from threading import Thread
import queue
import time
import threading
class TaskQueue(queue.Queue):
	def __init__(self,num_workers=1):
		queue.Queue.__init__(self)
		self.num_workers = num_workers
		self.start_workers()

	def add_task(self,task,*args,**kwargs):
		args = args or ()
		kwargs = kwargs or {}
		self.put((task, args, kwargs ))

	def start_workers(self):
		for i in range(self.num_workers):
			t = Thread(target=self.worker)
			t.daemon = True
			t.start()

	def worker(self):
		while True:
			tupl = self.get()
			item, args, kwargs = self.get()
			item(*args, **kwargs)
			self.task_done()

def test():
	def blokkah(*args, **kwargs):
		time.sleep(1)
		print("task: "+(str)(time.time()))

	q = TaskQueue(num_workers=5)
	
	for item in range(10):
		q.add_task(blokkah)
	q.join()
	print("alldone")

#--------------------------------------------------------

class task_queue():
	def __init__(self,size):
		self.q=queue.Queue(size)
		self.mLock = threading.Lock()
		self.full_cond = threading.Condition(self.mLock)
		self.empty_cond = threading.Condition(self.mLock)
	def addTask(self):#def addTask(self,task,*args,**kwargs)
		if self.mLock.acquire():
			while self.q.full():
			    self.full_cond.wait()
			import random
			tmp = random.randrange(100)
			self.q.put(tmp)
			#self.q.put((task,args,kwargs))
			print(threading.current_thread().getName(),"put in ",tmp)
			self.empty_cond.notify_all()
			self.mLock.release()

	def getTask(self):
		time.sleep(5)#let producer work first
		while True:
			if self.mLock.acquire():
				while self.q.empty():
					self.empty_cond.wait()
				tmp=self.q.get_nowait()
				#tuple=self.q.get() ... task,args,kwargs = self.q.get() .....task(*args,**kwargs)
				if tmp:
					print(threading.current_thread().getName(),"get out ",tmp)
					self.full_cond.notify_all()
					self.q.task_done()
					self.mLock.release()

	def startThreadPool(self,n,target,*args):
		for i in range(n):
			threading.Thread(target=self.getTask,args=(*args,),daemon=True).start()
		

def main_2():
	q=task_queue(10)
	#consumer = threading.Thread(target=q.getTask)
	#consumer.setDaemon(True)
	#consumer.start()
	q.startThreadPool(n=3,target=q.getTask)
	for i in range(10):
		time.sleep(1)
		q.addTask()
	time.sleep(10)	
	print("active count:",threading.active_count())
	for i in threading.enumerate():
		if i is not threading.current_thread():
			print(i.getName(),"join")
			i.join(1)

	



if __name__ == "__main__":
	main_2()
