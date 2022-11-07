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
		if (keyActionsList.size() != 0) processKeyboardEvents();
		scrollX = lastScrollX;
		scrollY = lastScrollY;

		lastScrollX = 0;
		lastScrollY = 0;
		//Mouse
	}

	void InputManager::processKeyboardEvents() {
		//First we process all the actions.
		for (int i = 0; i < keyActionsList.size(); i++)
		{
			KeyCodes& key = keyActionsList[i].first;
			InputActions& action = keyActionsList[i].second;

			if (action == Down)downKeyMap.add((Xperrty::KeyCodes)key, Time::now());
			else if (action == Up) upKeyMap.add((Xperrty::KeyCodes)key, Time::now());
		}
		//Then we send the events
		for (int i = 0; i < keyActionsList.size(); i++)
		{
			KeyCodes& key = keyActionsList[i].first;
			InputActions& action = keyActionsList[i].second;
			InputInteraction& interaction = inputActionEventData->getValue();
			interaction.keyCode = key;
			interaction.action = action;
			if (action == Down)EventManager::invoke(EngineEventType::INPUT_KEY_DOWN, inputActionEventData);
			else if (action == Up) EventManager::invoke(EngineEventType::INPUT_KEY_UP, inputActionEventData);
		}
		keyActionsList.clear();
	}

	void InputManager::onRawKeyPressed(int key, int scancode, int action, int mods)
	{
		//if (action == 1)downKeyMap.add((Xperrty::KeyCodes)key, Time::now());
		//else if (action == 0) upKeyMap.add((Xperrty::KeyCodes)key, Time::now());
		keyActionsList.push_back(std::make_pair((KeyCodes)key, (InputActions)action));
	}
	void InputManager::onMousePressed(int button, int action)
	{
		mouseActionsList.push_back(std::make_pair((MouseCodes)button, (InputActions)action));
	}
	void InputManager::onMouseScroll(float offset)
	{
		lastScrollY = offset;
	}
	float InputManager::x = 0;
	float InputManager::y = 0;
	float InputManager::scrollX = 0;
	float InputManager::scrollY = 0;
	float InputManager::lastScrollX = 0;
	float InputManager::lastScrollY = 0;
	Dictionary<KeyCodes, float> InputManager::downKeyMap;
	Dictionary<KeyCodes, float> InputManager::upKeyMap;

	Array<std::pair<KeyCodes, InputActions>> InputManager::keyActionsList;
	Array<std::pair<MouseCodes, InputActions>> InputManager::mouseActionsList;

	InputInteractionEventData* InputManager::inputActionEventData = new InputInteractionEventData();
}