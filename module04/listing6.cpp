#include <iostream>
#include <future>
#include <functional>
#include <thread>

using namespace std;

long _3n_plus_1(long n){
	long step=0;
	while (n>1){
	   n= (n%2==1) ? 3*n+1:n/2;
	   ++step;
	}
	return step;
}

long __3n_plus_1(future<long>& _future){
	long step=0;
	long n= _future.get();
	while (n>1){
	   n= (n%2==1) ? 3*n+1:n/2;
	   ++step;
	}
	return step;
}

void task_lambda(){
    std::packaged_task<long(long)> task(
	    [](long n){	
			long step=0;
			while (n>1){
			   n= (n%2==1) ? 3*n+1:n/2;
			   ++step;
			}
			return step;
		}
	);
    std::future<long> step = task.get_future(); 
    task(837799); 
    cout << "837799 takes " << step.get() << " steps!" << endl;	
}
 
void task_bind(){
    std::packaged_task<long()> task(bind(_3n_plus_1,837799));
    std::future<long> step = task.get_future(); 
    task(); 
    cout << "837799 takes " << step.get() << " steps!" << endl;	
}

void task_thread(){
	packaged_task<long(long)> task(_3n_plus_1);	
    future<long> step= task.get_future();
	thread t(move(task),837799);
	cout << "837799 takes " << step.get() << " steps!" << endl;	
	t.join();	
}

void task_promise(){
	promise<long> number;
	future<long> n= number.get_future();		
	packaged_task<long(future<long>&)> task(__3n_plus_1);		
	future<long> step= task.get_future();	
	thread t(move(task),ref(n));
	number.set_value(837799);
	cout << "837799 takes " << step.get() << " steps!" << endl;	
	t.join();
}


int main(){
   task_lambda();
   task_bind();
   task_thread();
   task_promise();
   return 0;
}	
