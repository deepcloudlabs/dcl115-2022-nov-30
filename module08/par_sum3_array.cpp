#include <iostream>
#include <thread>
#include <future>
#include <algorithm>
#include <time.h>

using namespace std;

const int SIZE=80000000;
int numbers[SIZE];

template <typename iter>
void init_problem(iter beg,iter end){
    int i=1;
	for (iter p=beg;p!=end;p++,++i)
	    *p= i;
}

template <typename iter>
int parallel_sum(iter begin, iter end){
    long len= distance(begin,end);
    if (len <= 10000000){
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
	init_problem(numbers,numbers+SIZE);
	int num_cores= thread::hardware_concurrency();
	struct timespec begin_time, end_time;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC,&begin_time);	
	int sum= parallel_sum(numbers+0,numbers+SIZE);
	clock_gettime(CLOCK_MONOTONIC,&end_time);
	elapsed = 
	   end_time.tv_sec - begin_time.tv_sec;
	elapsed += (end_time.tv_nsec - begin_time.tv_nsec) / 1000000000.0;		
	cout << "Sum (parallel): " << sum << " @ " << elapsed	 << endl ;	
}




