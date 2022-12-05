#include <iostream>
#include <thread>
#include <functional>
#include <future>
#include <chrono>

using namespace std;

long fun(long n){
  long step=0;
  while(n>1){
    n = (n%2==1) ? 3*n+1 : n/2;
    ++step;
    this_thread::sleep_for(100ms);
  }
  return step;
}

int main(){
    packaged_task<long()> task(bind(fun,1234567));
    future<long> step = task.get_future();
    task();
    cerr << "steps: " << step.get() << endl;
    return 0;
}
