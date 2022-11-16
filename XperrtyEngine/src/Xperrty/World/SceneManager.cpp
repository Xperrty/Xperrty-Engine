#include "xppch.h"
#include "SceneManager.h"
#include "Xperrty/Time/Stopwatch.h"
#include "Xperrty/Rendering/Renderer2D.h"
namespace Xperrty {
	//ToDo:change the harcoded sizes and cores.
	SceneManager::SceneManager() :goPool(400), threadPool(8), renderedObjects(0), multithreaded(true) {

	}

	void SceneManager::addObjectInBatch(GameObject* go) {

		if (batches.size() == 0 || batches.back()->isFull()) {
			batches.push_back(std::make_shared<Batch>(go->getMaterial(), 400));
		}
		//batches.back()->addObject(go);
		for (int i = 0; i < batches.size(); i++)
		{
			if (!batches[i]->isFull()) {
				batches[i]->addObject(go);
				break;
			}
		}
	}
	void SceneManager::addObject(GameObject* go) {
		objectList.push_back(go);
		//addObjectInBatch(go);
	}
	void SceneManager::removeObject(GameObject* go) {
		//ToDo:at some point clear this list from all the nullPointers.
		for (int i = 0; i < objectList.size(); i++)
		{
			if (objectList[i] == go) {
				objectList[i] = nullptr;
				break;
			}
		}
	}
	void SceneManager::removeNullObjects() {
		int lastIndexNull = -1;
		//order of elements is important so we are stuck with this implementation
		for (int i = objectList.size() - 1; i >= 0; i--)
		{
			//we didn't find a nullptr yet.
			if (objectList[i] == nullptr) {
				if (lastIndexNull == -1) lastIndexNull = i;
			}
			//we are at the end of nullPointer blocks
			if (objectList[i] != nullptr && lastIndexNull != -1) {
				objectList.erase(objectList.begin() + i + 1, objectList.begin() + lastIndexNull);
				lastIndexNull = -1;
				//XP_TRACE("Removing items {0}", i);
			}
		}
		if (objectList[0] == nullptr && lastIndexNull != -1) {
			objectList.erase(objectList.begin(), objectList.begin() + lastIndexNull);
			lastIndexNull = -1;
		}
	}

	void SceneManager::renderScene() {
		renderedObjects = 0;
		//Stopwatch sw;
		for (int i = 0; i < batches.size(); i++)
		{
			batches[i]->clear();
		}
		unsigned int nullObjects = 0;
		for (int i = 0; i < objectList.size(); i++)
		{
			if (objectList[i] != nullptr) {
				renderedObjects++;
				addObjectInBatch(objectList[i]);
			}
			else nullObjects++;
		}
		//if we have more than 10% of our objects as null, we clear them from the scene.
		if (static_cast<float>(nullObjects) / static_cast<float>(objectList.size()) > 0.1) {
			if (multithreaded) {

				threadPool.queue([&]()mutable {
					removeNullObjects();
					//XP_INFO("3.List Size:{0}",objectList.size() );
					});
			}
			else removeNullObjects();
		}

		for (int j = 0; j < batches.size(); j++)
		{
			Batch* batch = batches[j].get();
			batch->done = false;
			//batch->updateTransforms();
			if (batch->size() != 0) {
				if (multithreaded)threadPool.queue([&, b = batch] {b->updateTransforms(); });
				else batch->updateTransforms();
			}
		}
		threadPool.start();
		for (int j = 0; j < batches.size(); j++)
		{
			Batch& batch = *batches[j];
			//ToDo:maybe try to get rid of the spinlock and use cond Vars....
			//Quick spinlock to make sure the batch is done updating before rendering it.
			while (!batch.done && batch.size() != 0) {
				//XP_INFO("Spinlock");
			}
			if (batch.size() != 0)Renderer2D::instance->renderBatch(batch);
		}
		threadPool.waitAll();

	}

	SceneManager* SceneManager::_instance = nullptr;
	SceneManager* SceneManager::instance() {
		if (_instance) return _instance;
		_instance = new SceneManager();
		return _instance;
	}
}