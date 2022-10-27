#pragma once
#include "Xperrty/Time/Time.h"
namespace Xperrty {

	class InputManager
	{
	public:
		inline static float getX() { return x; }
		inline static float geY() { return y; }
		static inline bool isKeyDown(KeyCodes code, float timeInThePast = 0)
		{
			float lastPressed;
			if (downKeyMap.tryGet(code, lastPressed)) {
				return Time::now() - lastPressed <= timeInThePast;
			}
			return false;
		}
		static void update();
	private:
		static float x;
		static float y;
		friend class Window;
		static void onRawKeyPressed(int key, int scancode, int action, int mods);
		static void onMousePressed(int button, int action);
		static void onMouseScroll(float offset);
		static Dictionary<KeyCodes, float> downKeyMap;
		static Dictionary<KeyCodes, float> upKeyMap;
	};

	struct KeyInteraction {
		KeyCodes code;

	};
}
