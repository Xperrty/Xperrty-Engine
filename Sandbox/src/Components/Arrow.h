#pragma once
#include "Xperrty/World/Component.h"
#include "Xperrty/World/GameObject.h"
#include "Xperrty/Math/Vector2.h"

//ToDo:Refactor to projectile.
//Class that implements basic projectile movement.
class Arrow :public Xperrty::Component
{
public:
	Arrow():speed(0) {}
	~Arrow() {}

	virtual void onAddedToObject()override {}
	virtual void init()override {};
	virtual void onUpdate(float dt);

	//Sets the direction and speed of the projectile.
	inline void setDirection(const Xperrty::Vector2& direction, float speed) { this->direction = direction; this->speed = speed; }
	//Sets the direction and speed of the projectile.
	inline void setSpeed(float speed) { this->speed = speed; };


private:
	float speed;
	Xperrty::Vector2 direction;
};