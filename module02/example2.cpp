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
   std::thread my_thread(f);
   my_thread.join(); 
   return 0; 
}