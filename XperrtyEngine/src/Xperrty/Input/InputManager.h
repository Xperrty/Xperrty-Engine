#pragma once
#include "Xperrty/Time/Time.h"
namespace Xperrty {
	struct InputInteractionEventData;
	class InputManager
	{
	public:
		inline static float getX() { return x; }
		inline static float geY() { return y; }
		inline static float getScrollX() { return scrollX; }
		inline static float getScrollY() { return scrollY; }
		static inline bool isKeyDown(KeyCodes code, float timeInThePast = 0)
		{
			float lastDown;
			float lastUp;
			if (downKeyMap.tryGet(code, lastDown) && upKeyMap.tryGet(code, lastUp)) {
				//XP_INFO("LastPressed {0} Now {1} timeInThePast {2} diff {3}", lastPressed, Time::now(), timeInThePast, Time::now() - lastPressed);
				return lastDown>lastUp;
			}
			return downKeyMap.contains(code);
		}
		static void update();
	private:
		static float x;
		static float y;
		static float scrollX;
		static float scrollY;
		static float lastScrollX;
		static float lastScrollY;
		friend class Window;
		static void onRawKeyPressed(int key, int scancode, int action, int mods);
		static void onMousePressed(int button, int action);
		static void onMouseScroll(float offset);
		static Dictionary<KeyCodes, float> downKeyMap;
		static Dictionary<KeyCodes, float> upKeyMap;
		static Array<std::pair<KeyCodes, InputActions>> keyActionsList;
		static Array<std::pair<MouseCodes, InputActions>> mouseActionsList;
		static InputInteractionEventData* inputActionEventData;

		static void processKeyboardEvents();
		static void processMouseEvents();
	};

	struct InputInteraction {
		InputInteraction() : keyCode(KEY_A), mouseCode(MOUSE_BUTTON_1), scrollValue(0), action(Down) {}
		InputInteraction(const InputInteraction& other) { XP_WARN("Trying to copy input interaction!!"); }
		KeyCodes keyCode;
		MouseCodes mouseCode;
		float scrollValue;
		InputActions action;
	};

	struct InputInteractionEventData :public EventData {
	public:
		InputInteractionEventData(InputInteraction val) :value(val) {}
		InputInteractionEventData() :value(InputInteraction()) {}
		inline InputInteraction& getValue() { return value; }
		inline void setValue(InputInteraction val) { value = val; }

	private:
		InputInteraction value;
	};
	
}
