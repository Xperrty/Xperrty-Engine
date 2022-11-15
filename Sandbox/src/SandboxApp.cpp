#include "Xperrty.h"
#include "CombatManager.h"
#include "TerrainGenerator.h"
#include "Xperrty/Rendering/Cameras/FollowCamera.h"
class SandboxApp :public  Xperrty::Application, public Xperrty::IEngineEventListener {
public:
	SandboxApp() : terrain(0, 0), combatManager() {
		//APP_TRACE("TRACE! {0}", 10);
		//APP_INFO("INFO!{0}", 11);
		//APP_WARN("WARN!{0}", 12);
		//APP_ERROR("ERROR{0}", 13);
		Xperrty::EventManager::addEventListener(Xperrty::UPDATE, this);
	}

	virtual void init() override {
		
	}

	// Inherited via IEngineEventListener
	virtual void onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) override
	{

		if (Xperrty::InputManager::isKeyDown(Xperrty::KEY_A, 0)) {
			//APP_TRACE("LEFT");
		}
	}
private:
	TerrainGenerator terrain;
	CombatManager combatManager;
};


Xperrty::Application* Xperrty::createApplication() {
	return new SandboxApp();
}

