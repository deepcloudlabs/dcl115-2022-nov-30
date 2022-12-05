#include <iostream>
#include <thread>
#include <numeric>
#include <functional>

using namespace std;

template<typename Iterator,typename T>
struct accumulate_block{
	void operator()(Iterator first,Iterator last,T& result){
		result=accumulate(first,last,result);
		cout << "Thread " << std::this_thread::get_id() << " is returning " << result << endl;
	}
};

template<typename Iterator,typename T>
T parallel_accumulate(Iterator first,Iterator last,T init){
	unsigned long const length=distance(first,last);
	if(!length) return init;
	unsigned long const min_per_thread=6;
	unsigned long const max_threads= (length+min_per_thread-1)/min_per_thread;
	unsigned long const hardware_threads=thread::hardware_concurrency();
	unsigned long const num_threads= min(hardware_threads,max_threads);
	cout << "Number of hardware threads are " << hardware_threads << endl ;
	cout << "Maximum number of threads are " << max_threads << endl ;
	cout << "Number of threads are " << num_threads << endl ;
	unsigned long const block_size=length/num_threads;
	vector<T> results(num_threads);
	vector<thread> threads(num_threads-1);
	Iterator block_start=first;
	for(unsigned long i=0;i<(num_threads-1);++i){
		Iterator block_end=block_start;
		advance(block_end,block_size);
		threads[i]=thread(accumulate_block<Iterator,T>(),block_start,block_end,ref(results[i]));
		block_start=block_end;
	}
	accumulate_block<Iterator,T>()(block_start,last,results[num_threads-1]);
	for_each(threads.begin(),threads.end(),mem_fn(&thread::join));
	return accumulate(results.begin(),results.end(),init);
}

int main(){
    int lost[]={4,8,15,16,23,42,4,8,15,16,23,42,4,8,15,16,23,42,4,8,15,16,23,42,4,8,15,16,23,42,4,8,15,16,23,42,4,8,15,16,23,42,4,8,15,16,23,42};
	int sum= parallel_accumulate(lost,lost+48,int());
	cout << sum << endl;
	return 0;
}
