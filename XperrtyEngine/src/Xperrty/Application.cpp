#include "xppch.h"
#include "Application.h"
#include "Xperrty/Loader/TextureManager.h"
#include "Xperrty/World/SceneManager.h"

//TODO:DELETE. For testing only
#include "Xperrty/Time/Timer.h"

//Tests
#include "Testing/BatchTest.h"
namespace Xperrty {

	Application::Application() :
		isRunning(true), time(new Time()), window(new Window(1920, 1080)), renderer(new Renderer2D()), mainCamera(new Camera(Rect(0, 0, 1280, 720), 1)), input(new InputManager())
	{
		updates = 0;
		TextureManager::init();
	}

	Application::~Application()
	{
		delete window;
		delete time;

	}
	void Application::run() {
		int batchSize = 200;
		Timer<Application> timer(2000.0f, -1, this, &Application::onTimerDone);

		XP_INFO("Sizeof size_t{0}", sizeof(size_t));
		while (isRunning)
		{

			time->update();
			InputManager::update();
			EventManager::invoke(UPDATE, &Time::ed);
			updates++;
			renderer->clear();
			SceneManager::instance()->renderScene();
			window->updateWindow();
			if (!window->isAlive())terminate();
		}

		return;


	}
	void Application::onTimerDone(float value) {
		XP_TRACE("Fps:{0} Objects:{1} Rendered:{2} DrawCalls:{3}", updates / 2, SceneManager::instance()->getTotalObjects(),SceneManager::instance()->getRenderedObjects(), Renderer2D::instance->getDrawCalls());
		this->updates = 0;
	}

	void Application::terminate()
	{
		isRunning = false;
	}

}
