#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

const int NUMBER_OF_CORES =  sysconf(_SC_NPROCESSORS_ONLN);

struct problem {
    int *array;
    int start;
    int size;
} ;

typedef struct problem sproblem;

int bind_self_to_core(int core_id) {
    core_id = core_id % NUMBER_OF_CORES ;

    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    pthread_t current_thread = pthread_self();
    return pthread_setaffinity_np(current_thread, sizeof(cpu_set_t), &cpuset);
}

void * sum (void *param) {
  static int counter=0;
  bind_self_to_core(counter++);
  struct problem *p= (struct problem*) param ;
  int *arr= p->array + p->start;
  long partialSum= 0;
  for (int i=0;i<p->size;++i,++arr){
      partialSum += arr[0];
  }
  return (void*) partialSum;
}

const int N = 10;
const int ARRAY_SIZE = 10000000;
const int PROBLEM_SIZE= ARRAY_SIZE/N;

int main () {
    pthread_t *threads= new pthread_t[N];
    struct problem *problem_instances= new struct problem[N];
    int *array= new int[ARRAY_SIZE];
    int *p= array;
    long sumOfArray=0;
    cout << "Number of virtual cpu is " << NUMBER_OF_CORES << "." << endl ;
    for (int i=0;i<ARRAY_SIZE;++i,++p){
        p[0]= rand() % 10 ;
        sumOfArray += p[0];
    }
    cout << "Sum of array (Serial) is " << sumOfArray << endl;
    /* Create n threads, each working with a different array partition. */
    for (int i=0,start=0;i<N;++i,start+=PROBLEM_SIZE){
        problem_instances[i].array= array;
        problem_instances[i].size= PROBLEM_SIZE;
        problem_instances[i].start= start;
        pthread_create (threads+i, NULL, sum, (void *) (problem_instances+i));
    }
    sumOfArray=0;
    for (int i=0;i<N;++i){
        long partialSum;
        pthread_join (threads[i], (void**)&partialSum);
        sumOfArray += partialSum;
    }
    cout << "Sum of array (Parallel) is " << sumOfArray << endl;
    delete[] array;
    delete[] threads;
    delete[] problem_instances;
        return 0;
}