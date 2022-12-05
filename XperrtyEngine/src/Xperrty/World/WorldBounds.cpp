#include "xppch.h"
#include "WorldBounds.h"
#include "Xperrty/Math/Utils/MathFunctions.h"

namespace Xperrty {
	void WorldBoundsCell::addDynamicObject(GameObject* object) {
		//ToDo:find a way to optimize this.
		std::lock_guard<std::mutex> guard(*cellMutex);
		dynamicIndex++;
		if (dynamicIndex < static_cast<int>(dynamicObjects.size()) - 1) {
			//XP_INFO("Index{0}, size {1}, if{2}", dynamicIndex, static_cast<int>(dynamicObjects.size()) - 1, dynamicIndex < dynamicObjects.size() - 1);
			dynamicObjects[dynamicIndex] = object;
		}
		else dynamicObjects.push_back(object);
	}
	void WorldBoundsCell::addStaticObject(GameObject* object) {
		std::lock_guard<std::mutex> guard(*cellMutex);
		staticObjects.push_back(object);
	}
	void WorldBoundsCell::removeDynamicObject(GameObject* object) {}
	void WorldBoundsCell::removeStaticObject(GameObject* object) {}
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
		int skip = 1;
		while (wCopy || hCopy)
		{
			if (wCopy == 0) wCopy = 1;
			if (hCopy == 0) hCopy = 1;
			if (skip)lodSize.emplace_back(wCopy, hCopy);
			//skip = (skip + 1) % 2;
			wCopy /= 2;
			hCopy /= 2;
		}
		if (lodSize.back().x != 1 || lodSize.back().y != 1) lodSize.emplace_back(1, 1);
		//mutexArray = Array<std::mutex*>();
		mutexArray.reserve(width);
		for (int i = 0; i < width; i++)
		{
			mutexArray.emplace_back(new std::mutex());
		}

		xPxOffset = -static_cast<float>(width) / 2.0f * cellWidth;
		yPxOffset = -static_cast<float>(height) / 2.0f * cellHeight;
		XP_INFO("xOffset:{0} yOffset:{1}", xPxOffset, yPxOffset);

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
		object->getWorldCells().clear();
		removeObject(object);
		Rect& objectBounds = object->getWorldBounds();
		addInMap(object, objectBounds, 0, 0, 0);
	}
	void WorldBounds::removeObject(GameObject* object)
	{
		return;
		//std::lock_guard<std::mutex> objectWorldGuard(objectWorldMapMutex);
		//if (objectWorldMap.contains(object)) {
			//Array<Vector2ui>& worldPositionList = objectWorldMap[object];
			//for (int i = 0; i < worldPositionList.size(); i++)
			//{
				//Vector2ui& pos = worldPositionList[i];
				//worldMap[pos.x][pos.y].removeFromBack(object);
			//}
			//objectWorldMap.erase(object);
			//XP_INFO("removed object!!");
		//}
	}

	void WorldBounds::resetDynamic()
	{
		for (unsigned int i = 0; i < width; i++)
		{
			threadPool.queue([this, i] {

				for (unsigned int j = 0; j < height; j++)
				{
					worldMap[i][j].reset();
				}
				});
		}
		threadPool.start();
		threadPool.waitAll();
	}

	void WorldBounds::addInMap(GameObject* object, const Rect& objectBounds, unsigned int lodLevel, unsigned int x, unsigned int y)
	{
		//this lod level size
		unsigned int lodWidth = lodSize[lodLevel].x;
		unsigned int lodHeight = lodSize[lodLevel].y;
		//lod level cell Size
		unsigned int lodCellWidth = lodWidth * cellWidth;
		unsigned int lodCellHeight = lodHeight * cellHeight;
		//prev lod level size
		unsigned int prevLodWidth = lodLevel == 0 ? width : lodSize[lodLevel - 1].x;
		unsigned int prevLodHeight = lodLevel == 0 ? height : lodSize[lodLevel - 1].y;
		//start index for this lod
		unsigned int startX = lodLevel == 0 ? 0 : lodSize[lodLevel - 1].x * x / lodWidth;
		unsigned int startY = lodLevel == 0 ? 0 : lodSize[lodLevel - 1].y * y / lodHeight;
		for (unsigned int i = startX; i < startX + prevLodWidth / lodWidth; i++)
		{
			bool intersected = false;
			for (unsigned int j = startY; j < startY + prevLodHeight / lodHeight; j++)
			{
				Rect lodBound(xPxOffset + i * lodWidth * cellWidth, yPxOffset + j * lodHeight * cellHeight, lodCellWidth, lodCellHeight);
				bool intersects = Rect::intersects(objectBounds, lodBound);
				if (intersects) {
					intersected = true;
					//XP_INFO("Found intersection between object X{0} Y{1} W{2} H{3} and Bounds X{4} Y{5} W{6} H{7}", objectBounds.x, objectBounds.y, objectBounds.width, objectBounds.height, lodBound.x, lodBound.y, lodBound.width, lodBound.height);
					if (lodLevel != lodSize.size() - 1) {
						addInMap(object, objectBounds, lodLevel + 1, i, j);
					}
					else {
						object->getWorldCells().emplace_back(i * lodWidth, j * lodHeight);
						worldMap[i][j].addDynamicObject(object);
					}
				}
				else if (intersected) {
					break;
				}
			}
		}
	}

	WorldBounds* WorldBounds::instance;
}