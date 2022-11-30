#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

static int global_state = 0;
mutex mut;

void race(int id){
   cerr << id << ", " << this_thread::get_id() << " is running race() ..." << endl;
   {
      for (auto i=0;i<1'000'000'000;++i) // critical section -> function body
      {
         lock_guard<mutex> guard(mut); 
         // cerr << id << ", " <<  this_thread::get_id() << " gets the lock..." << endl;
         global_state++;
         // cerr << id << ", " << this_thread::get_id() << " release the lock..." << endl;
      }
   }
}

int main(){
   thread t1(race,1);
   thread t2(race,2);
   thread t3(race,3);
   t1.join();
   t2.join();
   t3.join();
   cerr << "global_state: " << global_state << endl;
   return 0;
}
