#pragma once
//#include "Xperrty.h"
#include <memory>
#include <Xperrty/World/GameObject.h>
#include <Xperrty/Rendering/Cameras/FollowCamera.h>
#include "Components/AnimationPlayer.h"

//Basic player controller. Movement and shooting.
class PlayerController:public Xperrty::IEngineEventListener
{
public:
	PlayerController();
	~PlayerController() { delete followCam; };
	//Listener for update.
	void onUpdate(Xperrty::EventData* eventData);
	//Engine event listener.
	void onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) override;
	//Returns the GameObject it's controlling.
	inline std::shared_ptr<Xperrty::GameObject> getPlayer() { return object; }
private:
	Xperrty::Material* mat;
	std::shared_ptr<Xperrty::GameObject> object;
	Xperrty::FollowCamera* followCam;
	AnimationPlayer* animation;
	float speed;
	int currentAnimation;
	void onShootArrow();
	float shotCooldown;
};
