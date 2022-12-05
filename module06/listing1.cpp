#include <iostream>
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
#include <thread>

#include "domain.h"

using namespace std;

struct empty_stack:exception{
    const char* what() const throw()
    {
        return "empty stack";
    }
};

template<typename T>
class threadsafe_stack{
private:
    stack<T> data;
    mutable mutex m;
public:
    threadsafe_stack(){}
    threadsafe_stack(const threadsafe_stack& other){
        lock_guard<mutex> lock(other.m);
        data=other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value){
        lock_guard<mutex> lock(m);
        data.push(move(new_value));
    }
	
    shared_ptr<T> pop(){
        lock_guard<mutex> lock(m);
        if(data.empty()) throw empty_stack();
        shared_ptr<T> const res(
            make_shared<T>(move(data.top())));
        data.pop();
        return res;
    }
	
    void pop(T& value){
        lock_guard<mutex> lock(m);
        if(data.empty()) throw empty_stack();
        value=move(data.top());
        data.pop();
    }
	
    bool empty() const {
        lock_guard<mutex> lock(m);
        return data.empty();
    }
	
    int size() const {
        lock_guard<mutex> lock(m);
        return data.size();
    }
	
};

static threadsafe_stack<programmer> ts_stack;

void fun1(){
	ts_stack.push(programmer(string("Jack"),string("Sheppard"),41,programming_language(string("c++"),8)));
	ts_stack.push(programmer(string("Kate"),string("Austen"),36,programming_language(string("java"),6)));
	ts_stack.push(programmer(string("Sun"),string("Kwon"),36,programming_language(string("scala"),5)));
	ts_stack.push(programmer(string("Hugo"),string("Reyes"),29,programming_language(string("python"),7)));
	ts_stack.push(programmer(string("John"),string("Lock"),29,programming_language(string("perl"),10)));
	ts_stack.push(programmer(string("Claire"),string("Littleton"),27,programming_language(string("perl"),4)));
	ts_stack.push(programmer(string("Juliet"),string("Burke"),36,programming_language(string("go"),9)));
	ts_stack.push(programmer(string("Richard"),string("Alpert"),37,programming_language(string("f#"),9)));
	ts_stack.push(programmer(string("Shannon"),string("Rutherford"),27,programming_language(string("pl/1"),2)));
	ts_stack.push(programmer(string("Alex"),string("Rousseau"),21,programming_language(string("cobol"),2)));
}

void fun2(){
	ts_stack.push(programmer(string("Ben"),string("Linus"),47,programming_language(string("c#"),9)));
	ts_stack.push(programmer(string("James"),string("Ford"),47,programming_language(string("c"),6)));
	ts_stack.push(programmer(string("Jin"),string("Kwon"),36,programming_language(string("lisp"),4)));
	ts_stack.push(programmer(string("Desmond"),string("Hume"),38,programming_language(string("c#"),9)));
	ts_stack.push(programmer(string("Charlie"),string("Pace"),32,programming_language(string("c"),6)));
	ts_stack.push(programmer(string("Sayyid"),string("Jarrah"),41,programming_language(string("lisp"),4)));
	ts_stack.push(programmer(string("Miles"),string("Leung"),32,programming_language(string("ada"),4)));
	ts_stack.push(programmer(string("Walt"),string("Llyod"),16,programming_language(string("bash"),5)));
	ts_stack.push(programmer(string("Daniel"),string("Rousseau"),49,programming_language(string("cobol"),7)));
}

void fun3(){
	ts_stack.push(programmer(string("Daniel"),string("Faraday"),37,programming_language(string("c#"),9)));
	ts_stack.push(programmer(string("Frank"),string("Lapidus"),47,programming_language(string("c"),6)));
	ts_stack.push(programmer(string("Boone"),string("Carlyle"),36,programming_language(string("lisp"),4)));
	ts_stack.push(programmer(string("Mr."),string("Eko"),38,programming_language(string("c#"),9)));
	ts_stack.push(programmer(string("Charlie"),string("Pace"),32,programming_language(string("c"),6)));
	ts_stack.push(programmer(string("Ana Lucia"),string("Cortez"),32,programming_language(string("lisp"),4)));
	ts_stack.push(programmer(string("Bernard"),string("Nadler"),57,programming_language(string("ada"),4)));
	ts_stack.push(programmer(string("Rose"),string("Nadler"),53,programming_language(string("bash"),5)));
	ts_stack.push(programmer(string("Niki"),string("Fernandez"),32,programming_language(string("awk"),3)));
	
}

int main(){
	thread t1(fun1);
	thread t2(fun2);
	thread t3(fun3);
	t1.join();
	t2.join();
	t3.join();
	cout << "There are " << ts_stack.size() << " programmers in the stack!" << endl; 
	while (!ts_stack.empty()){
	  cout << *ts_stack.pop() << endl ; 
	}  
	return 0;
	
}

