#!/usr/bin/python

import threading
import time
def worker():
	print(threading.get_ident(),"work begins")
	print(threading.get_ident(),"active_count",threading.active_count())

t = list(range(5))
for i in range(5):
	t[i] = threading.Thread(target=worker)
	t[i].start()
print("the main thread:",threading.current_thread())
time.sleep(5)

for i in threading.enumerate():
	if i is not threading.current_thread():
		i.join()
print(threading.active_count())
