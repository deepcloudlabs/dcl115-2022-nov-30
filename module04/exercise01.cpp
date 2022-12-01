#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

static bool flag = false;
mutex mut;

void wait_for(){
  unique_lock<mutex> ul(mut); 
  while(!flag){
     ul.unlock();
     this_thread::sleep_for(100ms);
     ul.lock();
  }
}

void fun(){
   cerr << "fun runs now..." << endl;
   wait_for();
   cerr << "fun continue now..." << endl;
}

void gun(){
   cerr << "gun starts now..." << endl;
   this_thread::sleep_for(10s);
   cerr << "gun sets the flag now..." << endl;
   flag=true;
}

int main(){
   thread t1(fun);
   thread t2(fun);
   thread t3(fun);
   thread t4(fun);
   thread t5(gun);
   t1.join();
   t2.join();
   t3.join();
   t4.join();
   t5.join();
   return 0;
}
