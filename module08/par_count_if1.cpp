#include <iostream>
#include <pthread.h>
#include <time.h>

using namespace std;

const long PROBLEM_SIZE=16;
const int NUMBER_OF_CORE= 
          pthread_num_processors_np();

template <typename T>
struct problem {
	T *begin;
	T *end;
	bool(*fun)(T);
	problem(T *_begin,T *_end,bool(*_fun)(T)):
	    begin(_begin), end(_end), fun(_fun) {	    
	}
};

long numbers[PROBLEM_SIZE];

void init_array(long *array,long size){
	for (long i=0,*p=array;i<size;++i,++p)
	    *p=i;
}

template <typename T>
void* par_count_if(void* _problem){
    int count=0;
	problem<T>* prob= (problem<T>*) _problem;
	for (T *q=prob->begin;q!=prob->end;++q)
	{
	    if(prob->fun(*q)) ++count;
	}
	return new int(count);
}

template <typename T>
int count_if(T *begin,T *end,bool(*fun)(T)){
    T problem_size= end-begin; 
	pthread_t threads[NUMBER_OF_CORE];
	problem<T> **probs= 
	    new problem<T>*[NUMBER_OF_CORE];
	long per_thread= 
	         problem_size / NUMBER_OF_CORE;	
	T* _beg= begin;
	T* _end= _beg +  per_thread;
	for (int i=0;i<NUMBER_OF_CORE;++i){
	    probs[i]= 
		  new problem<T>(_beg,_end,fun);
		_beg = _beg + per_thread;
		_end= _end + per_thread;
	}	
	for (int i=0;i<NUMBER_OF_CORE;++i){
	    pthread_create(threads+i,
		   0L,
		   par_count_if<T>,
		   (void*)probs[i]);
    }	
	int total_count=0;
	for (int i=0;i<NUMBER_OF_CORE;++i){
	    int *result;
		pthread_join(threads[i], (void**)&result);
		total_count += *result;
		delete result;
    }	
	for (int i=0;i<NUMBER_OF_CORE;++i){
		delete probs[i];
    } 		 
	delete[] probs;
	return total_count;
}

template <typename T>
bool is_odd(T value){
	return value%2 ? true : false ;
}

int main(){
    init_array(numbers,PROBLEM_SIZE);
	int count= count_if(numbers,
	 numbers+PROBLEM_SIZE,is_odd<long>);
	cerr << "count: " << count << endl ;
	int arr[]={4,8,15,16,23,42,44,48};
	count= count_if(arr,arr+8,is_odd<int>);
	cout << endl;
	cerr << "count: " << count << endl ;
	cout << endl;
}















