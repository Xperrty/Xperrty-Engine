#pragma once
#include "Xperrty/World/WorldBounds.h"
namespace Xperrty {
	namespace Tests {
		class WorldBoundsTest {
		public:
			WorldBoundsTest() {
				bounds = new WorldBounds();
				bounds->setWorldSize(128, 128, 100, 100);
				GameObject* obj = new GameObject();
				obj->setX(10);
				obj->setY(10);
				obj->setWidth(100);
				obj->setHeight(100);
				obj->setAnchorX(0);
				obj->setAnchorY(0);
				obj->updateTransform();
				bounds->updateObject(obj);
			}
		private:
			WorldBounds* bounds;
		};
	}
}