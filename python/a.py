#!/usr/bin/python

def foo(a,b):
	print('{}==a,{}==b'.format(a,b))


import re
text=[]
with open("tmp") as f:
	for line in f.readlines():
		add = [str for str in re.split(r'[\s,.:]\s*',line) if len(str) >=2]
		text.extend(add)

from collections import Counter
c = Counter(text)
for a,b in c.most_common(10):
	print a,b

