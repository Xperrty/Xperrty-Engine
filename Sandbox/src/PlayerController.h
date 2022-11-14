#pragma once
//#include "Xperrty.h"
#include <memory>
#include <Xperrty/World/GameObject.h>
#include <Xperrty/Rendering/Cameras/FollowCamera.h>
#include "Components/AnimationPlayer.h"
class PlayerController:public Xperrty::IEngineEventListener
{
public:
	PlayerController();
	~PlayerController() {};
	void onUpdate(Xperrty::EventData* eventData);
	void onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) override;
	inline std::shared_ptr<Xperrty::GameObject> getPlayer() { return object; }
private:
	std::shared_ptr<Xperrty::GameObject> object;
	std::unique_ptr<Xperrty::Material> mat;
	Xperrty::FollowCamera* followCam;
	AnimationPlayer* animation;
	float speed;
	int currentAnimation;
	void onShootArrow();
	float shotCooldown;
};
