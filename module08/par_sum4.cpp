#include <iostream>
#include <pthread.h>
#include <time.h>

using namespace std;

const long PROBLEM_SIZE=100000000;
const int NUMBER_OF_CORE= 
          pthread_num_processors_np();
		  
struct problem {
	long *begin;
	long *end;
	problem(){} 
	problem(long *_begin,long *_end):
	    begin(_begin), end(_end){	    
	}
};

long numbers[PROBLEM_SIZE];

void init_array(long *array,long size){
	for (long i=0,*p=array;i<size;++i,++p)
	    *p=i;
}

long serial_sum(problem *prob){
    long sum=0;
	for (long *p=prob->begin;p!=prob->end;++p)
	    sum += *p;
	return sum;
}

void * parallel_sum(void* _problem){
	problem* prob= (problem*) _problem;
	long size= prob->end - prob->begin;
	if (size <= 20000000){
	   return new long(serial_sum(prob)); 
	}
    problem problem_left, problem_right;	
	long *mid= prob->begin + size / 2;
	problem_left.begin= prob->begin;
	problem_left.end= mid;
	problem_right.begin= mid;
	problem_right.end= prob->end;

    pthread_t left,right;
    if(pthread_create(&left,0L,parallel_sum,
	          (void*)&problem_left)){
	   cerr << "Cannot create a thread!" 
	        << endl;			
    } 	
    if(pthread_create(&right,0L,parallel_sum,
	          (void*)&problem_right)){
	   cerr << "Cannot create a thread!" 
	        << endl;			
    }
   	cerr << " 2 Thread are created!" << endl ;		  
	long *result_left,*result_right,sum;
	pthread_join(left,(void**)&result_left);
	pthread_join(right,(void**)&result_right);
	sum = *result_left + *result_right;
	delete result_left;
	delete result_right;
	return new long(sum);
}

int main(){
    init_array(numbers,PROBLEM_SIZE);
	struct timespec begin_time, end_time;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC,&begin_time);
	problem prob(numbers,numbers+PROBLEM_SIZE);
	long *result= 
	  (long*) parallel_sum((void*)&prob);
	clock_gettime(CLOCK_MONOTONIC,&end_time);
	elapsed = 
	   end_time.tv_sec - begin_time.tv_sec;
	elapsed += (end_time.tv_nsec - begin_time.tv_nsec) / 1000000000.0;
    cout << "Sum (parallel): " << *result 
	     << " @ " << elapsed << endl;
	delete result;
}















