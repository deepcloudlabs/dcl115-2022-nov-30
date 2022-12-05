#include <iostream>
#include <vector>
#include <list>
#include <future>
#include <algorithm>

using namespace std;

class join_threads {
      vector<std::thread>& threads;
   public:
      explicit join_threads(vector<std::thread>& threads_):threads(threads_){}
      ~join_threads() {
			for (unsigned long i=0;i<threads.size();++i) {
				if (threads[i].joinable())
					threads[i].join();
			}
		}
};

template<typename Iterator,typename Func>
void parallel_for_each(Iterator first,Iterator last,Func f){
    unsigned long const length=distance(first,last);

    if(!length)
        return;

    unsigned long const min_per_thread=25;
    unsigned long const max_threads=
        (length+min_per_thread-1)/min_per_thread;

    unsigned long const hardware_threads=
        thread::hardware_concurrency();

    unsigned long const num_threads=
        min(hardware_threads!=0?hardware_threads:2,max_threads);

    unsigned long const block_size=length/num_threads;

    vector<future<void> > futures(num_threads-1);
    vector<thread> threads(num_threads-1);
    join_threads joiner(threads);

    Iterator block_start=first;
    for(unsigned long i=0;i<(num_threads-1);++i){
        Iterator block_end=block_start;
        advance(block_end,block_size);
        packaged_task<void(void)> task(
            [=]()
            {
                for_each(block_start,block_end,f);
            });
        futures[i]=task.get_future();
        threads[i]=thread(move(task));
        block_start=block_end;
    }
    for_each(block_start,last,f);
    for(unsigned long i=0;i<(num_threads-1);++i){
        futures[i].get();
    }
}

int main(){
   list<int> numbers;
   int i=0;
   while (++i<=3000)
      numbers.push_back(i);
   parallel_for_each(numbers.begin(),numbers.end(),[](int i){cout << i << " " ;});
   return 0;
}
