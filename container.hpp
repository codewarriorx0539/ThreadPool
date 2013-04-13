#pragma once

#include "mutex.h"
#include "lock.h"

// BASE CLASS FOR ALL CONTAINERS

class Container
{
	
 protected:
	 int size;
	 int bound;
	 Mutex mtx;
	 Condition consume;
	 Condition produce;

 public:

	 int getSize()
	 {
		 return size;
	 }

	 bool isEmpty()
	 { 
		 Lock l(mtx);

		 if(size)
			 return false;
		 else
			 return true;
	 }

	 int getBound()
	 {
		 return bound;
	 }


	Container()
	{
		size = 0;
		bound = 0;
	}

	~Container()
	{
	}
};

class Wait2Consume
{
	protected:
		Condition &refOKConsume;
		Condition &refOKProduce;
		Mutex &refMtx;
		Container &refCon;

	public:
		Wait2Consume(Condition &OKConsume, Condition &OKProduce, Mutex &mtx, Container &refCon):refOKConsume( OKConsume), refOKProduce( OKProduce),refMtx( mtx), refCon(refCon)
		{
			while( refCon.getSize() == 0 ) 
			{
				refOKConsume.wait(refMtx); 
			}
		}

		~Wait2Consume( )
		{
			refOKProduce.broadcast();
		}
};


class Wait2Produce
{
	protected:
		Condition &refOKConsume;
		Condition &refOKProduce;
		Mutex &refMtx;
		Container &refCon;

	public:
		Wait2Produce(Condition &OKProduce, Condition &OKConsume, Mutex &mtx, Container &refCon):refOKConsume( OKConsume), refOKProduce( OKProduce),refMtx( mtx), refCon(refCon)
		{
			while(refCon.getSize() == refCon.getBound())
			{
				refOKProduce.wait(refMtx);
			}

		}

		~Wait2Produce( )
		{
			refOKConsume.broadcast();
		}
};




