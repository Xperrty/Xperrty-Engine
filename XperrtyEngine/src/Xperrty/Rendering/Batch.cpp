#include "xppch.h"
#include "Batch.h"

namespace Xperrty {

	Batch::~Batch() {

	}

	void Batch::insertObject(int index, GameObject* object) {
		if (index <= gameObjects.size()) {
			gameObjects.insert(gameObjects.begin() + index, object);
		}
	}
}