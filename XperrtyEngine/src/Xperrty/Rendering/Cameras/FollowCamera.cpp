#include "xppch.h"
#include "FollowCamera.h"

namespace Xperrty {
	FollowCamera::FollowCamera(Rect bounds) :RTSCamera(bounds, 1, 0),followTarget(nullptr) {
		XP_INFO("FOLLOW CAMERA CREATED!");

	}
	void FollowCamera::update() {
		if(followTarget!= nullptr)
		bounds.setCenter(followTarget->getWorldPosition());
		//XP_INFO("Camera bounds w:{0} h:{1}", bounds.getWidth(), bounds.getHeight());

	}
}