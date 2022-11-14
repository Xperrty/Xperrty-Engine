#pragma once
//#include "GLFW/glfw3.h"
#include "Xperrty/Core.h"
#include "GLFW/glfw3.h"
namespace Xperrty {

	enum VSynkMode
	{
		disabled,
		enabled,
		//tripleBuffered // not sure how to implement or if even worth it?
	};
	enum WindowMode {
		fullscreen,
		borderlessFullscreen,
		windowed
	};
	class Window
	{
	protected:
		int width;
		int height;
		GLFWwindow* window;
		VSynkMode VSynk;
		bool pendingClose;
		WindowMode windowMode;

		void initWindow();
	public:
		Window(int w, int h);

		void updateWindow();

		int getWidth();
		int getHeight();
		bool getVSynk();
		bool isAlive();
		Vector2 getMousePosition();
		WindowMode getWindowMode();

		void setWidth(int w);
		void setHeight(int h);
		void resizeWindow(int w, int h);
		void setVSynk(VSynkMode mode);
		void setFullScreen(bool mode);
		static Window* instance;
		~Window();
	private:
		static void onKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void onMouseMoveEvent(GLFWwindow* window, double xpos, double ypos);
		static void onMouseEvent(GLFWwindow* window, int button, int action, int mods);
		static void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
		static void onResizeCallback(GLFWwindow* window, int width, int height);
	};


}
