#pragma once
#include <SDL2/SDL.h>

class Timer
{
public:
	Timer();
	void setFps(int fps);
	void start();
	void stop();
	void pause();
	void unpause();

	void delay();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();
private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;
	bool mPaused; bool mStarted;

	int _fps = 60;
	int _ticksPerFrame;

};
