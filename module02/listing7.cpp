#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

void do_work(unsigned id){
	std::cout << "Working with id " << id << std::endl;
}

void f(){
	std::vector<std::thread> threads;
	for (unsigned i=0;i<20;++i){
		threads.push_back(std::thread(do_work,i));
	}
	std::for_each(threads.begin(),threads.end(),std::mem_fn(&std::thread::join));
	std::cout << "All threads are done!" << std::endl;	
}

int main(){
	f();
    return 0;
}