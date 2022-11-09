#include "xppch.h"
#include "Batch.h"

namespace Xperrty {

	Batch::~Batch() {

	}

	Batch::Batch(Material* material, int size) :gameObjects(), bd(size, material->getVertexSize(), material->getShader()) {
		gameObjects.reserve(size);
	}

	void Batch::insertObject(int index, GameObject* object) {
		if (index <= gameObjects.size()) {
			gameObjects.insert(gameObjects.begin() + index, object);
		}
	}

	void Batch::updateTransforms() {

	}
}