#include <iostream>
#include <algorithm>

using namespace std;

void print_element(int value){
	cout << value << " " ;
}


void print_odd_element(int value){
    if (value%2)
	   cout << value << " " ;
}

void print_even_element(int value){
    if (value%2==0)
	   cout << value << " " ;
}

int main(){
	int arr[]={4,8,15,16,23,42};
	for_each(arr,arr+6,print_element);
	cout << endl;
	for_each(arr,arr+6,print_odd_element);
	cout << endl;
	for_each(arr,arr+6,print_even_element);
	return 0;
}