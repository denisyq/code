#!/usr/bin/python
from threading import Thread
import queue
import time

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

if __name__ == "__main__":
	test()
