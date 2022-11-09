#include "xppch.h"
#include "Batch.h"
#include "Xperrty/Time/Time.h"
namespace Xperrty {

	Batch::~Batch() {

	}

	Batch::Batch(Material* material, int size) :gameObjects(), bd(size, material->getVertexSize(), material->getShader()),done(false) {
		gameObjects.reserve(size);
	}

	void Batch::insertObject(int index, GameObject* object) {
		if (index <= gameObjects.size()) {
			gameObjects.insert(gameObjects.begin() + index, object);
		}
	}

	void Batch::updateTransforms() {
		for (int i = 0; i < gameObjects.size(); i++)
		{
			GameObject* go = gameObjects[i];
			go->setX(go->getX() + Time::dt() * 5);
			go->setY(go->getY() + Time::dt() * 5);
			go->setScaleX(go->getScaleX() + Time::dt() * 0.0015);
			go->setScaleY(go->getScaleY() + Time::dt() * 0.0015);
			go->setAngle(go->getAngle() + Time::dt() * 360);
			go->updateTransform();
			go->getMaterial()->updateVertices();
		}
		done = true;
	}
}