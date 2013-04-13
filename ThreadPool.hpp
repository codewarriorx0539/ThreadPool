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
    static const int NUM_THREADS = 4;
    Thread *threads[NUM_THREADS];
    
 public:   
     ThreadPool(int limit) : bound(limit)
     {
         for(int i = 0; i < NUM_THREADS; i++)
         {
             threads[i] = new Thread(this);
         }
     }
     
     Work* popWork()
     {
         Lock lock(mtx);
         Work* newWork = null;
         Wait2Consume w(consume, produce, mtx, *this);
  
         newWork = heap.top();
         heap.pop();
         size--;
         
         return newWork;
     }
     
     void pushWork(Work *work)
     {
         Lock lock(mtx);
         Wait2Produce w(produce, consume, mtx, *this);
         
         heap.push(work);
         size++;
     }
     
     void start()
     {
         for(int i = 0; i < NUM_THREADS; i++)
         {
             threads[i]->start();
             threads[i]->join();
         }
     }
};

