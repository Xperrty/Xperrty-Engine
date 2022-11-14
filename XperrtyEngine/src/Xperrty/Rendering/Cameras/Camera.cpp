#include "xppch.h"
#include "Camera.h"

namespace Xperrty {
	Camera::Camera(Rect bounds, float scale) :bounds(bounds), scale(scale), active(false)
	{
		if (activeCamera == nullptr)activeCamera = this;
		EventManager::addEventListener(WINDOW_RESIZE, this);
		XP_INFO("CAMERA CREATED!");
	}
	void Camera::onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) {
		if (eventNr == WINDOW_RESIZE) {

			DoubleFloatEventData* ed = static_cast<DoubleFloatEventData*>(eventData);
			bounds.setWidth(ed->getValue1());
			bounds.setHeight(ed->getValue2());
		}
		//XP_INFO("RESIZE CAMERA! bounds w:{0} h:{1}", bounds.getWidth(), bounds.getHeight());
		//XP_INFO("Camera bounds w:{0} h:{1}", bounds.getWidth(), bounds.getHeight());

	}
	Camera::~Camera()
	{
		if (activeCamera == this) activeCamera == nullptr;
	}

	Vector2 Camera::screenToWorldPoint(float x, float y) {
		float scaledX = x * scale;
		float scaledY = y * scale;
		return Vector2(bounds.getCenter().x - bounds.getWidth() * scale / 2 + scaledX, bounds.getCenter().y - bounds.getHeight() * scale / 2 + scaledY);
	}
	Camera* Camera::activeCamera = nullptr;
}