#pragma once
#include <chrono>
#include "Xperrty/Events/EventData.h"
namespace Xperrty {

	class Time
	{
	private:
		static float deltaTime;
		static float deltaTimeMs;
		//Time Since app startup in seconds.
		static float timeSinceStartup;
		static long long lastTime;
		static int totalFramesRendered;

		static long long inline internalTime();
	public:
		Time();

		static void update();

		static float dt();
		static float dtMS();
		static float now();
		static int totalFrames();
		static FloatEventData ed;
		

		~Time();
	};

}
