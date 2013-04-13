
#include <iostream>
#include "ThreadPool.hpp"
#include "work.hpp"

using namespace std;

int main(int argc, char** argv) 
{
    ThreadPool tp(100);
    CoutMsg w[5];
    
    for(int i = 0; i < 5; i++)
    {
        tp.pushWork(&w[i]);
    }
    
    tp.start();
    
    return 0;
}

