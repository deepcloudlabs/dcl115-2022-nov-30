#include <thread>
#include <iostream>
#include <atomic>

using namespace std;
atomic<bool> x,y;

void fun(){
 x.store(true,memory_order_relaxed); 
 y.store(true,memory_order_release); 
};

void gun(){
   while(!y.load(memory_order_acquire));
   if(x.load(memory_order_relaxed)){
     // always works
     cerr << "y==true then x==true" << endl;
   }
};

int main(){
   x=false; 
   y=false; 
   thread t1(fun);  
   thread t2(gun);  
   t1.join(); 
   t2.join(); 
   cerr << "Application is done." << endl;
   return 0;
}
