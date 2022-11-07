#include "xppch.h"
#include "Time.h"
namespace Xperrty {

	Time::Time()
	{
		lastTime = internalTime();
	}

	inline long long Time::internalTime()
	{
		return std::chrono::high_resolution_clock::now().time_since_epoch().count();
	}

	void Time::update()
	{
		totalFramesRendered++;
		long long t = internalTime();
		deltaTimeMs = (t - lastTime) / 1000000.0f;
		deltaTime = deltaTimeMs / 1000.0f;
		timeSinceStartup += deltaTime;
		lastTime = t;
		ed.setValue(deltaTime);
		
	}

	float Time::dt()
	{
		return deltaTime;
	}

	float Time::dtMS()
	{
		return deltaTimeMs;
	}

	float Time::now()
	{
		return timeSinceStartup;
	}

	int Time::totalFrames()
	{
		return totalFramesRendered;
	}

	Time::~Time()
	{
	}

	float Time::deltaTime(0);
	float Time::deltaTimeMs(0);
	float Time::timeSinceStartup(0);
	int Time::totalFramesRendered(0);
	long long Time::lastTime(0);
	FloatEventData Time::ed(0);
}