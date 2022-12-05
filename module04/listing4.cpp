#include <iostream>
#include <future>

using namespace std;

long _3n_plus_1(long n){
	long step=0;
	while (n>1){
	   if (n%2==1){
	      n=3*n+1;
	   }else{
	      n=n/2;
	   }
	   ++step;
	}
	return step;
}


int main(){
    future<long> step= async(_3n_plus_1,837799L);	
	cout << "837799 takes " << step.get() << " steps!" << endl;	
}	