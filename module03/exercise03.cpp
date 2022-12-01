#include <stack>
#include <memory>
#include <mutex>

using namespace std;

template <class T>
class ts_stack {
   stack<T> my_data;
   mutex m;
public:
   ts_stack(){}
   ts_stack(const ts_stack&);
   ts_stack& operator=(const ts_stack&)=delete;
   void push(T new_value);
   shared_ptr<T> pop();
   void pop(T& value);
   bool empty() const;
};

template <class T>
ts_stack<T>::ts_stack(const ts_stack& other){
   lock_guard<mutex> lock(other.m);
   my_data = other.my_data;
}

template <class T>
void ts_stack<T>::push(T new_value){
   lock_guard<mutex> lock(m);
   my_data.push(new_value);
}

template <class T>
shared_ptr<T> ts_stack<T>::pop(){
   lock_guard<mutex> lock(m);
   shared_ptr<T> const result(make_shared<T>(my_data.top()));
   my_data.pop();
   return result;
}

template <class T>
void ts_stack<T>::pop(T& value){
   lock_guard<mutex> lock(m);
   value = my_data.top();
   my_data.pop();
}

template <class T>
bool ts_stack<T>::empty() const{
   lock_guard<mutex> lock(m);
   return my_data.empty();
}

int main(){

    return 0;
}
