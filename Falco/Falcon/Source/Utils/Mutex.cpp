#include "../stdafx.h"
#include "Mutex.h"

//Create a Mutex
Mutex::Mutex()
{
	mutex = CreateMutex(0, false, 0);

	if(mutex == NULL) 
	{
		DWORD error = GetLastError();
		//Todo: Insert Error Code
	}
	
}

//Release the mutex
void Mutex::Release()
{
	if(ReleaseMutex(mutex) == 0)
	{
		DWORD error = GetLastError();
		//Todo: Insert Error Code
	}
}

//Lock the mutex
void Mutex::Lock()
{
	if(WaitForSingleObject(mutex, INFINITE) == WAIT_FAILED)
	{
		DWORD error = GetLastError();
		//Todo: Insert Error Code
	}
}
