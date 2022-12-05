#include <iostream>
#include <thread>
#include "thread_guard.h"

struct fun {
	int& i;
	fun(int& k):i(k){}
	void do_something(int value){
		i= value;
	}
	void operator()() {
		for(unsigned j=0;j<1000000;++j) {
			do_something(j);
		}
	}
};

void do_something_in_current_thread(){
    std::cout << "Doing something in current thread" << std::endl;
}

int foo() {
	int some_local_state=0;
	fun my_fun (some_local_state);
	std::thread t(my_fun);
	thread_guard g(t);
	do_something_in_current_thread();
	return 0;
}

int main(){
    foo();
	int lost[] = {4,8,15,16,23,42};
    return 0;
}