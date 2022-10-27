#pragma once
#include "EventData.h"
#include <variant>
namespace Xperrty {
	enum EngineEventType;
	extern enum ClientEventType;

	class IEngineEventListener {
	public:
		//0-1000 engine Events, 1000+ client events. ALWAYS USE ENUMS FOR EventNr! USE INT AT YOUR OWN RISK!
		virtual void onEngineEvent(EngineEventType eventNr, EventData* eventData) = 0;
	};

	class IClientEventListener {
	public:
		//0-1000 engine Events, 1000+ client events. ALWAYS USE ENUMS FOR EventNr! USE INT AT YOUR OWN RISK!
		virtual void onClientEvent(ClientEventType eventNr, EventData* eventData) = 0;
	};

	enum EngineEventType {
		UPDATE, FIXED_UPDATE
	};
}