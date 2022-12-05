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
			do_something(i);
		}
	}
};

int foo() {
	int some_local_state=0;
	fun my_fun(some_local_state);
	std::thread my_thread(my_fun);
	my_thread.detach();
	return 0;
}

int main(){
    foo();
	int lost[] = {4,8,15,16,23,42};
    return 0;
}