#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <mutex>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::chrono;

vector<int> some_vector;
mutex some_mutex;

void add_to_vector(int new_value){
  lock_guard<mutex> guard(some_mutex);
  some_vector.push_back(new_value);
}

bool vector_contains(int value_to_find){
  lock_guard<mutex> guard(some_mutex);
  return find(some_vector.begin(),some_vector.end(),value_to_find)!= some_vector.end();
}

random_device rdev ;
mt19937 rng1( rdev() ) ;
mt19937 rng2( high_resolution_clock::now().time_since_epoch().count() ) ;
	
void fun(){
	for (int i=0;i<10;++i){
	    int candidate; 
	    do{
			candidate= 1+rng2()%49;
		}while(vector_contains(candidate));
 	    add_to_vector(candidate);
	}
}

int main(){
     thread t1(fun);
	 thread t2(fun);
	 t1.join();
	 t2.join();
	 cout<< "Done." << endl ;
	 sort(some_vector.begin(),some_vector.end(), [](const int& a,const int &b) { return a>= b; });
	 for_each(some_vector.begin(),some_vector.end(), [](const int & i) { cout << i << endl; });
	return 0;
}
