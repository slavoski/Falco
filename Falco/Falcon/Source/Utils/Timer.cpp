#include "../stdafx.h"
#include "Timer.h"
#include "Mutex.h"


DWORD WINAPI UpdateCountdown(LPVOID _lpParamter)
{
	ThreadInfo* Info = (ThreadInfo*)_lpParamter;
	LARGE_INTEGER pcFreq, currentTick;

	if(!QueryPerformanceFrequency(&pcFreq))
	{	
		//Todo: Insert Error Code
	}

	if(!QueryPerformanceCounter(&currentTick))
	{	
		//Todo: Insert Error Code
	}

	double startTime = double(currentTick.QuadPart) / double(pcFreq.QuadPart);
	
	//convert to milliseconds
	double countdown = Info->time / 1000.0;
	double lastTime = 0;

	//loop forever
	// or until the time is 0 or below 0
	while(true)
	{
		QueryPerformanceCounter(&currentTick);
		
		double currTime =  (double(currentTick.QuadPart) / double(pcFreq.QuadPart)) - startTime;

		countdown -= (currTime - lastTime);
		
		lastTime = currTime;

		//Are we ready to break?
		if(countdown <= 0.0)
			break;
	}

	//Call the function
	Info->function();

	//Delete the memory we allocated
	delete Info;

	return 0;
}


CTimer::~CTimer(void)
{

}


CTimer::CTimer(double _milliseconds,  void (*_callback)())
{

	this->Initialize();

	//Create a new Thread object to safe the info.
	ThreadInfo* tempInfo = new ThreadInfo();
	tempInfo->time = _milliseconds;
	tempInfo->function = _callback;
	
	CreateThread(0, 0, &UpdateCountdown, (LPVOID)tempInfo, 0, 0);

}

CTimer::CTimer()
{
	this->Initialize();
}


//Increments the timer, 
//cannot run if countdown is running.
void CTimer::StartTime()
{
	m_bUpdate = true;
	m_dLastTime = double(m_currTick.QuadPart) / double(m_liFrequency.QuadPart) - m_dStartTime;
}

//Stops the increment of time.
//returns current time in milliseconds
double CTimer::StopTime()
{
	m_bUpdate = false;
	return m_dCurrentTime;
}

//Get the current Seconds
double CTimer::GetSeconds()
{
	Update();
	return m_dCurrentTime;
}

//Get the current Minutes
double CTimer::GetMinutes()
{
	Update();
	return  m_dCurrentTime / 60;
}

//Get the current Milliseconds
double CTimer::GetMilliSeconds()
{
	Update();
	return m_dCurrentTime * 1000.0;
}

//Set the time until function is called
//i.e 3..2..1..call function
void CTimer::SetCountdownCallback(double _milliseconds, void (*_callback)())
{
	//Create a new Thread object to safe the info.
	ThreadInfo* tempInfo = new ThreadInfo();
	tempInfo->time = _milliseconds;
	tempInfo->function = _callback;
	
	CreateThread(0, 0, &UpdateCountdown, (LPVOID)tempInfo, 0, 0);
}

//Resets the timer to 0
void CTimer::Reset()
{
	QueryPerformanceCounter(&m_currTick);
	m_dStartTime = double(m_currTick.QuadPart) / double(m_liFrequency.QuadPart);
	m_dCurrentTime = m_dLastTime =  m_dPreviousFrameTime = 0.0;
	m_nFrames = m_nFramesPerSecond = 0;
}


//Returns the Frames Per Second
int CTimer::GetFPS()
{
	return m_nFramesPerSecond;
}

void CTimer::Initialize()
{
	if(!QueryPerformanceFrequency(&m_liFrequency))
	{	
		//Todo: Insert Error Code
	}

	if(!QueryPerformanceCounter(&m_currTick))
	{	
		//Todo: Insert Error Code
	}

	m_dStartTime = double(m_currTick.QuadPart) / double(m_liFrequency.QuadPart);

	m_bUpdate = false;
	m_dCurrentTime = 0;
	m_dLastTime = 0;
	m_nFrames = 0;
	m_nFramesPerSecond = 0;
	m_dPreviousFrameTime = 0;
}

void CTimer::Update()
{
	QueryPerformanceCounter(&m_currTick);

	double dNewTime = (double(m_currTick.QuadPart) / double(m_liFrequency.QuadPart)) - m_dStartTime;
	m_dDeltaTime = (dNewTime - m_dLastTime);

	//Don't update time unless they have started the timer.
	if(m_bUpdate)
	{
		m_dCurrentTime += m_dDeltaTime;
	}

	++m_nFrames;
	
	//How many frames have elapsed in one second
	if(dNewTime - m_dPreviousFrameTime > 1.0f)
	{
		m_nFramesPerSecond = m_nFrames / (int)(dNewTime - m_dPreviousFrameTime);
		m_nFrames = 0;
		m_dPreviousFrameTime = dNewTime;
	}
	
	m_dLastTime = dNewTime;

}



//Returns the change in time
double CTimer::GetDeltaTime()
{
	return m_dDeltaTime;
}