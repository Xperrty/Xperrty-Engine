#include "xppch.h"
#include "Window.h"
//#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "Xperrty/Input/InputManager.h"
namespace Xperrty {
	Window* Window::instance = nullptr;
	Window::Window(int w, int h) :
		width(w), height(h), window(0), VSynk(VSynkMode::disabled), pendingClose(false), windowMode(WindowMode::windowed)
	{
		instance = this;
		initWindow();
		setVSynk(VSynkMode::disabled);
		//callbacks
		glfwSetKeyCallback((GLFWwindow*)window, &Window::onKeyboardEvent);
		//glfwSetCursorPosCallback(window, &Window::onMouseMoveEvent); //Probably not needed... too much spam
		glfwSetMouseButtonCallback(window, &Window::onMouseEvent);
		glfwSetScrollCallback(window, &Window::onMouseScroll);
		glfwSetWindowSizeCallback(window, &Window::onResizeCallback);
		//setVSynk(VSynkMode::enabled);
	}



	void Window::initWindow()
	{
		/* Initialize the library */
		if (!glfwInit())
			return;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(width, height, "Performance Demo", NULL, NULL);
		GLFWwindow* glfwWindow = (GLFWwindow*)window;
		if (!window)
		{
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(glfwWindow);

		//TODO:Remove glad stuff from window...
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		XP_WARN("Status:{0}", status);
		/* Make the window's context current */
	}

	void Window::updateWindow()
	{
		glfwPollEvents();
		glfwSwapBuffers((GLFWwindow*)window);
		pendingClose = glfwWindowShouldClose((GLFWwindow*)window);
	}

	void Window::resizeWindow(int w, int h)
	{
		glfwSetWindowSize((GLFWwindow*)window, w, h);
	}

	int Window::getWidth()
	{
		return width;
	}

	int Window::getHeight()
	{
		return height;
	}

	bool Window::isAlive()
	{
		return !pendingClose;
	}

	Vector2 Window::getMousePosition()
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return Vector2(x, y);
	}

	WindowMode Window::getWindowMode()
	{
		return windowMode;
	}

	bool Window::getVSynk()
	{
		return VSynk;
	}
	void Window::setWidth(int w)
	{
		width = w;
		resizeWindow(width, height);
	}
	void Window::setHeight(int h)
	{
		height = h;
		resizeWindow(width, height);
	}

	void Window::setVSynk(VSynkMode mode)
	{
		VSynk = mode;
		if (mode == VSynkMode::disabled) {
			glfwSwapInterval(0);
		}
		else if (mode == VSynkMode::enabled) {
			glfwSwapInterval(1);
		}

	}

	void Window::setFullScreen(bool mode)
	{

	}

	Window::~Window()
	{
		glfwTerminate();
	}
	void Window::onKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//XP_INFO("Pressed {0} action {1}", keyCodeStr((KeyCodes)key), action);
		InputManager::onRawKeyPressed(key, scancode, action, mods);
	}
	void Window::onMouseMoveEvent(GLFWwindow* window, double xpos, double ypos)
	{
		//XP_INFO("Mouse move x: {0} y{0}", xpos, ypos);
	}
	void Window::onMouseEvent(GLFWwindow* window, int button, int action, int mods)
	{
		InputManager::onMousePressed(button, action);
		//XP_INFO("Pressed Mouse {0} action {1}", button, action);

	}
	void Window::onMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		InputManager::onMouseScroll(yoffset);
		//XP_INFO("scroll Mouse Mouse x {0} y {1}", xoffset, yoffset);

	}
	void Window::onResizeCallback(GLFWwindow* window, int width, int height)
	{
		DoubleFloatEventData ed(width, height);
		instance->width = width;
		instance->height = height;
		EventManager::invoke(WINDOW_RESIZE, &ed);
		//XP_INFO("scroll Mouse Mouse x {0} y {1}", xoffset, yoffset);

	}
}
