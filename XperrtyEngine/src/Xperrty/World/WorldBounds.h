#pragma once
#include "GameObject.h"
#include "Xperrty/Math/Vector2ui.h"
#include "Xperrty/Performance/BatchedThreadPool.h"
namespace Xperrty {
	struct WorldBoundsCell {
		Array<GameObject*> staticObjects;
		Array<GameObject*> dynamicObjects;
		std::unique_ptr<std::mutex> cellMutex;
		int dynamicIndex = -1;
		WorldBoundsCell() :dynamicIndex(0) { cellMutex = std::make_unique<std::mutex>(); }
		inline void reset() { dynamicIndex = -1; }
		void addDynamicObject(GameObject* object);
		void addStaticObject(GameObject* object);
		void removeDynamicObject(GameObject* object);
		void removeStaticObject(GameObject* object);
		//WorldBoundsCell(const WorldBoundsCell& other) = delete;
		//WorldBoundsCell(WorldBoundsCell& other) = delete;
	};

	class WorldBounds
	{
	public:
		static WorldBounds* instance;

		//Creates the world map with the given dimensins.
		//Width and height MUST be power of 2. If they are not, they will be rounded up to closest PO2.
		void setWorldSize(unsigned int width, unsigned int height, float cellWidth, float cellHeight);

		void addObject(GameObject* object);
		void updateObject(GameObject* object);
		void removeObject(GameObject* object);
		void resetDynamic();

		inline Array<Vector2ui>& getWorldCellPositions(GameObject* object) {
			if (objectWorldMap.contains(object))
				return objectWorldMap[object];
			else return emptyArray;
		}
		inline WorldBoundsCell& getObjectsInCell(const Vector2ui& position) { return worldMap[position.x][position.y]; }


		WorldBounds() :width(0), height(0), cellWidth(0.0f), cellHeight(0.0f), worldMap(), objectWorldMap(), lodSize(), xPxOffset(0), yPxOffset(0),threadPool(std::thread::hardware_concurrency()-2) { instance = this; }
	protected:
		Array<Array<WorldBoundsCell>> worldMap;
		Dictionary<GameObject*, Array<Vector2ui>> objectWorldMap;
		Array<Vector2ui> lodSize;
		Array<Vector2ui> emptyArray;
		Array<std::mutex*> mutexArray;

		void addInMap(GameObject* object, const Rect& objectBounds, unsigned int lodLevel, unsigned int x, unsigned int y);
	private:
		~WorldBounds() { instance = nullptr; }
		float xPxOffset;
		float yPxOffset;
		unsigned int width;
		unsigned int height;
		float cellWidth;
		float cellHeight;
		std::mutex objectWorldMapMutex;
		friend class Application;
		BatchedThreadPool threadPool;
	};

}
