import threading


# same as threads.c
# More python examples can be foun here


global counter;
counter = 0;

def doSomeThing():
    """thread worker function"""
    global counter;			#counter is global variable
    threadLock.acquire()
    counter = counter +1;	#needs lock as explained in the .c file
    thread_name = counter;
    threadLock.release()
    print 'Job %d started\n' % thread_name
    for i in range(20000):
    	pass
    print 'Job %d finished\n' % thread_name


threadLock = threading.Lock()
threads = []
for i in range(2):
    t = threading.Thread(target=doSomeThing, args=( ) )
    t.setDaemon(True)
    threads.append(t)	#save the threads on a list
    t.start()			#start the thread

threads[0].join();
threads[1].join();

print 'main exiting';