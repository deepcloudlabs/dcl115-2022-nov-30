#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;

bool flag=false;
mutex m;

void wait_for_flag(){
	unique_lock<mutex> lk(m);
	while(!flag){
		lk.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));
		lk.lock();
	}
}

void fun(){
	cout << "Long running process.." << endl;
	this_thread::sleep_for(chrono::milliseconds(10000));
	flag=true;
	cout << "This is end of fun!" << endl ;
}

void gun(){
	cout << "Waiting for long running process to end.." << endl;
	wait_for_flag();
	cout << "Finally, long running process has ended!" << endl;
}

int main(){
	thread t1(fun);
	thread t2(gun);	
	
	t1.join();
	t2.join();	
	cout << "This is end of main." << endl;	
}	