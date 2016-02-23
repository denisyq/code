#!/usr/bin/python

def lines(file):
	for line in file:
		yield line
		yield '\n'

def blocks(file):
	block=[]
	for line in lines(file):
		if line.strip():
			block.append(line)
		elif block:
			''.join(block).strip()
			block=[]
		'''
for line in open("filename"):
	tmp=line.rstrip('\n')
	if tmp:
		print tmp
def isstring(str):
	try: str + ''
	except TypeError: pass
	else: raise TypeError
	print str	

#isstring(123)
isstring("hello")	
#isstring(list(range(4)))

'''

print("helo")
