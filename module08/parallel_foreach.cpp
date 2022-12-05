#include <iostream>
#include <future>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;
class join_threads {
     vector<thread>& threads;
   public:
      explicit join_threads(vector<thread>& threads_)
         : threads(threads_) 
      {}
      ~join_threads(){
		for (auto& t : threads)
		{
		   if (t.joinable())
		      t.join();
		}	  
	  } 	  
} ;

template <typename Iterator,typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
    int length= distance(first,last);
	
	if (length==0) return;
	
	unsigned long const min_per_thread=25;
	unsigned long const max_threads= 
	   (length+min_per_thread-1)/min_per_thread;
	unsigned long const harware_threads=
             thread::hardware_concurrency();
    unsigned long const num_threads=
			min( 
			     harware_threads!=0?harware_threads:2,
			     max_threads
			);
	unsigned long const block_size= length / num_threads;
    vector<future<void>> futures(num_threads-1);
    vector<thread> threads(num_threads-1);
	join_threads thread_joiner(threads);
	
	Iterator block_start= first;
	for (unsigned long int i=0;i<(num_threads-1);++i)
	{
	    Iterator block_end= block_start;
		advance(block_end,block_size);
		packaged_task<void(void)> task(
		    [=](){
				for_each(block_start,block_end,f);
			}
		);
		futures[i]= task.get_future();
		threads[i]= thread(move(task));
		block_start= block_end;
	}
	for_each(block_start,last,f);
	for (unsigned long int i=0;i<(num_threads-1);++i)
	{
	   futures[i].get();
	}
}

int main(){
    list<int> numbers;
	for (int i=1;i<=100;++i)
	{
	    numbers.push_back(i);
	}
	parallel_for_each(
	   numbers.begin(),
	   numbers.end(),
	   [](int i){
	      cout << i << endl;
	   }
	);
}
