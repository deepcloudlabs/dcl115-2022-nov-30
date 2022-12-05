#include <atomic>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <algorithm>
#include <random>
#include <functional>
#include <iostream>

using namespace std;
using namespace std::chrono;

class spinlock_mutex {
    atomic_flag flag;
public:
    spinlock_mutex():flag(ATOMIC_FLAG_INIT){}
    void lock(){
        while(flag.test_and_set(memory_order_acquire));
    }
    void unlock(){
        flag.clear(memory_order_release);
    }
};

vector<int> some_vector;
spinlock_mutex mut;
mt19937 rng(high_resolution_clock::now().time_since_epoch().count());


void add_to_vector(int new_value){
	lock_guard<spinlock_mutex> guard(mut);
	some_vector.push_back(new_value);
} 

bool vector_contains(int value){
	lock_guard<spinlock_mutex> guard(mut);
    return find(some_vector.begin(),
	            some_vector.end(),value)
				!=some_vector.end();
} 

void fun(){
	for (int i=0;i<100;++i){
	    int random_value;
		do {
		  random_value= rng();
		  random_value= random_value<0? -random_value:random_value;
		} while (vector_contains(random_value)) ;
		add_to_vector(random_value);
	}
}

int main(){
	vector<thread> threads;
	for (int i=0;i<100;++i)
	    threads.push_back(thread(fun));
	for_each(threads.begin(),threads.end(),mem_fn(&thread::join));	
	sort(some_vector.begin(),
	         some_vector.end(),
			 [](const int &a,const int &b){
			     return a<=b ;
			 });
	for_each(some_vector.begin(),
	         some_vector.end(),
			 [](const int &i){
			     cout << i << endl ;
			 });
}
