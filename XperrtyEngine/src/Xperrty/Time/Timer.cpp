#include "xppch.h"
#include "Timer.h"


//namespace Xperrty {
//	template<typename T>
//	inline Timer<T>::Timer(float durationMs, int repeatTimes, T* classRef, std::function<void(T*, float)> onComplete) :onCompleteCallback(onComplete), maxTime(durationMs/1000), repeatCount(repeatTimes), cTime(0), completed(false)
//	{
//		EventManager::addEventListener(UPDATE, onEngineEvent);
//	}
//	template<typename T>
//	Timer<T>::~Timer()
//	{
//		EventManager::removeEventListener(UPDATE, onEngineEvent);
//
//	}
//	template<typename T>
//	void Timer<T>::onEngineEvent(EngineEventType eventNr, EventData& eventData)
//	{
//		if (completed) return;
//		if (eventNr == UPDATE) onUpdate((FloatEventData*)&eventData);
//	}
//	template<typename T>
//	inline void Timer<T>::onUpdate(FloatEventData* eventData)
//	{
//
//		float dt = eventData->getValue();
//		cTime += dt;
//		if (cTime >= maxTime) {
//			onCompleteCallback(classRef, cTime-maxTime);
//			repeatCount--;
//			if (repeatCount == -1) completed = true;
//			cTime -=maxTime;
//		}
//	}
//}