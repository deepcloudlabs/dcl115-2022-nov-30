#include <memory>

using namespace std;

template<typename T>
class queue {
private:
    struct node {
        T data;
        unique_ptr<node> next;
        node(T data_): data(move(data_)){}
    };    
    unique_ptr<node> head;
    node* tail;    
public:
    queue():tail(nullptr){}

    queue(const queue& other)=delete;
    queue& operator=(const queue& other)=delete;

    shared_ptr<T> try_pop(){
        if(!head){
            return shared_ptr<T>();
        }
        shared_ptr<T> const res(
            make_shared<T>(move(head->data)));
        unique_ptr<node> const old_head=move(head);
        head=move(old_head->next);
        return res;
    }
    
    void push(T new_value){
        unique_ptr<node> p(new node(move(new_value)));
        node* const new_tail=p.get();
        if(tail){
            tail->next=move(p);
        }
        else {
            head=move(p);
        }
        tail=new_tail;
    }
};
