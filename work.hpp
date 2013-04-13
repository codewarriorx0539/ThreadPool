#pragma once
#include <iostream>

class Work
{
 protected:
     int priority;
     
 public:
   Work(int p) : priority(p)
   {
     
   }
   
   virtual void run() =0;
   
   int getPriority() const
   {
       return priority;
   }
  
};

class CoutMsg : public Work
{
 public:
    
    CoutMsg() : Work(10)
    {
        
    }
    
    void run()
    {
        std::cout << "Hello World";
    }
    
};
