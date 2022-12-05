#include <thread>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

thread_local vector<int> my_numbers;

void doWork(int i){
	my_numbers.push_back(i);	
	for_each(my_numbers.begin(),my_numbers.end(),[](int i){ cout << i << endl;});
}

int main(){
   //my_numbers.push_back(5);	
   thread t1(doWork,1);
   thread t2(doWork,2);
   t1.join();
   t2.join();
   return 0;
}
