#include "xppch.h"
#include "Application.h"
//#include "glad/glad.h"
//#include "Rendering/Renderer2D.h"

//TODO:DELETE
#include "Xperrty/Time/Timer.h"
#include "Xperrty/Testing/Test.h"
#include "stb_image.h"
#include "Performance/ObjectPool.h"
#include "Xperrty/Math/Rect.h"
#include "Xperrty/Rendering/Cameras/RTSCamera.h"
#include "glad/glad.h"
#include "Rendering/Utils/BufferData.h"
#include "Rendering/Material.h"
//#include "Xperrty/Rendering/Material.h"
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
		Timer<Application> timer(5000.0f, -1, this, &Application::onTimerDone);
		Texture* t = new Texture("E:\\Projects\\Git\\Xperrty-Engine\\Sandbox\\assets\\images\\Cpu.png");
		Shader* shader = Shader::getShader("E:\\Projects\\Git\\Xperrty-Engine\\XperrtyEngine\\src\\Xperrty\\Rendering\\Shaders\\MultiTextureShader.glsl");
		ObjectPool<GameObject> objectPool(2000);
		ObjectPool<Material> materialPool(2000);
		//Texture* t = new Texture("D:\\Performance 4\\Xperrty-Engine\\Sandbox\\assets\\images\\Cpu.png");
		t->uploadToGpu();
		//Test test;
		//XP_INFO("TESTS SHOULD BE DONE!");
		RTSCamera* camera = new RTSCamera(Rect(0, 0, window->getWidth(), window->getHeight()), 1, 1000);
		camera->setActive(true);
		//BufferData bd(2000, sizeof(MaterialVertexData), shader);

		//GameObject* go = new GameObject("Test", { 0,0 }, { 1,1 }, 0, { 0.5,0.5 });
		//Material* material = new Material(shader, t, go);
		//go->setMaterial(material);
		//Array<GameObject*> objects;
		Batch batch(new Material(shader,t,nullptr),2000);
		//objects.reserve(2000);
		for (int i = 0; i < 2; i++)
		{
			GameObject* go = objectPool.newObject();
			Material* material =materialPool.newObject(shader, t, go);
			go->setMaterial(material);
			go->setAnchorX(0);
			go->setAnchorY(0);
			material->setVerticesMemLocation((MaterialVertexData*)(batch.getBufferData().getVertex(i)));
			//go->setX((i%10) * 100);
			//go->setX(i%100 * 10);
			go->setX(i*300);
			go->setY(i*50);
			//go->setY(i/10 * 100);
			//go->setScaleX(0.1);
			//go->setScaleY(0.1);
			batch.insertObject(i,go);
			go->updateTransform();
			if (i == 10) {
				material->bl->colors[0] = 1;
				material->bl->colors[1] = 0;
				material->bl->colors[2] = 0;
				material->bl->colors[3] = 1;
				material->br->colors[0] = 1;
				material->br->colors[1] = 0;
				material->br->colors[2] = 0;
				material->br->colors[3] = 1;
			}
			material->updateVertices();
			//if (i == 500) {
				XP_INFO("BL {0},{1} BR{2},{3} TR{4},{5} TL{6},{7}", material->bl->position[0], material->bl->position[1], material->br->position[0], material->br->position[1], material->tr->position[0], material->tr->position[1], material->tl->position[0], material->tl->position[1]);
				
			//}
			//XP_INFO("A{0} B{1} C{2} D{3} TX{4} TY{5}", go->getWorldTransformMatrix().getA(), go->getWorldTransformMatrix().getB(), go->getWorldTransformMatrix().getC(), go->getWorldTransformMatrix().getD(), go->getWorldTransformMatrix().getTx(), go->getWorldTransformMatrix().getTy());
		}
		XP_INFO("Batch size:{0} Vert Size: {1}", batch.size(), sizeof(MaterialVertexData));
		//batch.
		while (isRunning)
		{

			time->update();
			InputManager::update();
			EventManager::invoke(UPDATE, &Time::ed);
			updates++;
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->renderBatch(batch);
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
		XP_TRACE("Fps:{0}", updates / 5);
		this->updates = 0;
	}

	void Application::terminate()
	{
		isRunning = false;
	}

}
