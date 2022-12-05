#include <thread>
#include <iostream>
#include <atomic>

using namespace std;
atomic<int> counter{0};

void fun(){
  for(auto j=0;j<500'000'000;++j)
     counter++;
};

int main(){
   thread t1(fun);  
   thread t2(fun);  
   thread t3(fun);  
   t1.join(); 
   t2.join(); 
   t3.join(); 
   cerr << "Application is done: " 
        << counter.load() 
        << endl;
   return 0;
}
