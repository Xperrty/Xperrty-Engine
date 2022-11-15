#pragma once
#include "GameObject.h"
#include "Xperrty/Performance/ObjectPool.h"
#include "Xperrty/Performance/BatchedThreadPool.h"
#include "Xperrty/Rendering/Batch.h"
namespace Xperrty {

	class SceneManager
	{
	public:
		~SceneManager() = default;
		template <typename ...Args>
		GameObject* createObject(Args... args) {
			GameObject* go = goPool.newObject(args...);
			//addObjectInBatch(go);
			return go;
		}
		void removeObject(GameObject* go);
		void addObject(GameObject* go);
		void renderScene();
		inline int getTotalObjects() {
			if (batches.size() == 0) return 0;
			return (batches.size() - 1) * 400 + batches.back()->gameObjects.size();
		}
		static SceneManager* instance();
	private:
		void addObjectInBatch(GameObject* go);
		static SceneManager* _instance;
		SceneManager();
		ObjectPool<GameObject> goPool;
		BatchedThreadPool threadPool;
		Array<GameObject*> objectList;
		Array<std::shared_ptr<Batch>> batches;
		friend class Application;
		unsigned int renderedObjects;
	};

}