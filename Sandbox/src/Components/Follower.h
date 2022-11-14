#pragma once
#include "Xperrty/World/Component.h"
#include "Xperrty/Rendering/Texture.h"
#include "Xperrty/World/GameObject.h"

class Follower :public Xperrty::Component
{
public:
	~Follower() = default;

	virtual void onAddedToObject()override;
	virtual void init()override;
	virtual void onUpdate(float dt)override;

	void setTarget(Xperrty::GameObject* object, float speed);
	inline void setSpeed(float speed) { this->speed = speed; };

	Follower();
private:
	Xperrty::GameObject* target;
	float speed;
};