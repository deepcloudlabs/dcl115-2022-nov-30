#include <iostream>
#include <thread>
#include <functional>
#include <future>
#include <chrono>

using namespace std;

int main(){
    cerr << this_thread::get_id() << " runs main() function " << endl;
    packaged_task<long(long)> task([](long n){
      cerr << this_thread::get_id() << " runs lambda expression " << endl;
      long step=0;
      while(n>1){
        n = (n%2==1) ? 3*n+1 : n/2;
        ++step;
      }
      return step;
    });
    future<long> step = task.get_future();
    //task(1234567);
    thread t1(move(task),1234567);
    t1.join();
    cerr << "steps: " << step.get() << endl;
    return 0;
}
