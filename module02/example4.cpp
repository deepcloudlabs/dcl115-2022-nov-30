#include <iostream>
#include <thread>

void do_something() {
   std::cout << "Doing something...\n" ;
}
void do_something_else() {
   std::cout << "Doing something else...\n" ;
}

int main(){
   std::thread t1([]{
      do_something();
      do_something_else();
   });   
   t1.join(); 
   return 0; 
}
