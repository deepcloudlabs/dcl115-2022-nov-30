#include <mutex>
#include <condition_variable>
using namespace std;

class semaphore{
private:
    mutex mtx;
    condition_variable cv;
    int count;

public:
    semaphore(int count_ = 1):count(count_){;}
    void notify(){
        unique_lock<mutex> lck(mtx);
        ++count;
        cv.notify_one();
    }
    void wait(){
        unique_lock<mutex> lck(mtx);
        cv.wait(lck,[this](){return count>0;});
        count--;
    }
};