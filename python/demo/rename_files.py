#!/usr/bin/python
'''
#rename file ext
'''
import os
import os.path
'''
#solution1
for f in os.listdir():
	if f.endswith("txt"):
		new_file=os.path.splitext(f)[0]+".cpp"
		os.rename(f,new_file)
		print("rename done, new file: ",new_file)
'''

#solution2
pyfiles = [f for f in os.listdir() if f.endswith(".cpp")]
for f in pyfiles:
	new_file=os.path.splitext(f)[0]+".py"
	os.rename(f,new_file)
	print("rename done, new file: ",new_file)

#solution3
import glob
pyfiles=glob.glob('*.py')

#solution4
import fnmatch
pyfiles = [name for name in os.listdir() if fnmatch.fnmatch(name,'*.py')]
