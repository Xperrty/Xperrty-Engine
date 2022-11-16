#pragma once
#include "Xperrty/World/Component.h"
#include "Xperrty/Rendering/Texture.h"
#include "Xperrty/World/GameObject.h"

//Basic Follow behaviour, straight line towards the target. Stops when it's close to the target.
class Follower :public Xperrty::Component
{
public:
	~Follower() = default;
	//Called when component is added on the object.
	virtual void onAddedToObject()override;
	virtual void init()override;
	virtual void onUpdate(float dt)override;

	//Sets the target to follow.
	void setTarget(Xperrty::GameObject* object, float speed);
	//Changes the follow speed.
	inline void setSpeed(float speed) { this->speed = speed; };

	Follower();
private:
	Xperrty::GameObject* target;
	float speed;
};