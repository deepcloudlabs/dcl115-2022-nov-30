#include <iostream>
#include <thread>

void sum(int &result,int* p,int from,int length) {
    result=0;
    for (int *q=p,j=0;j<length;++j,++q)
	result += *q;
}

int main(){
	int *lost = new int[6] ;
	// lost= {4,8,15,16,23,42};
	int *partial_sums= new int[2];
	std::thread t1(sum,std::ref(partial_sums[0]),lost,0,3);
	std::thread t2(sum,std::ref(partial_sums[1]),lost,3,3);
	t1.join();
	t2.join();
	int solution=0;
	//std::thread t(sum,solution,partial_sums,0,2);
	//t.join();
	std::cout << "The sum is " << solution << std::endl;
	delete[] lost;
    return 0;
}
