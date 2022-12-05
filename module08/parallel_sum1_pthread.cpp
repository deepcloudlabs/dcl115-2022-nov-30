#include <iostream>
#include <algorithm>
#include <vector>
#include <pthread.h>
#include <time.h>

using namespace std;

const long PROBLEM_SIZE=64000000;
const int NUMBER_OF_CORE= pthread_num_processors_np();

struct problem {
	long *begin; 
	long *end;
	problem(long * _begin,long *_end) 
     : begin(_begin), end(_end){
   }
};

long numbers[PROBLEM_SIZE];

void init_array(long *array,long size){
	for (long *q=array,i=1;i<=size;++i,++q) {
	     *q= i;
	}	 
}

void* parallel_sum(void *_problem){
    problem *prob= (problem *) _problem;
	long sum=0;
    for (long *q=prob->begin;q!=prob->end;++q)
	    sum += *q;
	return new long(sum);
}

void serial_solver(long *array,int size){
	struct timespec begin_time, end_time;
	double elapsed;
	
	clock_gettime(CLOCK_MONOTONIC, &begin_time);
	long sum=0;
    for (long *q=array;q!=(array+size);++q)
	    sum += *q;
		
	clock_gettime(CLOCK_MONOTONIC, &end_time);

	elapsed = end_time.tv_sec - begin_time.tv_sec;
	elapsed += (end_time.tv_nsec - begin_time.tv_nsec) / 1000000000.0;
		
	cout << "Sum is " << sum << " @ " << elapsed << endl ;
 
}

int main(){
	init_array(numbers,PROBLEM_SIZE);

    serial_solver(numbers,PROBLEM_SIZE);
	struct timespec begin_time, end_time;
	double elapsed;
	
	clock_gettime(CLOCK_MONOTONIC, &begin_time);

    problem **problems;
    problems= new problem*[NUMBER_OF_CORE];
	pthread_t threads[NUMBER_OF_CORE];
	int per_thread= PROBLEM_SIZE / NUMBER_OF_CORE; 
	long* beg= numbers;
	long* end= beg+per_thread;

	for (int i=0;i<NUMBER_OF_CORE;++i){       
		problems[i]= new problem(beg,end);
		beg = beg + per_thread;
		end= end + per_thread;
		pthread_create(threads+i,0L, parallel_sum,(void*)problems[i]);
    }   
   
    long sum=0;
    for (int i=0;i<NUMBER_OF_CORE;++i){       
	    int *result;
		pthread_join(threads[i],(void**)&result);
		sum += *result;
		delete result;
    }
	clock_gettime(CLOCK_MONOTONIC, &end_time);

	elapsed = end_time.tv_sec - begin_time.tv_sec;
	elapsed += (end_time.tv_nsec - begin_time.tv_nsec) / 1000000000.0;
		
	cout << "Sum is " << sum << " @ " << elapsed << endl ;
    for (int i=0;i<NUMBER_OF_CORE;++i)      
	    delete problems[i];
	delete[] problems;	
    return 0; 	
}