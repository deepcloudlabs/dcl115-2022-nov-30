#include <iostream>
#include <atomic>
#include <thread>

using namespace std;

struct barrier {
    atomic<int> counter[2];
    atomic<int> lock[2];
    atomic<int> cur_idx;
    int thread_count;
	barrier(int parties) : thread_count(parties) {		
	}
    bool wait(){
		int idx  = cur_idx.load();
		if(lock[idx].load() == 0){
			lock[idx].store(1);
		}
		int val = counter[idx].fetch_add(1);
		if(val >= thread_count - 1){
			counter[idx].store(0);
			cur_idx.fetch_xor(1);
			lock[idx].store(0);
			return true;
		}
		while(lock[idx].load() == 1);
		return false;	
	}
};

barrier bar(4);

void fun(){
	bar.wait();
	cout << "I am here " << this_thread::get_id() << endl ;
}

int main(){
	thread t1(fun);
	thread t2(fun);
	thread t3(fun);
	thread t4(fun);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}
