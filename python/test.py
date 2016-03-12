#!/usr/local/bin/python


class A():
	def __init__(self):
		self.a = 1
	
class B(A):
	def __init__(self):
		super().__init__()
	def get(self):
		print(self.a)

class CountLatch:
	def __init__(self,start):
		self.start=start
	def __iter__(self):
		n = self.start
		while n>0:
			yield n
			n -= 1
	'''
	def __reversed__(self):
		n = 1
		while n<=self.start:
			yield n
			n += 1
	'''

c=CountLatch(5)
from itertools import dropwhile
with open("tmp") as f:
	for lineno, line in enumerate(f,1):
		words=[word.strip().lower() for word in line.split()]
		print(lineno,words)
