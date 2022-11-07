#pragma once
#include "Xperrty/Containers/Array.h"
#include "Xperrty/World/GameObject.h"
#include "Xperrty/Rendering/Utils/BufferData.h"
namespace Xperrty {
	class Batch {
	public:
		Batch(Material* material) :gameObjects(), bd(500, material->getVertexSize(),material->getShader()) {
			gameObjects.reserve(500);
		}
		void insertObject(int index, GameObject* object);


		inline BufferData& getBufferData() { return bd; }
		inline Material* getMaterial() { 
			if (gameObjects.size() > 0) return gameObjects[0]->getMaterial();
			else return nullptr;
		}
		inline int size()const { return gameObjects.size(); }
		~Batch();
	private:
		Array<GameObject*> gameObjects;
		BufferData bd;
	};

}