#pragma once
#include "Xperrty/Events/IEventListener.h"
namespace Xperrty {
	template<typename T>
	class Timer :public IEngineEventListener
	{

	public:
		Timer(float durationMs, int repeatTimes, T* classPtr, std::function<void(T*, float)>onComplete) :onCompleteCallback(onComplete), classRef(classPtr), maxTime(durationMs / 1000), repeatCount(repeatTimes), cTime(0), completed(false) {
			EventManager::addEventListener(UPDATE, this);
		}
		~Timer() {
			EventManager::removeEventListener(UPDATE, this);
		}
		inline bool isDone() { return completed; }
	private:
		std::function<void(T*, float)> onCompleteCallback;
		T* classRef;
		float maxTime;
		int repeatCount;
		float cTime;
		bool completed;

		// Inherited via IEngineEventListener
		virtual void onEngineEvent(EngineEventType eventNr, EventData* eventData) override {
			if (completed) return;
			if (eventNr == UPDATE) onUpdate((FloatEventData*)eventData);
		}
		inline void onUpdate(FloatEventData* eventData) {
			float dt = eventData->getValue();
			cTime += dt;
			if (cTime >= maxTime) {
				onCompleteCallback(classRef, cTime - maxTime);
				repeatCount--;
				if (repeatCount == -1) completed = true;
				cTime -= maxTime;
			}
		}
	};




}
