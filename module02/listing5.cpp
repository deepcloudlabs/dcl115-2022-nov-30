#include <iostream>
#include <functional>
#include <numeric>
#include <thread>

void f(int a,int b) {
	std::cout << "a= " << a << std::endl;
	std::cout << "b= " << b << std::endl;
}

void g(int *a,int length) {
   for (int i=0;i<length;++i)
	std::cout << a[i] << std::endl;
}

void h(int &result,int *a,int start,int length) {
   result=0;
   for (int i=start,j=0;j<length;++i,++j)
	result += a[i] ;
}

void h2(int &result,int *begin,int *end) {
   result= std::accumulate(begin,end,int(),[](int acc,int val) { return acc+val;} );
}

int main(){
    int x=3, y=5;
	int lost[]={4,8,15,16,23,42};
	int result[2],sum;
	std::thread t1(f,x,y);
	std::thread t2(g,lost,6);
	std::thread t3(h,std::ref(result[0]),lost,0,3);
	std::thread t4(h,std::ref(result[1]),lost,3,3);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	std::thread t5(h,std::ref(sum),result,0,2);
	t5.join();
	std::cout << "sum= " << sum << std::endl;
	std::thread t6(h2,std::ref(sum),lost,lost+6);
	t6.join();
	std::cout << "sum= " << sum << std::endl;
    return 0;
}