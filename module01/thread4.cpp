#include <iostream>
#include <thread>

int main() {
 std::thread t( 
     []() {
	    std::cout << "Hello Concurrent World!\n";
	});
 t.join();
 std::cout << "Hello Concurrent Mars!\n"; 
}
