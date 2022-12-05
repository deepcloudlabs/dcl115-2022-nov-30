#include <thread>
#include <iostream>
#include <atomic>

using namespace std;
atomic<bool> x,y;

void fun1(){
 x.store(true,memory_order_acq_rel); 
};

void fun2(){
 y.store(true,memory_order_acq_rel); 
};

void gun1(){
   while(!y.load(memory_order_acq_rel));
   if(x.load(memory_order_acq_rel)){
     // always work!
     cerr << "gun1: y==true then x==true" << endl;
   }
};

void gun2(){
   while(!x.load(memory_order_acq_rel));
   if(y.load(memory_order_acq_rel)){
     // always work!
     cerr << "gun2: x==true then y==true" << endl;
   }
};

int main(){
   x=false; 
   y=false; 
   thread t1(fun1);  
   thread t2(fun2);  
   thread t3(gun1);  
   thread t4(gun2);  
   t1.join(); 
   t2.join(); 
   t3.join(); 
   t4.join(); 
   cerr << "Application is done." << endl;
   return 0;
}
