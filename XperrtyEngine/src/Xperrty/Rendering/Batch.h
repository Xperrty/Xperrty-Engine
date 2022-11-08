#pragma once
#include "Xperrty/Containers/Array.h"
#include "Xperrty/World/GameObject.h"
#include "Xperrty/Rendering/Utils/BufferData.h"
namespace Xperrty {
	class Batch {
	public:
		Batch(Material* material,int size) :gameObjects(), bd(size, material->getVertexSize(),material->getShader()) {
			gameObjects.reserve(size);
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