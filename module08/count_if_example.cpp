#include <iostream>
#include <algorithm>

using namespace std;

void print_element(int value){
	cout << value << " " ;
}

bool is_odd(int value){
	return value%2 ? true : false ;
}

int main(){
	int arr[]={4,8,15,16,23,42};
	int count= count_if(arr,arr+6,is_odd);
	cout << "Number of odd numbers: " 
	     << count 
	     << endl;
	return 0;
}