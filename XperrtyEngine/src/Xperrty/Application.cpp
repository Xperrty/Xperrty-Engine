#include "xppch.h"
#include "Application.h"
#include "Xperrty/Loader/TextureManager.h"
#include "Xperrty/World/SceneManager.h"

//TODO:DELETE. For testing only
#include "Xperrty/Time/Timer.h"
#include "Xperrty/Testing/Test.h"

//Tests
namespace Xperrty {

	Application::Application() :
		isRunning(true), time(new Time()), window(new Window(1920, 1080)), renderer(new Renderer2D()), mainCamera(new Camera(Rect(0, 0, 1280, 720), 1)), input(new InputManager()), bounds(new WorldBounds())
	{
		updates = 0;
		TextureManager::init();
		bounds->setWorldSize(1000, 1000, 250, 250);
		//Tests::Test t;
		//bounds->setWorldSize(4096/2, 4096/2, 250, 250);
		//bounds->setWorldSize(4096*4, 4096*4, 250, 250);
		XP_INFO("Size of vector of Bounds Cell:{0}", sizeof(WorldBoundsCell));
	}

	Application::~Application()
	{
		delete window;
		delete time;

	}
	void Application::run() {
		int batchSize = 200;
		Timer<Application> timer(2000.0f, -1, this, &Application::onTimerDone);

		while (isRunning)
		{
			time->update();
			InputManager::update();
			WorldBounds::instance->resetDynamic();
			EventManager::invoke(UPDATE, &Time::ed);
			updates++;
			renderer->clear();
			SceneManager::instance()->renderScene();
			window->updateWindow();
			if (!window->isAlive())terminate();
		}
		TextureManager::destroy();
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
