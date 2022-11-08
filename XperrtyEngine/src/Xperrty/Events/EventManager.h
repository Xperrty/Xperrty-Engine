#pragma once
#include "IEventListener.h"

namespace Xperrty {

	class EventManager
	{
	public:
		//TODO: Implement events for client side...
		//TODO: Implement add/remove queue... but for now adding/removing will interfere with event calls while invoking
		static void addEventListener(EngineEventType evType, IEngineEventListener* listener);
		static void removeEventListener(EngineEventType evType, IEngineEventListener* listener);
		static void invoke(EngineEventType evType, EventData* data);

	private:
		static Dictionary<EngineEventType, Array<IEngineEventListener*>> engineEventMap;
		static std::mutex engineEventMutex;
	};

}
