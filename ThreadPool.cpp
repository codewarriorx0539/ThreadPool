#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int limit) : Container(limit)
{

    for(int i = 0; i < NUM_THREADS; i++)
    {
        threads[i] = new Thread(this);
    }
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
    for(int i = 0; i < NUM_THREADS; i++)
    {
        threads[i]->start();
        threads[i]->join();
    }
}
