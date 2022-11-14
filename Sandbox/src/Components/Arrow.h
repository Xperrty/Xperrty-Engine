#pragma once
#include "Xperrty/World/Component.h"
#include "Xperrty/World/GameObject.h"
#include "Xperrty/Math/Vector2.h"

class Arrow :public Xperrty::Component
{
public:
	Arrow() {}
	~Arrow() {}

	virtual void onAddedToObject()override {}
	virtual void init()override {};
	virtual void onUpdate(float dt);

	inline void setDirection(const Xperrty::Vector2& direction, float speed) { this->direction = direction; this->speed = speed; }
	inline void setSpeed(float speed) { this->speed = speed; };


private:
	float speed;
	Xperrty::Vector2 direction;
};