#pragma once
#include <queue>
#include <vector>
#include "container.hpp"
#include "thread.hpp"
#include "work.hpp"

class workCompare : public std::binary_function<Work*, Work*, bool>
{
   public:
      bool operator()(const Work* left, const Work* right)
      {
         return (left->getPriority() < right->getPriority());
      }
};
   
class ThreadPool : public Container
{
 protected:
    std::priority_queue<Work*, std::vector<Work*>, workCompare> heap;
    static const int NUM_THREADS = 1;
    Thread *threads[NUM_THREADS];
    
 public:   
     ThreadPool(int limit);
     
     Work* popWork();
    
     void pushWork(Work *work);
     
     void start();
};

