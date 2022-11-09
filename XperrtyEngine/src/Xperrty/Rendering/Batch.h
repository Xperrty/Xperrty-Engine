#pragma once
#include "Xperrty/Containers/Array.h"
#include "Xperrty/World/GameObject.h"
#include "Xperrty/Rendering/Utils/BufferData.h"
namespace Xperrty {
	class Batch {
	public:
		Batch(Material* material, int size);
		void insertObject(int index, GameObject* object);
		//ToDo: Remove, testing code
		void updateTransforms();

		inline BufferData& getBufferData() { return bd; }
		inline Material* getMaterial() { 
			if (gameObjects.size() > 0) return gameObjects[0]->getMaterial();
			else return nullptr;
		}
		inline int size()const { return gameObjects.size(); }
		~Batch();
		Array<GameObject*> gameObjects;
		bool done;
	private:
		BufferData bd;
	};

}