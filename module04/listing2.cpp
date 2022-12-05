#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

struct product {
	string name;
	int quantity;
	double price;
	double sub_total;
	product(string name,int quantity,double price):name(name),quantity(quantity),price(price){	
	}
};

struct purchase_order {
	list<product> items;
	double total;	
	purchase_order(list<product>& items):items(items){
		total= 0.0;
	}
} ;

mutex mut;
queue<purchase_order> orders;
condition_variable order_ready;

void recieve_po(list<purchase_order>& orders){
	for (auto o: orders){
	    cout << "Sending order..." << endl ;
		lock_guard<mutex> lk(mut);
		::orders.push(o);
		order_ready.notify_one();	
	}
}

void process_po(){
        unique_lock<mutex> lk(mut);
		order_ready.wait(lk,[]{return !orders.empty();});
	    cout << "An order is received..." << endl ;
		purchase_order po= orders.front();
		orders.pop();
		lk.unlock();
   	    for (auto p: po.items){
			cout << p.name << endl;
		}
}

int main(){
    list<purchase_order> orders;
	list<product> items1,items2,items3;	
	items1.push_back((product(string("Product AAA"),1,10.0)));
	items1.push_back((product(string("Product BBB"),2,20.0)));
	items1.push_back((product(string("Product CCC"),3,30.0)));
	items2.push_back((product(string("Product DDD"),4,40.0)));
	items2.push_back((product(string("Product EEE"),5,50.0)));
	items3.push_back((product(string("Product EEE"),6,60.0)));
	orders.push_back(purchase_order(items1));
	orders.push_back(purchase_order(items2));
	orders.push_back(purchase_order(items3));
	
	thread producer(recieve_po,ref(orders));
	thread consumer1(process_po);	
	thread consumer2(process_po);	
	thread consumer3(process_po);	
	
	producer.join();
	consumer1.join();	
	consumer2.join();	
	consumer3.join();	
	cout << "This is end of main." << endl;	
}	