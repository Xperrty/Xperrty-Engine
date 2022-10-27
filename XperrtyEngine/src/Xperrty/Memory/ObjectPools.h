#pragma once
#include "ObjectPool.h"
#include "Xperrty/World/GameObject.h"
#include "Xperrty/Math/Vector2.h"
#include "Xperrty/Math/Vector3.h"
namespace Xperrty {

	class ObjectPools {
	public:
		static ObjectPool<GameObject> gameObjectPool;
		static ObjectPool<Vector2> vector2Pool;
		static ObjectPool<Vector3> vector3Pool;
	private:
		ObjectPools();
	};
}