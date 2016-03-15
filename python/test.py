#!/usr/local/bin/python


import time	
from threading import Thread
######################
#Thread:
#1. start()
#2. join(timeout)
#3.	getName()/setName() 
#4. ident:id num
#5. is_alive()
#6. isDaemon()/setDaemon():call it before thread start()
#7. 因为GIL存在，python Thread不适合做CPU密集型操作，适合IO密集型，有等待IO阻塞操作的并发任务
######################
'''
class countdown():
	def __init__(self,n):
		self.count = n
		self.time = 0
	def countdown(self):
		while self.count > 0:
			time.sleep(1)
			self.time += 1
			self.count -= 1
			print("sleep {} sec".format(self.time))

c = countdown(5)
t1= Thread(target=c.countdown,args=(),daemon=False)
t1.setName("t1")
t1.start()
t1.join(1)
if t1.is_alive():
	print(t1.getName(),"id is:",t1.ident)
'''

###########################
#threading :: RLock
#1. RLock.acquire()
#2. RLock.release()
#3. mLock=RLock()
###########################
from threading import Thread
from threading import RLock
mLock = RLock()
def add(count):
	global x
	while True:
		mLock.acquire()	
		if count:
			x += 1
			count -= 1
		else:
			mLock.release()
			print("x is:",x)
			break
		mLock.release()


def test():
	t1 = Thread(target=add,args=(5,))
	t2 = Thread(target=add,args=(4,))
	t1.start()
	t2.start()

x = 0	
test()
