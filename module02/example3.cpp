#include <iostream>
#include <thread>

class background_task {
	private:
		void do_something() const {
		   std::cout << "Doing something...\n" ;
		}
		void do_something_else() const {
		   std::cout << "Doing something else...\n" ;
		}
	public:
		void operator()() const {
			do_something();
			do_something_else();
		}
};

int main(){
   background_task f;
   std::thread t1((background_task()));
   std::thread t2{background_task()};
   t1.join(); 
   t2.join(); 

   return 0; 
}