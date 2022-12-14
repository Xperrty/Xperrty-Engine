#pragma once
#include "Camera.h"
namespace Xperrty {
	class RTSCamera :public Camera {
	public:
		RTSCamera(Rect bounds, float scale, float speed);
		void enableFreeMove();
		void disableFreeMove();
		void update();
		~RTSCamera();

		virtual void onEngineEvent(EngineEventType eventNr, EventData* eventData) override;
	protected:
		float speed;
	};
};