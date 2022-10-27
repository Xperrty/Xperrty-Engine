#include "xppch.h"
#include "Camera.h"

namespace Xperrty {
	Camera::Camera(Rect bounds, float scale) :bounds(bounds), scale(scale)
	{
		if (activeCamera == nullptr)activeCamera = this;
	}
	Camera::~Camera()
	{
		if (activeCamera == this) activeCamera == nullptr;
	}
	Camera* Camera::activeCamera = nullptr;
}