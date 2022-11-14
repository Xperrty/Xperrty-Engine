#include "xppch.h"
#include "Follower.h"
#include <math.h>
#include "Xperrty/Math/Rect.h"
void Follower::onAddedToObject() {

}
void Follower::init() {

}
void Follower::onUpdate(float dt) {
	if (!target) return;
	Xperrty::Vector2 direction(target->getWorldPosition().x - gameObject->getWorldPosition().x, target->getWorldPosition().y - gameObject->getWorldPosition().y);
	if (direction.magnitude() <= 100) return;
	direction.normalize();
	gameObject->setX(gameObject->getX() + direction.x * speed * dt);
	gameObject->setY(gameObject->getY() + direction.y * speed * dt);
	gameObject->setScaleX(direction.x >= 0 ? 1: -1);
}

Follower::Follower() :target(nullptr), speed(0) {}


void Follower::setTarget(Xperrty::GameObject* object, float speed) {
	this->speed = speed;
	this->target = object;
}