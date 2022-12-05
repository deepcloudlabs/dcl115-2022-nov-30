#include <thread>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

thread_local 
int i=0;

void f(int newval){
    i=newval;
}

void g(){
    cout << i << endl ;
}

void threadfunc(int id){
    f(id);
    ++i;
    g();
}

int main(){
    i=9;
    thread t1(threadfunc,1);
    thread t2(threadfunc,2);
    thread t3(threadfunc,3);

    t1.join();
    t2.join();
    t3.join();
    cout<<i<<endl;
}
