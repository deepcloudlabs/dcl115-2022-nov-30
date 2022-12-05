#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mut;

void fun(){
   cerr << this_thread::get_id() << " is just started..." << endl;
   mut.lock(); // parking -> voluntary ctx
   this_thread::sleep_for(10000ms);
   mut.unlock();   
   cerr << this_thread::get_id() << " is done." << endl;
}

int main(){
    cerr << "Application is just started..." << endl;
    thread t1(fun);
    thread t2(fun);
    thread t3(fun);
    thread t4(fun);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cerr << "Application is done." << endl;
    return 0;
}
