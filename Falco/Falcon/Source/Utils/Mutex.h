#ifndef MUTEX_H
#define MUTEX_H


class Mutex
{
public:
	//Create a Mutex
	Mutex();

	//Release the mutex
	void Release();

	//Lock the mutex
	void Lock();

private:
	HANDLE mutex;
};


#endif