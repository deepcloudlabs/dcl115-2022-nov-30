#include <thread>
#include <iostream>

using namespace std;

// global state
static int my_data;

void do_taskA(){ // mutator function!
   cout << "Running the task A." << endl;
   my_data++;
   return;
}

void do_taskB(){ // mutator function!
   cout << "Running the task B." << endl;
   my_data++;
   return;
}

int main(){
   int x = 42; // main thread's Stack
   thread t1([&x](){ // t1's Stack
       int y= 108; // t1's stack
       do_taskA();
       do_taskB();
       x++; // it is NOT pure anymore! -> it is NOT TS!!!
   }); 
   x++; 
   t1.join();
   cout << "Application is done." << endl;
   return 0;
}
