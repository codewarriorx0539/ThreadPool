#pragma once

#include "mutex.hpp"
#include "lock.hpp"
#include "work.hpp"
#include <errno.h>
#include <exception>
#include <stdexcept>

class ThreadPool;

class Thread
{
 protected:
     pthread_t pthread;
     const ThreadPool *queue;
     
 public:
    Thread(const ThreadPool *pool); 
    
    void start();
    
    void join();
};

