#pragma once

class Work
{
 protected:
     int priority;
     
 public:
   Work(int p) : priority(p)
   {
     
   }
   
   virtual void run() =0;
   
   void getPriority()
   {
       return priority;
   }
  
};
