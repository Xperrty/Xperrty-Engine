#include "xppch.h"
#include "RTSCamera.h"
#include "Xperrty/Input/InputManager.h"
namespace Xperrty {
	RTSCamera::RTSCamera(Rect bounds, float scale, float speed) :Camera(bounds, scale), speed(speed)
	{
		enableFreeMove();
	}

	void RTSCamera::enableFreeMove()
	{
		EventManager::addEventListener(UPDATE, this);
	}
	void RTSCamera::disableFreeMove()
	{
		EventManager::removeEventListener(UPDATE, this);
	}
	void RTSCamera::update()
	{
		if (InputManager::isKeyDown(KEY_A)) bounds.setX(bounds.getX() - Time::dt() * speed);
		if (InputManager::isKeyDown(KEY_D))bounds.setX(bounds.getX() + Time::dt() * speed);
		if (InputManager::isKeyDown(KEY_W))bounds.setY(bounds.getY() - Time::dt() * speed);
		if (InputManager::isKeyDown(KEY_S))bounds.setY(bounds.getY() + Time::dt() * speed);
		if (InputManager::getScrollY()) {

			//ToDo: smooth the scale... zoom in is way, way too abrupt
			Camera* camera = Camera::getActiveCamera();
			camera->setScale(camera->getScale() - InputManager::getScrollY() * 1000 * Time::dt());
			if (camera->getScale() < 0.2f) camera->setScale(0.2f);
			if (camera->getScale() > 20.0f) camera->setScale(20.0f);
		}
	}
	RTSCamera::~RTSCamera()
	{
		disableFreeMove();
	}
	void RTSCamera::onEngineEvent(EngineEventType eventNr, EventData* eventData)
	{
		update();
	}
}