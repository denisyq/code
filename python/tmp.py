#!/usr/bin/python

#fileinput.filename()		#
#fileinput.fileno()			#fd number
#fileinput.lineno()			#line increase after next file
#fileinput.filelineno()		#line increasa in one file
#fileinput.isfirstline()	#
#fileinput.isstdin()
#fileinput.close()

def isOdds(data):
	if data % 2 == 1:
		return data
def getPrime(data):
	ret=list()
	return ret.append(x for x in data if isPrime(x))

l=[1,2,3,4]
print(getPrime(l))
