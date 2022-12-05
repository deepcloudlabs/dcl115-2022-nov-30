#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

struct task {
  int &data; 
  task(int& data):data(data){}

  void operator()(){
      for(auto j=0;j<1'000'000;++j)
        data++;
      cerr << "data: " << data << endl; 
  }
};

int main(){
   int my_local_data=0; // main thread's stack
   task my_task1{my_local_data};
   thread t1(my_task1);  
   thread t2(my_task1);  
   thread t3(my_task1);  
   t1.join(); 
   t2.join(); 
   t3.join(); 
   cerr << "Application is done." << endl;
   cerr << "my_local_data: " << my_local_data << endl;
   return 0;
}
