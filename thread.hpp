#pragma once
#include "mutex.hpp"
#include "work.hpp"

class ThreadPool;

void processWork(void * thread)
{
    
    {
        Mutex mtx;
        Lock lock(mtx);
        Thread* pThread = (Thread*)thread;
    }
    
    Work* pWork = null;

    while(1)
    {
        pWork = queue.popWork();
        pWork->run();
    }

}

class Thread
{
 protected:
     Mutex mtx;
     pthread_t pthread;
     ThreadPool *queue;
     
 public:
    Thread(ThreadPool *pool) : queue(pool)
    {
        
    }
    
    
    
    void start()
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
    
    void join()
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
};

