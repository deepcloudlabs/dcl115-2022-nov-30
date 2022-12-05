#include <thread>
#include <iostream>
#include <mutex>
#include <memory>
#include  "domain.h"

using namespace std;

template<typename T>
class threadsafe_queue {
  struct node {
    shared_ptr<T> data;
    unique_ptr<node> next;
  };

private:
    mutex head_mutex;
    unique_ptr<node> head;
    mutex tail_mutex;
    unique_ptr<node> tail;

    unique_ptr<node> get_tail(){
        lock_guard<mutex> tail_lock(tail_mutex);
        return tail;
    }

    unique_ptr<node>& pop_head() {
        lock_guard<mutex> head_lock(head_mutex);
        if(head==tail) {
            return nullptr;
        }
        unique_ptr<node> const old_head=move(head);
        head=move(old_head->next);
        return old_head;
    }

    std::unique_ptr<node> try_pop_head()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        if(head==tail)
        {
            return std::unique_ptr<node>();
        }
        return pop_head();
    }

    std::unique_ptr<node> try_pop_head(T& value)
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        if(head==tail)
        {
            return std::unique_ptr<node>();
        }
        value=std::move(*head->data);
        return pop_head();
    }

public:
    std::shared_ptr<T> try_pop()
    {
        std::unique_ptr<node> const old_head=try_pop_head();
        return old_head?old_head->data:std::shared_ptr<T>();
    }
    void push(T new_value){
        shared_ptr<T> new_data( make_shared<T>(move(new_value)));
        unique_ptr<node> new_tail(new node);
        lock_guard<mutex> tail_lock(tail_mutex);
        tail->data=new_data;
        tail->next=move(new_tail);
        tail=move(new_tail);
    }

    bool try_pop(T& value)
    {
        std::unique_ptr<node> const old_head=try_pop_head(value);
        return old_head;
    }

    bool empty()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        return (head==tail);
    }
};

threadsafe_queue<programmer> ts_queue;

void fun1(){
        ts_queue.push(programmer(string("Jack"),string("Sheppard"),41,programming_language(string("c++"),8)));
        ts_queue.push(programmer(string("Kate"),string("Austen"),36,programming_language(string("java"),6)));
        ts_queue.push(programmer(string("Sun"),string("Kwon"),36,programming_language(string("scala"),5)));
        ts_queue.push(programmer(string("Hugo"),string("Reyes"),29,programming_language(string("python"),7)));
        ts_queue.push(programmer(string("John"),string("Lock"),29,programming_language(string("perl"),10)));
        ts_queue.push(programmer(string("Claire"),string("Littleton"),27,programming_language(string("perl"),4)));
        ts_queue.push(programmer(string("Juliet"),string("Burke"),36,programming_language(string("go"),9)));
        ts_queue.push(programmer(string("Richard"),string("Alpert"),37,programming_language(string("f#"),9)));
        ts_queue.push(programmer(string("Shannon"),string("Rutherford"),27,programming_language(string("pl/1"),2)));
        ts_queue.push(programmer(string("Alex"),string("Rousseau"),21,programming_language(string("cobol"),2)));
}

void fun2(){ 
        ts_queue.push(programmer(string("Ben"),string("Linus"),47,programming_language(string("c#"),9)));
        ts_queue.push(programmer(string("James"),string("Ford"),47,programming_language(string("c"),6)));
        ts_queue.push(programmer(string("Jin"),string("Kwon"),36,programming_language(string("lisp"),4)));
        ts_queue.push(programmer(string("Desmond"),string("Hume"),38,programming_language(string("c#"),9)));
        ts_queue.push(programmer(string("Charlie"),string("Pace"),32,programming_language(string("c"),6)));
        ts_queue.push(programmer(string("Sayyid"),string("Jarrah"),41,programming_language(string("lisp"),4)));
        ts_queue.push(programmer(string("Miles"),string("Leung"),32,programming_language(string("ada"),4)));
        ts_queue.push(programmer(string("Walt"),string("Llyod"),16,programming_language(string("bash"),5)));
        ts_queue.push(programmer(string("Daniel"),string("Rousseau"),49,programming_language(string("cobol"),7)));
}

void fun3(){
        ts_queue.push(programmer(string("Daniel"),string("Faraday"),37,programming_language(string("c#"),9)));
        ts_queue.push(programmer(string("Frank"),string("Lapidus"),47,programming_language(string("c"),6)));
        ts_queue.push(programmer(string("Boone"),string("Carlyle"),36,programming_language(string("lisp"),4)));
        ts_queue.push(programmer(string("Mr."),string("Eko"),38,programming_language(string("c#"),9)));
        ts_queue.push(programmer(string("Charlie"),string("Pace"),32,programming_language(string("c"),6)));
        ts_queue.push(programmer(string("Ana Lucia"),string("Cortez"),32,programming_language(string("lisp"),4)));        ts_queue.push(programmer(string("Bernard"),string("Nadler"),57,programming_language(string("ada"),4)));
        ts_queue.push(programmer(string("Rose"),string("Nadler"),53,programming_language(string("bash"),5)));
        ts_queue.push(programmer(string("Niki"),string("Fernandez"),32,programming_language(string("awk"),3)));
}

int main(){
        thread t1(fun1);
        thread t2(fun2);
        thread t3(fun3);
        t1.join();
        t2.join();
        t3.join();
        while (!ts_queue.empty()){
          cout << ts_queue.try_pop() << endl ;
        }

    return 0;
}
