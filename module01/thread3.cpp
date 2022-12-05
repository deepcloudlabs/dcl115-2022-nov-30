#include <iostream>
#include <thread>

struct fun {
	void operator()(){
		std::cout << "Hello Concurrent World!\n";	
	}
};

int main() {
 fun f;
 std::thread t(f);
 t.join();
 std::cout << "Hello Concurrent Mars!\n"; 
}
