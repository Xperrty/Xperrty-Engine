#pragma once
namespace Xperrty {
	class GameObject;
	class Component
	{
	public:
		virtual void onAddedToObject() = 0;
		virtual void init() = 0;
		virtual void onUpdate(float dt) = 0;
		inline GameObject* getGameObject() { return gameObject; }
		inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
		virtual ~Component() {};
	protected:
		GameObject* gameObject;
		Component():gameObject(nullptr) {};
	private:
		//Only gameObjects can instantiate a new component.
		friend class GameObject;
	};

}
