#include <latch>
#include <barrier>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std;

latch go(4);
//barrier go(4);
mutex m;

struct Worker {
   Worker(string name): name(name) {}
   void operator()(){
       {
         lock_guard<mutex> lg(m);
         cerr << name << " arrived to the barrier... " << endl;
       }
       go.arrive_and_wait();
       this_thread::sleep_for(750ms);
       //go.count_down();
       //go.wait();
       {
         lock_guard<mutex> lg(m);
         cerr << name << " sending a rest api call... " << endl;
       }
   }
private:
    string name;  
};

int main(){
    Worker worker1{"worker #1"};
    Worker worker2{"worker #2"};
    Worker worker3{"worker #3"};
    Worker worker4{"worker #4"};
    Worker worker5{"worker #5"};
    Worker worker6{"worker #6"};
    Worker worker7{"worker #7"};
    Worker worker8{"worker #8"};
    thread t1{worker1};
    thread t2{worker2};
    thread t3{worker3};
    thread t4{worker4};
    thread t5{worker5};
    thread t6{worker6};
    thread t7{worker7};
    thread t8{worker8};
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    return 0;
}
