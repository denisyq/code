

def leftpad(string,n):
	tmp = ' '* (n-len(string))
	return tmp + string

s="hello;world"
print(leftpad(s,15))
	
