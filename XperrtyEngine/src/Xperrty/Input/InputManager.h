#pragma once
#include "Xperrty/Time/Time.h"
namespace Xperrty {
	struct InputInteractionEventData;
	//ToDo:Rework the entire isUp and isDown functionality.
	class InputManager
	{
	public:
		//Returns the last mouse X position.
		inline static float getX() { return x; }
		//Returns the last mouse Y position.
		inline static float getY() { return y; }
		//Returns the last Scroll X value.
		inline static float getScrollX() { return scrollX; }
		//Returns the last Scroll Y value.
		inline static float getScrollY() { return scrollY; }
		/// <summary>
		/// Checks if key was down this frame or at some point in the past.
		/// </summary>
		/// <param name="code">Key to check.</param>
		/// <param name="timeInThePast">Time interval in the past. If 0, checks only the current frame.</param>
		/// <returns></returns>
		static inline bool isKeyDown(KeyCodes code, float timeInThePast = 0)
		{
			float lastDown;
			float lastUp;
			if (downKeyMap.tryGet(code, lastDown) && upKeyMap.tryGet(code, lastUp)) {
				return lastDown>lastUp;
			}
			return downKeyMap.contains(code);
		}

		//Returns true if key was release this frame.
		static inline bool isKeyUp(KeyCodes code, float timeInThePast = 0)
		{
			float lastUp;
			if (upKeyMap.tryGet(code, lastUp)) {
				return lastUp == Time::now();
			}
			return false;
		}
		//Returns true if mouse is down this frame. (True as long as mouse button is held down)
		static inline bool isMouseDown(MouseCodes code, float timeInThePast = 0)
		{
			float lastDown;
			float lastUp;
			if (downMouseMap.tryGet(code, lastDown) && upMouseMap.tryGet(code, lastUp)) {
				return lastDown>lastUp;
			}
			return downMouseMap.contains(code);
		}
		//Update the input system.
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
		static Dictionary<MouseCodes, float> downMouseMap;
		static Dictionary<MouseCodes, float> upMouseMap;
		static Array<std::pair<KeyCodes, InputActions>> keyActionsList;
		static Array<std::pair<MouseCodes, InputActions>> mouseActionsList;
		static InputInteractionEventData* inputActionEventData;
		//ToDo: If input is pressed and released in the same frame, the press doesn't register.
		static void processKeyboardEvents();
		static void processMouseEvents();
	};

	struct InputInteraction {
		InputInteraction() : keyCode(KEY_A), mouseCode(MOUSE_BUTTON_1), scrollValue(0), action(Down) {}
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
