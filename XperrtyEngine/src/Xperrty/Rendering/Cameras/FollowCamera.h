#pragma once
#include "RTSCamera.h"
#include "Xperrty/World/GameObject.h"
namespace Xperrty {
	class FollowCamera :public RTSCamera
	{
	public:
		FollowCamera(Rect bounds);
		~FollowCamera() {};

		inline void addFollowTarget(GameObject* objectToFollow) { followTarget = objectToFollow; update(); }
		void update();
	private:
		GameObject* followTarget;
	};
}