#!/usr/bin/python
'''
statistic the num of every single letter
use defaultdict and Counter
'''
from collections import defaultdict
from collections import Counter

d=defaultdict(int)
s="helloworld"
for i in s:
	d[i] += 1
print(sorted(list(d.items()),key=lambda x:x[1],reverse=True))
	

dd=defaultdict(int)
ss=[1,2,3,4,3,2,34,4,2,2,1]
for i in ss:
	dd[i] += 1
print(sorted(list(dd.items()),key=lambda x:x[1],reverse=True)[0][1])

c=Counter(s)
print(c.most_common(len(c)))

