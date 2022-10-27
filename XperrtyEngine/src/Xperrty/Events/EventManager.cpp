#include "xppch.h"
#include "EventManager.h"

namespace Xperrty {
	Dictionary<EngineEventType, Array<IEngineEventListener*>> EventManager::engineEventMap;
	std::mutex EventManager::engineEventMutex;

	void EventManager::addEventListener(EngineEventType evType, IEngineEventListener* listener)
	{
		std::lock_guard<std::mutex> lock(engineEventMutex);
		if (engineEventMap.contains(evType)) {
			engineEventMap[evType].push_back(listener);
		}
		else {
			auto arr = Array<IEngineEventListener*>();
			arr.push_back(listener);
			engineEventMap.add(evType, arr);
		}
	}

	void EventManager::removeEventListener(EngineEventType evType, IEngineEventListener* listener)
	{
		std::lock_guard<std::mutex> lock(engineEventMutex);
		if (!engineEventMap.contains(evType)) return;
		auto& arr = engineEventMap[evType];
		if (arr.contains(listener)) arr.remove(listener, true);
	}

	void EventManager::invoke(EngineEventType evType, EventData* data)
	{
		std::lock_guard<std::mutex> lock(engineEventMutex);
		if (!engineEventMap.contains(evType)) return;
		auto& arr = engineEventMap[evType];
		for (int i = 0; i < arr.size(); i++)
		{
			arr[i]->onEngineEvent(evType, data);
		}
	}

}

