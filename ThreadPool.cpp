#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int numThreads, int limit) : Container(limit)
{
    this->numThreads = numThreads;
    
    threads = new Thread*[numThreads];
    
    for(int i = 0; i < numThreads; i++)
    {
        threads[i] = new Thread(this);
    }
}

ThreadPool::~ThreadPool()
{
    for(int i =0; i < numThreads; i++)
    {
        delete threads[i];
    }
    
    delete [] threads;
}

Work* ThreadPool::popWork()
{
    Lock lock(mtx);
    Work* newWork = NULL;
    Wait2Consume w(consume, produce, mtx, *this);

    newWork = heap.top();
    heap.pop();
    size--;

    return newWork;
}

void ThreadPool::pushWork(Work *work)
{
    Lock lock(mtx);
    Wait2Produce w(produce, consume, mtx, *this);

    heap.push(work);
    size++;
}

void ThreadPool::start()
{
    for(int i = 0; i < numThreads; i++)
    {
        threads[i]->start();
    }
    
    for(int i = 0; i < numThreads; i++)
    {
        threads[i]->join();
    }
  
}
