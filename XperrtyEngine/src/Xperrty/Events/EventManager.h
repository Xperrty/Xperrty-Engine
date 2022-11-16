#pragma once
#include "IEventListener.h"

namespace Xperrty {

	class EventManager
	{
	public:
		//TODO: Implement events for client side...
		//TODO: Implement add/remove queue... but for now adding/removing will interfere with event calls while invoking
		//Adds an event listener to an engine event.
		static void addEventListener(EngineEventType evType, IEngineEventListener* listener);
		//Removes an event listener from an engine event.
		static void removeEventListener(EngineEventType evType, IEngineEventListener* listener);
		//Invokes an engine event.
		static void invoke(EngineEventType evType, EventData* data);

	private:
		static Dictionary<EngineEventType, Array<IEngineEventListener*>> engineEventMap;
		static std::mutex engineEventMutex;
	};

}
