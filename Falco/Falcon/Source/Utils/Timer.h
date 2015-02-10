#ifndef TIMER_H
#define TIMER_H

struct ThreadInfo
{
public:
	double time;
	void (*function)();
};

class Timer
{
public:
	~Timer(void);
	Timer(double _milliseconds, void (*_callback)());


	//Increments the timer, 
	//cannot run if countdown is running.
	void StartTime();

	//Decrements the timer, until zero
	//Cannot run if timer is running
	void StartCountdown();

	//Stops the increment or decrement of time.
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
	void SetCountdownCallback(double _milliseconds, void* _callback);

	//Resets the timer to the initial time or passed in time
	void Reset();

	//Resets the initial time to the passed in value, and resets the timer if true
	void ResetInitialTime(double _milliseconds, bool _resetTimer = false);

	//Returns the Frames Per Second
	int GetFPS();

private:

	 LARGE_INTEGER m_liFrequency;
	 LARGE_INTEGER m_currFrequency;
	 LARGE_INTEGER m_elapsedTime;
	 
	 bool m_bUpdate;
};


#endif