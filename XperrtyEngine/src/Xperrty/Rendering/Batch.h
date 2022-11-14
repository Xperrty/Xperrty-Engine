#pragma once
#include "Xperrty/Containers/Array.h"
#include "Xperrty/World/GameObject.h"
#include "Xperrty/Rendering/Utils/BufferData.h"
namespace Xperrty {
	class Batch {
	public:
		Batch(Material* material, int capacity);
		void insertObject(int index, GameObject* object);
		void addObject(GameObject* object);
		//ToDo: Remove, testing code
		void updateTransforms();
		
		inline void clear() { gameObjects.clear(); }
		inline BufferData& getBufferData() { return bd; }
		inline Material* getMaterial() { 
			if (gameObjects.size() > 0) return gameObjects[0]->getMaterial();
			else return nullptr;
		}
		inline int size()const { return gameObjects.size(); }
		inline bool isFull() { return size() >= capacity; }
		~Batch();
		Batch(const Batch& other) = delete;
		Batch(Batch& other) = delete;
		Array<GameObject*> gameObjects;
		bool done;
	private:
		BufferData bd;
		int capacity;
	};

}