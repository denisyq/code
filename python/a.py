#!/usr/bin/python

def foo(a,b):
	print('{}==a,{}==b'.format(a,b))


a="hello world yes man."
choice=["http","ftp","hello"]

print([a for i in choice if a.startswith(i)])
