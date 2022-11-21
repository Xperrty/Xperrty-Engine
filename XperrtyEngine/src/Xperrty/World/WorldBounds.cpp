#include "xppch.h"
#include "WorldBounds.h"

namespace Xperrty {
	void WorldBounds::setWorldSize(unsigned int width, unsigned int height, float cellWidth, float cellHeight)
	{
		this->width = width;
		this->height = height;
		this->cellWidth = cellWidth;
		this->cellHeight = cellHeight;
		worldMap.reserve(width);
		for (unsigned int i = 0; i < width; i++)
		{
			worldMap.emplace_back();
			worldMap[i].reserve(height);
			for (unsigned int j = 0; j < height; j++)
			{
				worldMap[i][j].emplace_back();
			}
		}
	}
	void WorldBounds::addObject(GameObject* object)
	{

	}
	void WorldBounds::updateObject(GameObject* object)
	{
	}
	void WorldBounds::removeObject(GameObject* object)
	{
		if (objectWorldMap.contains(object)) {
			Array<Vector2ui>& worldPositionList = objectWorldMap[object];
			for (int i = 0; i < worldPositionList.size(); i++)
			{
				Vector2ui& pos = worldPositionList[i];
				worldMap[pos.x][pos.y].removeFromBack(object);
			}
			objectWorldMap.erase(object);
		}
	}
}