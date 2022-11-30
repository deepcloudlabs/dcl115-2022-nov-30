#include <thread>
#include <iostream>

using namespace std;

struct task {
 
  void do_taskA(){
     cout << "Running the task A." << endl;
     return;
  }

  void do_taskB(){
     cout << "Running the task B." << endl;
     return;
  }

  void operator()(){
     do_taskA();
     do_taskB();
  }
};

int main(){
   task my_task1{};
   thread t1(my_task1);  
   thread t2((task()));  
   thread t3{task()};  
   t1.join();
   t2.join();
   t3.join();
   cout << "Application is done." << endl;
   return 0;
}
