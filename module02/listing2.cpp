#include <iostream>
#include <thread>

struct fun {
	int& i;
	fun(int& k):i(k){}
	void do_something(int value){
		i= value;
   	    std::cout << "i= " << i << std::endl ;
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
	fun my_fun(some_local_state);
	std::thread my_thread(my_fun);
	try{
	    do_something_in_current_thread();
	}catch(...){
	    my_thread.join();
		throw;
	}
	my_thread.join();	
	return 0;
}

int main(){
    foo();
	int lost[] = {4,8,15,16,23,42};
    return 0;
}