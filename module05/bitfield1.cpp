#include <iostream>

using namespace std;

typedef struct tagT{
    int a:4;
    int b:4;
    int c:8;
    int d:16;
}T;


int main()
{
    char data[]={0x12,0x34,0x56,0x78};
    T *t = (T*)data;
    cout << "a= " << hex << t->a << endl ;
    cout << "b= " << hex << t->b << endl ;
    cout << "c= " << hex << t->c << endl ;
    cout << "d= " << hex << t->d << endl ;

    return 0;
}
