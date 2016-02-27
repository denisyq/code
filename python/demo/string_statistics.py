#!/usr/bin/python
'''
#statistic the num of every single letter
'''
from collections import defaultdict

d=defaultdict(int)
s="helloworld"
for i in s:
	d[i] += 1
print(sorted(list(d.items()),key=lambda x:x[1]))
	

d=defaultdict(int)
s=[1,2,3,4,3,2,34,4,2,2,1]
for i in s:
	d[i] += 1
print(sorted(list(d.items()),key=lambda x:x[1],reverse=True)[0][1])
