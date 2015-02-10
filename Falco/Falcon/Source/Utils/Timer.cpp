#include "../stdafx.h"
#include "Timer.h"
#include "Mutex.h"


DWORD WINAPI UpdateCountdown(LPVOID _lpParamter)
{
	ThreadInfo* Info = (ThreadInfo*)_lpParamter;
	LARGE_INTEGER startTime;

	if(!QueryPerformanceCounter(&startTime))
	{	
		//Todo: Insert Error Code
	}

	double pcFreq = startTime.QuadPart / 1000.0;
	__int64 startCount = startTime.QuadPart;

	cout << Info->time << endl;

	double countdown = Info->time;

	while(true)
	{
		QueryPerformanceCounter(&startTime);

		countdown -= (startTime.QuadPart - startCount) /pcFreq;

		startCount = startTime.QuadPart;

		if(countdown <= 0.0)
			break;
	}

	Info->function();

	delete Info;

	return 0;
}


Timer::~Timer(void)
{

}


Timer::Timer(double _milliseconds,  void (*_callback)())
{
	ThreadInfo* tempInfo = new ThreadInfo();
	tempInfo->time = _milliseconds;
	tempInfo->function = _callback;
	
	CreateThread(0, 0, &UpdateCountdown, (LPVOID)tempInfo, 0, 0);

}


//Increments the timer, 
//cannot run if stopwatch is running.
void Timer::StartTime()
{

}

//Decrements the timer, until zero
//Cannot run if timer is running
void Timer::StartCountdown()
{

}

//Stops the increment or decrement of time.
//returns current time in milliseconds
double Timer::StopTime()
{
	return 0;
}

//Get the current Seconds
double Timer::GetSeconds()
{
	return 0;
}

//Get the current Minutes
double Timer::GetMinutes()
{
	return 0;
}

//Get the current Milliseconds
double Timer::GetMilliSeconds()
{
	return 0;
}

//Set the time until function is called
//i.e 3..2..1..call function
void Timer::SetCountdownCallback(double _milliseconds, void* _callback)
{

}

//Resets the timer to 0
void Timer::Reset()
{

}

//Resets the initial time to the passed in value, and resets the timer if true
void Timer::ResetInitialTime(double _milliseconds, bool _resetTimer)
{
	
}

//Returns the Frames Per Second
int Timer::GetFPS()
{
	return 0;
}

