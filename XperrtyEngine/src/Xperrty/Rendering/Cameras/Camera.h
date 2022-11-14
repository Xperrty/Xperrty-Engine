#pragma once
namespace Xperrty {

	class Camera: public IEngineEventListener
	{
	public:
		Camera(Rect bounds, float scale);
		static inline Camera* getActiveCamera() { return activeCamera; };
		static inline void setActiveCamera(Camera* newCamera) { activeCamera = newCamera; };
		inline void setCenterX(float val) { bounds.setCenterX(val); }
		inline void setCenterY(float val) { bounds.setCenterY(val); }
		inline void setScale(float val) { scale = val; }
		inline float getCenterX() { bounds.getCenterX(); }
		inline float getCenterY() { bounds.getCenterY(); }
		inline Rect getBounds() { return bounds; }
		inline void setActive(bool val) { active = val; Camera::setActiveCamera(this);}
		inline bool isActive() { return active; }
		inline float getScale() { return scale; }
		Vector2 screenToWorldPoint(float x, float y);
		virtual ~Camera();
	protected:
		virtual void onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) override;
		Rect bounds;
		float scale;
		bool active;
		static Camera* activeCamera;

	};

}
