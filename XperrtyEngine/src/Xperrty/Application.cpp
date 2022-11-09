#include "xppch.h"
#include "Application.h"
//#include "glad/glad.h"
//#include "Rendering/Renderer2D.h"

//TODO:DELETE. For testing only
#include "Xperrty/Time/Timer.h"
#include "Xperrty/Testing/Test.h"
#include "stb_image.h"
#include "Performance/ObjectPool.h"
#include "Xperrty/Math/Rect.h"
#include "Xperrty/Rendering/Cameras/RTSCamera.h"
#include "glad/glad.h"
#include "Rendering/Utils/BufferData.h"
#include "Rendering/Material.h"
#include <filesystem>
#include "Performance/BatchedThreadPool.h"
namespace Xperrty {

	Application::Application() :
		isRunning(true), time(new Time()), window(new Window(1920, 1080)), renderer(new Renderer2D()), mainCamera(new Camera(Rect(0, 0, 1280, 720), 1)), input(new InputManager())
	{
		updates = 0;

	}

	Application::~Application()
	{
		delete window;
		delete time;

	}
	void Application::run() {
		std::cout << "RUN!" << std::endl;
		int batchSize = 2000;
		Timer<Application> timer(2000.0f, -1, this, &Application::onTimerDone);
		//Broken atm. If it's running outside of visual studio debugger it will not find the files.
		std::string path = std::filesystem::current_path().string() + "\\..\\";
		//Texture* t = new Texture(path + "Sandbox\\assets\\images\\Cpu.png");
		Texture* tile2 = new Texture(path + "Sandbox\\assets\\images\\tile_2.png");
		Texture* tile3 = new Texture(path + "Sandbox\\assets\\images\\tile_3.png");
		Texture* tile1 = new Texture(path + "Sandbox\\assets\\images\\tile_1.png");
		Texture* tile4 = new Texture(path + "Sandbox\\assets\\images\\tile_4.png");
		Texture* tiles[]{ tile2,tile3,tile1, tile4 };
		Shader* shader = Shader::getShader(path + "XperrtyEngine\\src\\Xperrty\\Rendering\\Shaders\\MultiTextureShader.glsl");
		ObjectPool<GameObject> objectPool(batchSize);
		ObjectPool<Material> materialPool(batchSize);
		Array<std::shared_ptr<Batch>> batches;
		for (int i = 0; i < 10; i++)
		{
			//Testing code, won't need to make materials like this.
			Material* mat = new Material(shader, tiles[i%4], nullptr);
			batches.emplace_back(std::make_shared<Batch>(mat, batchSize));
			delete mat;
		}
		//batches.reserve(100)
		//t->uploadToGpu();
		tile2->uploadToGpu();
		tile3->uploadToGpu();
		tile1->uploadToGpu();
		tile4->uploadToGpu();
		//XP_INFO("TESTS SHOULD BE DONE!");
		RTSCamera* camera = new RTSCamera(Rect(0, 0, window->getWidth(), window->getHeight()), 1, 1000);
		camera->setActive(true);
		//Batch batch(new Material(shader,t,nullptr), batchSize);
		//objects.reserve(2000);
		for (int j = 0; j < batches.size(); j++)
		{
			Batch& batch = *batches[j];
			for (int i = 0; i < batchSize; i++)
			{
				GameObject* go = objectPool.newObject();
				Material* material = materialPool.newObject(shader, tiles[i % 4], go);
				go->setMaterial(material);
				go->setAnchorX(0);
				go->setAnchorY(0);
				material->setVerticesMemLocation((MaterialVertexData*)(batch.getBufferData().getVertex(i)));
				go->setX((i % 100) * 100);
				go->setY(j  * 100);
				go->setScaleX(0.21);
				go->setScaleY(0.21);
				batch.insertObject(i, go);
				go->updateTransform();
				/*if (i % 5 == 0) {
					material->bl->colors[0] = 1;
					material->bl->colors[1] = 0;
					material->bl->colors[2] = 0;
					material->bl->colors[3] = 1;
					material->br->colors[0] = 1;
					material->br->colors[1] = 0;
					material->br->colors[2] = 0;
					material->br->colors[3] = 1;
				}*/
				material->updateVertices();
			}
		}
		BatchedThreadPool tp(8);
		XP_WARN("Batches: {0}", batches.size());
		while (isRunning)
		{

			time->update();
			InputManager::update();
			EventManager::invoke(UPDATE, &Time::ed);
			updates++;
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			for (int j = 0; j < batches.size(); j++)
			{
				Batch& batch = *batches[j];
				batch.done = false;
				//tp.queue([&, b = &batch] {b->updateTransforms(); });
				batch.updateTransforms();
				//renderer->renderBatch(batch);
			}
			//tp.start();
			for (int j = 0; j < batches.size(); j++)
			{
				Batch& batch = *batches[j];
				while (!batch.done) {
					//XP_INFO("WHILE!");
				}
				//batch.updateTransforms();
				renderer->renderBatch(batch);
			}

			//tp.waitAll();
			//renderer->renderQuadImmediate(Rect(100, 100, t->getWidth(), t->getHeight()), nullptr, t, Color(1.0f, 0.0f, 0.0f, 1.0f));
			/*for (int i = 0; i < 1; i++)
			{
				renderer->batchRenderQuadImmediate(Rect(-0.5f, -0.5f, 1, 1), nullptr, t, Color(1.0f, 0.0f, 0.0f, 1.0f),1000);

			}*/
			//glClear(GL_COLOR_BUFFER)
			window->updateWindow();
			if (!window->isAlive())terminate();
		}

		return;


	}
	void Application::onTimerDone(float value) {
		XP_TRACE("Fps:{0}", updates / 2);
		this->updates = 0;
	}

	void Application::terminate()
	{
		isRunning = false;
	}

}
