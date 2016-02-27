#!/usr/bin/python
'''
#priority_queue
'''
import heapq

class priority_queue:
	def __init__(self):
		self._queue=[]
		self._index=0
	#data could be string, heapq.heappush use tuple[0] to sort.
	#if need descending order, let priority negative
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

	

