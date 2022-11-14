#include"xppch.h"
#include "Arrow.h"

void Arrow::onUpdate(float dt) {
	gameObject->setX(gameObject->getX() + direction.x * speed * dt);
	gameObject->setY(gameObject->getY() + direction.y * speed * dt);
	speed -= 500 * dt;
	if (speed < 0) {
		gameObject->setAlpha(0);
		speed = 0;
	}
	else if (speed < 100) gameObject->setAlpha(speed / 100.0);
}