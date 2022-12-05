#include <iostream>
#include <thread>

struct fun {
	void operator()(){
		std::cout << "Hello Concurrent World!\n";	
	}
};

int main() {
 std::thread t((fun()));
 t.join();
 std::cout << "Hello Concurrent Mars!\n"; 
}
