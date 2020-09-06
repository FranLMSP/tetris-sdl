#include "Timer.h"
#include <iostream>


Timer::Timer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;
	mPaused = false;
	mStarted = false;
}

void Timer::setFps(int fps)
{
	this->_fps = fps;
	this->_ticksPerFrame = 1000 / this->_fps;
}

void Timer::delay()
{
	int ticks = this->getTicks();

	if ( ticks < this->_ticksPerFrame )
	{
		//std::cout << (this->_ticksPerFrame) - ticks << std::endl;
		SDL_Delay( (this->_ticksPerFrame) - ticks );
	}
}

void Timer::start()
{
	//Start the timer
	mStarted = true;
	//Unpause the timer
	mPaused = false;
	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void Timer::stop()
{
	//Stop the timer
	mStarted = false;
	//Unpause the timer
	mPaused = false;
	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void Timer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;
		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks; mStartTicks = 0;
	}
}

void Timer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;
		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		//Reset the paused ticks mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;
	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	return time;
}

bool Timer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool Timer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}

