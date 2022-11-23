#pragma once
#include "GameObject.h"
#include "Xperrty/Math/Vector2ui.h"
namespace Xperrty {

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
	protected:
		Array<Array<Array<GameObject*>>> worldMap;
		Dictionary<GameObject*, Array<Vector2ui>> objectWorldMap;
		Array<Vector2ui> lodSize;

		void addInMap(GameObject* object, const Rect& objectBounds, unsigned int lodLevel, unsigned int x, unsigned int y);
	private:
		WorldBounds() :width(0), height(0), cellWidth(0.0f), cellHeight(0.0f), worldMap(), objectWorldMap(), lodSize() { instance = this; }
		~WorldBounds() { instance = nullptr; }

		unsigned int width;
		unsigned int height;
		float cellWidth;
		float cellHeight;
		friend class Application;
	};

}
