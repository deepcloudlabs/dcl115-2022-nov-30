#include <thread>
#include <iostream>
#include <atomic>

using namespace std;
atomic<bool> x,y;

void fun(){
 x.store(true,memory_order_seq_cst); 
 y.store(true,memory_order_seq_cst); 
};

void gun(){
   while(!y.load(memory_order_seq_cst));
   if(x.load(memory_order_seq_cst)){
     // always works
     cerr << "y==true then x==true" << endl;
   }
};

int main(){
   x = true;
   y = true;
   thread t1(fun);  
   thread t2(gun);  
   t1.join(); 
   t2.join(); 
   cerr << "Application is done." << endl;
   return 0;
}
