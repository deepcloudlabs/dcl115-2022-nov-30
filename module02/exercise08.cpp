#include <thread>
#include <iostream>
#include <functional>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

void task(int task_id){
  cerr << "Running task #" << task_id 
       << ", executed by the thread #" << this_thread::get_id()
       << endl;
}

void fun(){
  vector<thread> threads; 
  cerr << "Creating threads..." << endl;
  for (auto i=1;i<=50;i++){
     threads.push_back(thread(task,i));
  }
  cerr << "Joining threads..." << endl;
  for_each(threads.begin(),threads.end(),mem_fn(&thread::join));
  cerr << "Leaving fun()..." << endl;
}

int main(){
   cerr << "Application is just started..." << endl;
   fun();
   cerr << "Application is done." << endl;
   return 0;
}
