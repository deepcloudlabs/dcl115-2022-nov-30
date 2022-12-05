#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;
#pragma once

template<typename T>
class threadsafe_queue {
		mutex mut;
		queue<T> data_queue;
		condition_variable data_cond;
	public:
		threadsafe_queue(){}
		threadsafe_queue(const threadsafe_queue&) = delete ;
		threadsafe_queue& operator=(const threadsafe_queue&) = delete;
		void push(T& new_value);
		void pop(T& value);
		T pop();
		bool empty() const {
		   lock_guard<mutex> lk(mut);
		   return data_queue.empty();
		}
};