#pragma once
#include "Xperrty/Rendering/Batch.h"
#include "Xperrty/Utils/Log.h"
namespace Xperrty {

	class BatchTest
	{
	public:
		void addObjectInBatch(GameObject* go) {


			if (batches.size() == 0 || batches.back()->isFull()) {
				batches.push_back(std::make_shared<Batch>(go->getMaterial(), 2));
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
		void clearBatches() {

			for (int i = 0; i < batches.size(); i++)
			{
				batches[i]->clear();
			}
		}
		BatchTest() {
			XP_INFO("Batch Test");
			Material* mat = new Material(Shader::getShader(Shader::getDefaultShaderPath()), nullptr, nullptr);
			for (int i = 0; i < 1000; i++)
			{
				GameObject* go1 = new GameObject();
				go1->setMaterial(mat);
				objects.push_back(go1);
			}
			//batch = new Batch(mat, 200);
			addObjectInBatch(objects[0]);
			if (batches.size() != 1) XP_ERROR("Batch size !=1");
			batches[0]->clear();
			if (batches[0]->size() != 0) XP_ERROR("Batch size !=0");
			addObjectInBatch(objects[0]);
			if (batches.size() != 1) XP_ERROR("Batch size !=2");

			clearBatches();
			for (int i = 0; i < 10; i++)
			{
				addObjectInBatch(objects[i]);
			}
			if (batches.size() != 5) XP_ERROR("Batch size !=5 actual size{0}",batches.size());
			clearBatches();
			for (int i = 0; i < 10; i++)
			{
				addObjectInBatch(objects[i]);
			}
			if (batches.size() != 5) XP_ERROR("Batch size !=5 actual size{0}", batches.size());


		}

		~BatchTest() {}

	private:
		Array<std::shared_ptr<Batch>>batches;
		Array<GameObject*> objects;
	};
}
