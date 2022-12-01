#include <vector>
#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <numeric>
#include <future>

using namespace std;

//binary_semaphore signal{0};
counting_semaphore<1> signal{0};

vector<int> nums{};

void prepare_data(){
   nums.insert(nums.end(),{4,8,15,16,23,42});
   this_thread::sleep_for(2s);
   signal.release();
}

int process_data(){
   signal.acquire();
   return accumulate(nums.begin(),nums.end(),int());
}

int main(){
   cerr << "Application is just started..." << endl;
   thread t1(prepare_data);
   auto total = async(process_data);
   cerr << "Sum is " << total.get() << endl;
   t1.join(); 
   return 0;
}
