#include "threadsafe_queue.h"
#include <mutex>
#include <memory>

using namespace std;

template<typename T>
void threadsafe_queue<T>::push(T& new_value){
	lock_guard<mutex> lk(mut);
	data_queue.push(new_value);
	data_cond.notify_one();
}

template<typename T>
void threadsafe_queue<T>::pop(T& value){
	unique_lock<mutex> lk(mut);
	data_cond.wait(lk,[this]{return !data_queue.empty();});
	value=data_queue.front();
	data_queue.pop();		
}

template<typename T>
T threadsafe_queue<T>::pop(){
	unique_lock<mutex> lk(mut);
	data_cond.wait(lk,[this]{return !data_queue.empty();});
    T value= data_queue.front();	
	data_queue.pop();		
	return value;
}
