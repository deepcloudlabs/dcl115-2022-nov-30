#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

void task(){
   cerr << "Running a task...";
   this_thread::sleep_for(5000ms);
   cerr << "done." << endl;
}

class thread_guard {
     thread& t;
public:
     explicit thread_guard(thread& t):t(t){}
     ~thread_guard(){
        if (t.joinable())
           t.join();
     }
};

void fun(){
  thread t1(task);
  thread_guard tg(t1);
  // throw;
  return;
}

int main(){
   cerr << "Application is just started..." << endl;
   fun();
   cerr << "Application is done." << endl;
   return 0;
}
