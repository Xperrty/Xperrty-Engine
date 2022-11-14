#include "xppch.h"
#include "Batch.h"
#include "Xperrty/Time/Time.h"
#include "Xperrty/Time/Stopwatch.h"
#include "Xperrty/Rendering/Cameras/Camera.h"
namespace Xperrty {

	Batch::~Batch() {

	}

	Batch::Batch(Material* material, int capacity) :gameObjects(), capacity(capacity), bd(capacity, material->getVertexSize(), material->getShader()), done(false) {
		gameObjects.reserve(capacity);
	}

	void Batch::insertObject(int index, GameObject* object) {
		if (index <= gameObjects.size()) {
			gameObjects.insert(gameObjects.begin() + index, object);
		}
	}
	void Batch::addObject(GameObject* object) {
		insertObject(gameObjects.size(), object);
	}

	void Batch::updateTransforms() {
		Camera* camera = Camera::getActiveCamera();
		Rect cameraBounds = camera->getBounds();
		cameraBounds.rescale(camera->getScale(), camera->getScale());
		//Stopwatch sw;
		int toRender = 0;
		for (int i = 0; i < gameObjects.size(); i++)
		{
			GameObject* go = gameObjects[i];
			//go->setX(go->getX() + Time::dt() * 5);
			//go->setY(go->getY() + Time::dt() * 5);
			//go->setScaleX(go->getScaleX() + Time::dt() * 0.015);
			//go->setScaleY(go->getScaleY() + Time::dt() * 0.015);
			//go->setAngle(go->getAngle() + Time::dt() * 360);
			go->updateTransform();
			//if (Rect::intersects(cameraBounds, go->getWorldBounds()))
				go->getMaterial()->setVerticesMemLocation((MaterialVertexData*)bd.getVertex(i));
		}
		//XP_INFO("{0}",gameObjects[0]->getAngle());
		done = true;
	}
}