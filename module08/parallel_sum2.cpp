#include <iostream>
#include <thread>
#include <algorithm> // accumulate
#include <vector>
#include <atomic>
#include <numeric>
#include <future>

using namespace std;

const int SIZE=1'000'000;

vector<int> my_numbers;
atomic<int> no_threads = ATOMIC_VAR_INIT(0);
atomic<int> no_leaf = ATOMIC_VAR_INIT(0);

void init_vector(vector<int>& vec,int size){
	for (int i=1;i<=size;++i) {
	     vec.push_back(i);
	}	 
}
// generic programming
template <typename iter>
int parallel_sum(iter beg, iter end){
    auto len= distance(beg,end);
	if (len <= 1000){
	   atomic_fetch_add(&no_leaf,1);   	
       return accumulate(beg,end, 0);	
	}   
	iter mid= beg + len / 2;
    auto handle= 
	   async(launch::async,parallel_sum<iter>,mid,end);
	atomic_fetch_add(&no_threads,1);   
    int sum= parallel_sum(beg,mid);
    return sum + handle.get();	
}

int main(){
   init_vector(my_numbers,SIZE);
	cout << "Sum is " 
	     << parallel_sum(my_numbers.begin(),my_numbers.end()) 
		 << endl ;
	cout << no_threads.load() << endl ;	 
	cout << no_leaf.load() << endl ;	 
    return 0; 	
}
