#include <iostream>
#include <mutex>
using namespace std;

class some_big_object {
   public:
     int x;
};

void swap(some_big_object& lhs,some_big_object& rhs){}

class X {
private:
    some_big_object some_detail;
    mutable mutex m;
public:
    X(some_big_object const& sd):some_detail(sd){}

    friend void swap(X& lhs, X& rhs) {	    
        if(&lhs==&rhs)
            return;
		cout << "Swapping is done" ;	
        lock(lhs.m,rhs.m);
        lock_guard<mutex> lock_a(lhs.m,adopt_lock);
        lock_guard<mutex> lock_b(rhs.m,adopt_lock);
        swap(lhs.some_detail,rhs.some_detail);
		cout << "." << endl;
    }
};

int main(){
   some_big_object bo1{42},bo2{108};
   X x1 {bo1}, x2 {bo2};
   swap(x1,x2);
   return 0;
}
