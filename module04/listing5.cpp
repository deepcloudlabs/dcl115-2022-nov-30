#include <iostream>
#include <string>
#include <list>
#include <future>

using namespace std;

struct product {
	string name;
	int quantity;
	double price;
	product(string name,int quantity,double price):name(name),quantity(quantity),price(price){	
	}
};

struct purchase_order {
	list<product> items;
	purchase_order(list<product>& items):items(items){
	}
} ;

double calculate_total(purchase_order &po){
    double sum= 0.0;
	for (auto& item: po.items){
	    sum += item.price * item.quantity;
	}
	return sum;
}

int main(){
	list<product> items;	
	items.push_back(product(string("Product AAA"),1,10.0));
	items.push_back(product(string("Product BBB"),2,20.0));
	items.push_back(product(string("Product CCC"),3,30.0));
	items.push_back(product(string("Product DDD"),4,40.0));
	items.push_back(product(string("Product EEE"),5,50.0));
	items.push_back(product(string("Product EEE"),6,60.0));
	purchase_order po(items);
	
	future<double> total= async(calculate_total,ref(po));
	cout << "total: " << total.get() << endl;	
	return 0;
}	