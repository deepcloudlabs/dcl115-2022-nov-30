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
   t1.detach();
   t2.detach();
   t3.detach();
   cerr << "is t1 joinable?: " << t1.joinable() << endl;
   cerr << "is t2 joinable?: " << t2.joinable() << endl;
   cerr << "is t3 joinable?: " << t3.joinable() << endl;
   if (t1.joinable())
      t1.join(); 
   this_thread::sleep_for(5000ms);
   cerr << "Application is done." << endl;
   cerr << "my_local_data: " << my_local_data << endl;
   return 0;
}
