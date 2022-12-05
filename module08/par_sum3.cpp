#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <algorithm>
#include <time.h>

using namespace std;

const int SIZE=80000000;
vector<int> numbers(SIZE);

void init_problem(vector<int> &vec,int size){
	for (int i=1;i<=size;++i)
	    vec.push_back(i);
}

template <typename iter>
int parallel_sum(iter begin, iter end){
    long len= distance(begin,end);
    if (len <= 20000000){
	   return accumulate(begin,end,int()); 
	} 	
	iter mid= begin + len /2;
	auto handle_left= 
	  async(launch::async,
	     parallel_sum<iter>,begin,mid);		 
	auto handle_right= 
	  async(launch::async,
	     parallel_sum<iter>,mid,end);		 
	return handle_left.get()+
	       handle_right.get();
}

int main(){
	init_problem(numbers,SIZE);
	int num_cores= 
	     thread::hardware_concurrency();
	int per_thread= SIZE / num_cores;
	struct timespec begin_time, end_time;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC,&begin_time);	
	int sum= parallel_sum(numbers.begin(),numbers.end());
	clock_gettime(CLOCK_MONOTONIC,&end_time);
	elapsed = 
	   end_time.tv_sec - begin_time.tv_sec;
	elapsed += (end_time.tv_nsec - begin_time.tv_nsec) / 1000000000.0;		
	cout << "Sum (parallel): " 
	     << sum 
		 << " @ "
		 << elapsed
		 << endl ;	
}




