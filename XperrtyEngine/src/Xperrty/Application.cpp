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
//#include "Xperrty/Rendering/Material.h"
namespace Xperrty {

	Application::Application() :
		isRunning(true), time(new Time()), window(new Window(1280, 720)), renderer(new Renderer2D()), mainCamera(new Camera(Rect(0, 0, 1280, 720), 1)),input(new InputManager())
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
		t->uploadToGpu();
		//Test test;
		//XP_INFO("TESTS SHOULD BE DONE!");
		RTSCamera* camera = new RTSCamera(Rect(0, 0, window->getWidth(), window->getHeight()), 1, 1000);
		camera->setActive(true);
		XP_INFO("Size of vert: {0}", sizeof(MaterialVertexData));
		while (isRunning)
		{
			
			time->update();
			InputManager::update();
			EventManager::invoke(UPDATE, &Time::ed);
			updates++;
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			renderer->renderQuadImmediate(Rect(100,100, t->getWidth(), t->getHeight()), nullptr, t, Color(1.0f, 0.0f, 0.0f, 1.0f));
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
