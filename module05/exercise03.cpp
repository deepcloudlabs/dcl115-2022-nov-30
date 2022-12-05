#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class SpinLock {
   atomic_flag flag = ATOMIC_FLAG_INIT;
public:
   void lock(){
      while(flag.test_and_set());
   }
   void unlock(){
      flag.clear();
   }

};
SpinLock spinLock;

int bind_self_to_core(int core_id) {
    core_id = 2; //core_id % 1 ;

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

void fun(){
   static int i=0;
   bind_self_to_core(i++);
   cerr << this_thread::get_id() << " is just started..." << endl;
   spinLock.lock();
   this_thread::sleep_for(10000ms);
   spinLock.unlock();   
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
