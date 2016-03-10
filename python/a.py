#!/usr/local/bin/python


class A():
	def __init__(self):
		self.a = 1
	
class B(A):
	def __init__(self):
		super().__init__()
	def get(self):
		print(self.a)

b=B()
print(b.get())
