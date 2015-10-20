#ifndef TIMER_H
#define TIMER_H

struct ThreadInfo
{
public:
	double time;
	void (*function)();
};

class CTimer
{
public:
	~CTimer(void);
	//Initialize the timer to send a callback after elapsed time has passed
	CTimer(double _milliseconds, void (*_callback)());

	//Initialize the timer
	CTimer();

	//Increments the timer, 
	//cannot run if countdown is running.
	void StartTime();

	//Stops the increment of time.
	//returns current time in milliseconds
	double StopTime();
	
	//Get the current Seconds
	double GetSeconds();

	//Get the current Minutes
	double GetMinutes();

	//Get the current Milliseconds
	double GetMilliSeconds();

	//Set the time until function is called
	//i.e 3..2..1..call function
	void SetCountdownCallback(double _milliseconds, void (*_callback)());

	//Resets the timer to the 0
	void Reset();

	//Returns the Frames Per Second
	int GetFPS();

	//Returns the change in time
	double GetDeltaTime();

	//Update the time
	void Update();

private:

	void Initialize();

	 LARGE_INTEGER m_liFrequency;
	 LARGE_INTEGER m_currTick;
	 
	 bool m_bUpdate;

	 double m_dCurrentTime;
	 double m_dStartTime;
	 double m_dLastTime;
	 double m_dDeltaTime;
	 double m_dPreviousFrameTime;

	 int m_nFrames;
	 int m_nFramesPerSecond;

};
	

#endif