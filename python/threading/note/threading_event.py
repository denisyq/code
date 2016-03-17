#!/usr/bin/python

#########################
# Event API:
# ev = threading.Event()
# ev.set()
# ev.wait(timeout=None)
# ev.is_set()
# ev.clear()
#########################
import threading
import time
def work():
	print(threading.current_thread().getName(), ":new thread work begins")
	time.sleep(2)
	event_start.set()
	print(threading.current_thread().getName(), ":new thread works done")

event_start = threading.Event()

threading.Thread(target=work).start()
print(threading.current_thread().getName(),":wait for thread to start!")
event_start.wait()
print(threading.current_thread().getName(),":new thread start!")



