#include <iostream>
#include <thread>

void do_some_work() {
   std::cout << "Running do_some_work()\n" ;
}

int main(){
   std::thread my_thread(do_some_work);
   my_thread.join(); 
   return 0; 
}
