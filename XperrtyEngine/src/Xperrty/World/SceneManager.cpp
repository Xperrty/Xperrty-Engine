#include "xppch.h"
#include "SceneManager.h"
#include "Xperrty/Time/Stopwatch.h"
#include "Xperrty/Rendering/Renderer2D.h"
namespace Xperrty {
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
	//ToDo:implement
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
	
	void SceneManager::renderScene() {
		//Stopwatch sw;
		for (int i = 0; i < batches.size(); i++)
		{
			batches[i]->clear();
		}
		for (int i = 0; i < objectList.size(); i++)
		{
			if (objectList[i] != nullptr)addObjectInBatch(objectList[i]);
		}

		for (int j = 0; j < batches.size(); j++)
		{
			Batch* batch = batches[j].get();
			batch->done = false;
			//batch->updateTransforms();
			if (batch->size() != 0) threadPool.queue([&, b = batch] {b->updateTransforms(); });
		}
		threadPool.start();
		for (int j = 0; j < batches.size(); j++)
		{
			Batch& batch = *batches[j];
			//Quick spinlock to make sure the batch is done updating before rendering it.
			while (!batch.done && batch.size()!=0) {
				//XP_INFO("Spinlock");
			}
			if (batch.size() != 0)Renderer2D::instance->renderBatch(batch);
		}
		threadPool.waitAll();
	}
	//ToDo:change the harcoded sizes and cores.
	SceneManager::SceneManager() :goPool(400), threadPool(4) {

	}

	SceneManager* SceneManager::_instance = nullptr;
	SceneManager* SceneManager::instance() {
		if (_instance) return _instance;
		_instance = new SceneManager();
		return _instance;
	}
}