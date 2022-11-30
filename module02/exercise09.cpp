#include <thread>
#include <iostream>

using namespace std;

int main(){
   cerr << "The number of logical processors is " 
        << thread::hardware_concurrency()
        << endl;
   return 0;
}
