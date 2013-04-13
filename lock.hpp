#pragma once

#include "mutex.hpp"

// RAII
class Lock
{
 protected:
	Mutex &refMtx;
 public:
	Lock(Mutex &mut):refMtx(mut)
	{   
		refMtx.lock(); 
	}

	~Lock(void)
	{ 
		refMtx.unlock();  
	}
};

// Prevents deadlock circular wait while releasing resources
class DualLock
{

protected:
	Mutex &refLeft;
	Mutex &refRight;
public:
	DualLock(Mutex &mutLeft , Mutex &mutRight):refLeft(mutLeft),refRight(mutRight)
	{ 
			while ( refRight.trylock() )  
			{
				refLeft.unlock(); 
				// Pause if you want non real time performance
				refLeft.lock();
			}				
	}
	
	~DualLock(void)
	{ 
		refRight.unlock(); 
		refLeft.unlock();
	}
};
