#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

using namespace std;

mutex cout_mutex;

thread_local string s("hello mars "); // thread stack 

void add(string const& s2){
  s += s2;
  lock_guard<mutex> lg(cout_mutex);
  cerr << s << endl; 
  cerr << "&s: " << &s << endl; 
  cerr << endl;
}

int main(){
    thread t1(add,"t1 ");   
    thread t2(add,"t2 ");   
    thread t3(add,"t3 ");   
    thread t4(add,"t4 ");   
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cerr << s << endl; 
    cerr << "&s: " << &s << endl; 
    cerr << endl;
    return 0;
}
