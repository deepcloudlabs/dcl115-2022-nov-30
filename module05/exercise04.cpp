#include <iostream>
#include <thread>
#include <atomic>
#include <numeric>
#include <vector>
#include <chrono>

using namespace std;

vector<int> my_numbers{};
atomic_flag flag{};

void populate(){
   cerr << this_thread::get_id() << " Populate is just started..." << endl;
   my_numbers.insert(my_numbers.end(), {4,8,15,16,23,42});
   flag.test_and_set();
   flag.notify_one();
   cerr << this_thread::get_id() << " Populate is done." << endl;
}

void process(){
   cerr << this_thread::get_id() << " Process is just started..." << endl;
   flag.wait(false);
   auto total = accumulate(my_numbers.begin(),my_numbers.end(),int());
   cerr << this_thread::get_id() << " Process is done: " << total << endl;
}

int main(){
    cerr << "Application is just started..." << endl;
    thread t1(populate);
    thread t2(process);
    t1.join();
    t2.join();
    cerr << "Application is done." << endl;
    return 0;
}
