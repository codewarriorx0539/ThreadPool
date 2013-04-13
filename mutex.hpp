#pragma once

#include <pthread.h>

// Abstracted a mutex and condition variable

class Mutex
{
 
 protected:
	  pthread_mutex_t mutex;
 public:
	Mutex(void)
	{ 
		init();
	}

	~Mutex(void)
	{   
		pthread_mutex_destroy(&mutex);
	}

	int init()
	{
		 return pthread_mutex_init( &mutex, NULL );
	}

	int lock()
	{ 
                return pthread_mutex_lock( &mutex );
	}

	int unlock()
	{ 
                return pthread_mutex_unlock( &mutex );
	}

	int trylock()
	{ 
                return pthread_mutex_trylock( &mutex );
	}

	friend class Condition;
};

class Condition
{

 // data
 protected:
	pthread_cond_t cond;

 // functions
 public:
	Condition()
	{
		init();
	}

	~Condition()
	{
		pthread_cond_destroy(&cond);
	}

	int init()
	{
                return pthread_cond_init( &cond, NULL );
	}

	int wait(Mutex &mtx)
	{ 
		return pthread_cond_wait(&cond, &mtx.mutex);
	}

	int broadcast()
	{
                return pthread_cond_broadcast(&cond);
	}
};