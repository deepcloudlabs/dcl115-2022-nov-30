#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <future>
#include <numeric>

using namespace std;

const int SIZE=500'000'000;

vector<int> my_numbers;

void init_vector(vector<int>& vec,int size){
	for (int i=1;i<=size;++i) {
	     vec.push_back(i);
	}	 
}
// generic programming
template <typename iter>
int parallel_sum(iter beg, iter end){
    return accumulate(beg,end, 0);	
}

int main(){
   init_vector(my_numbers,SIZE);
   int numberOfVirtualCPUs= thread::hardware_concurrency();
   vector<future<int>> partial_sums;
   int per_thread= SIZE / numberOfVirtualCPUs; 
   auto beg= my_numbers.begin();
   auto end= beg+per_thread;
   for (int i=0;i<numberOfVirtualCPUs;++i){       
        partial_sums.push_back(
		  async(parallel_sum<vector<int>::iterator>,beg,end)
		);
		beg = beg + per_thread;
		end= end + per_thread;
   }   
   int sum=0;
   for (auto& f : partial_sums)
       sum += f.get();
	cout << "Sum is " << sum << endl ;
    return 0; 	
}
