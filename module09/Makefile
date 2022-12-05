thread_pool:	thread_pool.cpp threadsafe_queue.o
	g++ -std=c++23 -o thread_pool thread_pool.cpp threadsafe_queue.o

threadsafe_queue.o: threadsafe_queue.cpp 	
	g++ -std=c++23 -c threadsafe_queue.cpp

clean: 
	rm -f *.o thread_pool
