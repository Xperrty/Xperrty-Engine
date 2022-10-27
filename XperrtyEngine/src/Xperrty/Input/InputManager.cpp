#include "xppch.h"
#include "InputManager.h"
#include "Xperrty/Rendering/Window.h"

namespace Xperrty {
	void InputManager::update()
	{
		//change input positions.
		Vector2 mousePositin = Window::instance->getMousePosition();
		x = mousePositin.x;
		y = mousePositin.y;
		//Invoke all the inputs from last frame.
	}
	void InputManager::onRawKeyPressed(int key, int scancode, int action, int mods)
	{
		if (action == 1)downKeyMap.add((Xperrty::KeyCodes)key, Time::now());
		else if (action == 0) upKeyMap.add((Xperrty::KeyCodes)key, Time::now());
	}
	void InputManager::onMousePressed(int button, int action)
	{
	}
	void InputManager::onMouseScroll(float offset)
	{
	}
	float InputManager::x = 0;
	float InputManager::y = 0;
	Dictionary<KeyCodes, float> InputManager::downKeyMap;
	Dictionary<KeyCodes, float> InputManager::upKeyMap;
}