#include "Xperrty.h"
#include "CombatManager.h"
#include "TerrainGenerator.h"
#include "Xperrty/Rendering/Cameras/FollowCamera.h"
class SandboxApp :public  Xperrty::Application, public Xperrty::IEngineEventListener {
public:
	SandboxApp() : terrain(50, 40), combatManager() {
		Xperrty::EventManager::addEventListener(Xperrty::UPDATE, this);
		//ToDo: Memory cleanup... lifetime of all the objects and events is the same as the app atm.
	}

	virtual void init() override {
	}

	// Inherited via IEngineEventListener
	virtual void onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) override
	{

	}
private:
	TerrainGenerator terrain;
	CombatManager combatManager;
};


Xperrty::Application* Xperrty::createApplication() {
	return new SandboxApp();
}

