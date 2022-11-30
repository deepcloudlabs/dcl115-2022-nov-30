#include <thread>
#include <iostream>

using namespace std;

void task(){
   cout << "Running a task." << endl;
   return;
}

int main(){
   thread t1(task);  
   t1.join();
   cout << "Application is done." << endl;
   return 0;
}
