#!/usr/bin/python
'''
#delete the duplicate item
'''
l=[1,5,2,1,9,1,5,10]
s=set(l) # sequence will change


def del_dup(items):
	seen=set()
	for item in items:
		if item not in seen:
			yield item
			seen.add(item)

print(list(del_dup(l))) #sequence will not change


#why should sequence not changed?
#Answer: readline and process and keep line sequence in file
