#include "xppch.h"
#include "WorldBounds.h"
#include "Xperrty/Math/Utils/MathFunctions.h"

namespace Xperrty {
	void WorldBounds::setWorldSize(unsigned int width, unsigned int height, float cellWidth, float cellHeight)
	{
		if (!isPowerOfTwo(width)) width = roundUpToPowerOfTwo(width);
		if (!isPowerOfTwo(height)) height = roundUpToPowerOfTwo(height);

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
				worldMap[i].emplace_back();
			}
		}
		unsigned int wCopy = width;
		unsigned int hCopy = height;
		while (wCopy || hCopy)
		{
			if (wCopy == 0) wCopy = 1;
			if (hCopy == 0) hCopy = 1;
			lodSize.emplace_back(wCopy, hCopy);
			wCopy /= 2;
			hCopy /= 2;
		}

		for (int i = 0; i < lodSize.size(); i++)
		{
			XP_INFO("W:{0} H:{1}", lodSize[i].x, lodSize[i].y);
		}
	}
	void WorldBounds::addObject(GameObject* object)
	{

	}
	void WorldBounds::updateObject(GameObject* object)
	{
		removeObject(object);
		Rect& objectBounds = object->getWorldBounds();
		addInMap(object,objectBounds, 0, 0, 0);
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

	void WorldBounds::addInMap(GameObject* object,const Rect& objectBounds, unsigned int lodLevel, unsigned int x, unsigned int y)
	{
		unsigned int lodWidth = lodSize[lodLevel].x;
		unsigned int lodHeight = lodSize[lodLevel].y;
		unsigned int prevLodWidth = lodLevel == 0 ? width : lodSize[lodLevel - 1].x;
		unsigned int prevLodHeight = lodLevel == 0 ? height : lodSize[lodLevel - 1].y;
		unsigned int startX = lodLevel == 0 ? 0 : lodSize[lodLevel - 1].x * x / lodWidth;
		unsigned int startY = lodLevel == 0 ? 0 : lodSize[lodLevel - 1].y * y / lodHeight;
		for (unsigned int i = startX; i < startX + prevLodWidth / lodWidth; i++)
		{
			for (unsigned int j = startY; j < startY + prevLodHeight / lodHeight; j++)
			{
				Rect lodBound(i * lodWidth, j * lodHeight, lodWidth, lodHeight);
				bool intersects = Rect::intersects(objectBounds, lodBound);
				if (intersects) {
					if (lodLevel != lodSize.size() - 1) {
						addInMap(object,objectBounds, lodLevel + 1, i, j);
					}
					else {
						//ToDo:Add a lock guard
						worldMap[i][j].push_back(object);
					}
				}
			}
		}
	}

	WorldBounds* WorldBounds::instance;
}