#include <thread>
#include <iostream>

using namespace std;

void do_taskA(){
   cout << "Running the task A." << endl;
   return;
}

void do_taskB(){
   cout << "Running the task B." << endl;
   return;
}

int main(){
   thread t1([](){ // lambda expression -> functional programming: pure function -> TS
       do_taskA();
       do_taskB();
   });  
   t1.join();
   cout << "Application is done." << endl;
   return 0;
}
