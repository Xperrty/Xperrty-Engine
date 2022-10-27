#pragma once
#include "xppch.h"
#include "Core.h"
#include "Xperrty/Rendering/Window.h"
#include "Xperrty/Time/Time.h"
#include "Xperrty/Rendering/Renderer2D.h"
#include "Xperrty/Rendering/Camera.h"
#include "Xperrty/Input/InputManager.h"
namespace Xperrty {

	class Application
	{
	protected:
		bool isRunning;
		Time* time;
		Window* window;
		Renderer2D* renderer;
		Camera* mainCamera;
		InputManager* input;
		void onTimerDone(float extraTime);
		int updates;
	public:
		Application();
		virtual ~Application();
		void run();
		void terminate();
	};

	Application* createApplication();
}
