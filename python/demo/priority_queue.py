#!/usr/bin/python
'''
#priority_queue
'''
import heapq

class priority_queue:
	def __init__(self):
		self._queue=[]
		self._index=0
	#如果是string，使用首字母排列
	#基本上是从小到大排列，如果需要大到小，需要把priority设置为负数
	def push(self,data,priority):
		heapq.heappush(self._queue,(priority,data))   #asceding order
		#heapq.heappush(self._queue,(-priority,data)) #descending order
		self._index += 1
	
	def pop(self):
		self._index -= 1
		return heapq.heappop(self._queue)[1]
	
	def size(self):
		return self._index;


pri=priority_queue()
pri.push("minor",1)
pri.push("major",2)

print(pri.pop(),pri.size())

	

