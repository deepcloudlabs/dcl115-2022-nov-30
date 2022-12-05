#include <iostream>
#include <thread>
#include <vector>

using namespace std;

template<typename T>
void count(int& counter,T *array, int from, int size,T value){
	counter=0;	   
	T *begin= array+from;
	T *end= begin+size;
	for (T *p=begin;p!=end;++p){
	    if (*p==value) ++counter;
	}			
}

int get_cores(){
    return thread::hardware_concurrency();
}

template <typename T>
int solve(T *array,int size,T value){
    vector<thread> threads;
	int noc= get_cores();
	int local_size= size / noc;
	int partial_counter[noc];
	for (int i=0,from=0;i<noc; ++i,from += local_size){
		threads.push_back(
		   thread(count<T>,
		    ref(partial_counter[i]),
			array,
			from,
			local_size,
			value)
		);
	}
	for (auto& t: threads) t.join();
	int counter=0;
	for (auto &pc: partial_counter)	counter += pc;
	return counter;	
}

int main(){
	int arr[]={3,7,11,8, 4,11,42,55, 11,23,42,11};
	double arr2[]={3.,7.,11.,8., 4.,11.,42.,55., 11.,23.,42.,11.};			   
	int size= sizeof(arr)/sizeof(int);		   
	int size2= sizeof(arr2)/sizeof(double);		   
	cout << "Counter: " 
		<< solve(arr,size,11)
		<< endl ;
	cout << "Counter: " 
		<< solve(arr2,size2,11.)
		<< endl ;
        return 0;
}
