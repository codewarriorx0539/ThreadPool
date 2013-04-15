
#include <iostream>
#include "ThreadPool.hpp"
#include "work.hpp"

using namespace std;

int main(int argc, char** argv) 
{
    int limit =100;
    int numthreads = 4;
    
    ThreadPool tp(numthreads, limit);
    CoutMsg w[5];
    
    for(int i = 0; i < 5; i++)
    {
        tp.pushWork(&w[i]);
    }
    
    tp.start();
    
    return 0;
}

