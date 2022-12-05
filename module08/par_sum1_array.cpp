#include <iostream>
#include <thread>
#include <vector>
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
	return accumulate(begin,end,int());
}

int main(){
	init_problem(numbers,numbers+SIZE);
	int num_cores= 
	     thread::hardware_concurrency();
	int per_thread= SIZE / num_cores;
	struct timespec begin_time, end_time;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC,&begin_time);	
	vector<future<int>> partial_sums;
	auto beg= numbers;
	auto end= beg + per_thread;
	for (int i=0;i<num_cores;++i){
		partial_sums.push_back(
		async(
		parallel_sum<int*>,
		beg,end
		));
		beg= beg + per_thread;
		end= end + per_thread;
	}
	int sum=0;
	for (auto & fut : partial_sums)
	    sum += fut.get();
	clock_gettime(CLOCK_MONOTONIC,&end_time);
	elapsed = 
	   end_time.tv_sec - begin_time.tv_sec;
	elapsed += (end_time.tv_nsec - begin_time.tv_nsec) / 1000000000.0;		
	cout << "Sum (parallel): " 
	     << sum 
		 << " @ "
		 << elapsed
		 << endl ;
	clock_gettime(CLOCK_MONOTONIC,&begin_time);	
	sum= accumulate(numbers,numbers+SIZE,int()); 
	clock_gettime(CLOCK_MONOTONIC,&end_time);
	elapsed = 
	   end_time.tv_sec - begin_time.tv_sec;
	elapsed += (end_time.tv_nsec - begin_time.tv_nsec) / 1000000000.0;
	
	cout << "Sum (serial): " 
	     <<  sum
		 << " @ "
		 << elapsed
		 << endl ;
	
}




