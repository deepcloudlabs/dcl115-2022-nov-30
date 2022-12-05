all:	hello_world.cpp thread1.cpp thread2.cpp thread3.cpp thread4.cpp 
	g++ -std=c++20 -lpthread -o hello_world hello_world.cpp
	g++ -std=c++20 -lpthread -o thread1 thread1.cpp
	g++ -std=c++20 -lpthread -o thread2 thread2.cpp
	g++ -std=c++20 -lpthread -o thread3 thread3.cpp
	g++ -std=c++20 -lpthread -o thread4 thread4.cpp
	
clean: 
	rm thread1 thread2 thread3 thread4 hello_world
