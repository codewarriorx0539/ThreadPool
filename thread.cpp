#include "thread.hpp"
#include "ThreadPool.hpp"

void* processWork(void * pool)
{
    ThreadPool* queue = NULL;
    
    {
        Mutex mtx;
        Lock lock(mtx);
        queue = (ThreadPool*)pool;
    }
    
    Work* pWork = NULL;

    while(1)
    {
        pWork = queue->popWork();
        pWork->run();
    }

    pthread_exit(NULL);
}

Thread::Thread(const ThreadPool *pool) : queue(pool)
{

}

void Thread::start()
{
    Lock lock(mtx);

    int status = pthread_create(&pthread, 0, &processWork, (void*)queue);
    if (status != 0)
    {
       if (status == EAGAIN)
       {
          throw std::runtime_error(
             "insufficient system resources to create thread");
       } else if (status == EINVAL)
       {
          throw std::logic_error(
             "invalid thread attributes while creating thread");
       } else if (status == EPERM)
       {
          throw std::logic_error(
             "permission error while creating thread");
       } else
       {
          throw std::runtime_error(
             "unknown error while creating thread");
       }
    }
}

void Thread::join()
{
    Lock lock(mtx);

    int status = pthread_join(pthread, 0);
    if (status != 0)
    {
       if (status == EDEADLK)
       {
          throw std::logic_error(
             "joining thread would cause deadlock");
       } else if (status == EINVAL)
       {
          throw std::logic_error(
             "thread is not joinable or is already being joined");
       } else if (status == ESRCH)
       {
          throw std::logic_error(
             "attempt to join invalid thread");
       } else
       {
          throw std::runtime_error(
             "unknown error while joining thread");
       }
    }
}