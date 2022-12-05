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
	void(*fun)(T);
	problem(T *_begin,T *_end,void(*_fun)(T)):
	    begin(_begin), end(_end), fun(_fun) {	    
	}
};

long numbers[PROBLEM_SIZE];

void init_array(long *array,long size){
	for (long i=0,*p=array;i<size;++i,++p)
	    *p=i;
}

template <typename T>
void* par_for_each(void* _problem){
	problem<T>* prob= (problem<T>*) _problem;
	for (T *q=prob->begin;q!=prob->end;++q)
	{
	    prob->fun(*q);
	}
}

template <typename T>
void for_each(T *begin,T *end,void(*fun)(T)){
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
		   par_for_each<T>,
		   (void*)probs[i]);
    }	
	for (int i=0;i<NUMBER_OF_CORE;++i){
		pthread_join(threads[i], NULL);
    }	
	for (int i=0;i<NUMBER_OF_CORE;++i){
		delete probs[i];
    } 		 
	delete[] probs;
}

void print_odd_numbers(long value){
	if (value%2==1){
		cerr << value << " " ;
	}
}

template <typename T>
void print_element(T value){
	cout << value << " " ;
}

template <typename T>
void print_even_numbers(T value){
	if (value%2==0){
		cerr << value << " " ;
	}
}

template <typename T>
void print_odd_element(T value){
    if (value%2)
	   cout << value << " " ;
}

template <typename T>
void print_even_element(T value){
    if (value%2==0)
	   cout << value << " " ;
}
int main(){
    init_array(numbers,PROBLEM_SIZE);
	for_each(numbers,
	 numbers+PROBLEM_SIZE,print_odd_numbers);
	cerr << endl ;
	for_each(numbers,
	 numbers+PROBLEM_SIZE,print_even_numbers);	
	 
	int arr[]={4,8,15,16,23,42};
	for_each(arr,arr+6,print_element<int>);
	cout << endl;
	for_each(arr,arr+6,print_odd_element<int>);
	cout << endl;
	for_each(arr,arr+6,print_even_element<int>);	 
	double arr2[]={4.4,8.8,15.15,16.16,23.23,42.42};
	cout << endl;
	for_each(arr2,arr2+6,print_element<double>);
	cout << endl;

}















