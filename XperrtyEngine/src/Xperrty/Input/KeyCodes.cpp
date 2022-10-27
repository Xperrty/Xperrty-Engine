#include "xppch.h"
#include "KeyCodes.h"
namespace Xperrty {
	const char* keyCodeStr(KeyCodes code)
	{
		{
			switch (code)
			{
			case Xperrty::KEY_SPACE: return "SPACE";

			case Xperrty::KEY_APOSTROPHE: return "APOSTROPHE";

			case Xperrty::KEY_COMMA: return "COMMA";

			case Xperrty::KEY_MINUS: return "MINUS";

			case Xperrty::KEY_PERIOD: return "PERIOD";

			case Xperrty::KEY_SLASH: return "SLASH";

			case Xperrty::KEY_0: return "0";

			case Xperrty::KEY_1: return "1";

			case Xperrty::KEY_2: return "2";

			case Xperrty::KEY_3: return "3";

			case Xperrty::KEY_4: return "4";

			case Xperrty::KEY_5: return "5";

			case Xperrty::KEY_6: return "6";

			case Xperrty::KEY_7: return "7";

			case Xperrty::KEY_8: return "8";

			case Xperrty::KEY_9: return "9";

			case Xperrty::KEY_SEMICOLON: return "SEMICOLON";

			case Xperrty::KEY_EQUAL: return "EQUAL";

			case Xperrty::KEY_A: return "A";

			case Xperrty::KEY_B: return "B";

			case Xperrty::KEY_C: return "C";

			case Xperrty::KEY_D: return "D";

			case Xperrty::KEY_E: return "E";

			case Xperrty::KEY_F: return "F";

			case Xperrty::KEY_G: return "G";

			case Xperrty::KEY_H: return "H";

			case Xperrty::KEY_I: return "I";

			case Xperrty::KEY_J: return "J";

			case Xperrty::KEY_K: return "K";

			case Xperrty::KEY_L: return "L";

			case Xperrty::KEY_M: return "M";

			case Xperrty::KEY_N: return "N";

			case Xperrty::KEY_O: return "O";

			case Xperrty::KEY_P: return "P";

			case Xperrty::KEY_Q: return "Q";

			case Xperrty::KEY_R: return "R";

			case Xperrty::KEY_S: return "S";

			case Xperrty::KEY_T: return "T";

			case Xperrty::KEY_U: return "U";

			case Xperrty::KEY_V: return "V";

			case Xperrty::KEY_W: return "W";

			case Xperrty::KEY_X: return "X";

			case Xperrty::KEY_Y: return "Y";

			case Xperrty::KEY_Z: return "Z";

			case Xperrty::KEY_LEFT_BRACKET: return "LEFT_BRACKET";

			case Xperrty::KEY_BACKSLASH: return "BACKSLASH";

			case Xperrty::KEY_RIGHT_BRACKET: return "RIGHT_BRACKET";

			case Xperrty::KEY_GRAVE_ACCENT: return "GRAVE_ACCENT";

			case Xperrty::KEY_WORLD_1: return "WORLD_1";

			case Xperrty::KEY_WORLD_2: return "WORLD_2";

			case Xperrty::KEY_ESCAPE: return "ESCAPE";

			case Xperrty::KEY_ENTER: return "ENTER";

			case Xperrty::KEY_TAB: return "TAB";

			case Xperrty::KEY_BACKSPACE: return "BACKSPACE";

			case Xperrty::KEY_INSERT: return "INSERT";

			case Xperrty::KEY_DELETE: return "DELETE";

			case Xperrty::KEY_RIGHT: return "RIGHT";

			case Xperrty::KEY_LEFT: return "LEFT";

			case Xperrty::KEY_DOWN: return "DOWN";

			case Xperrty::KEY_UP: return "UP";

			case Xperrty::KEY_PAGE_UP: return "PAGE_UP";

			case Xperrty::KEY_PAGE_DOWN: return "PAGE_DOWN";

			case Xperrty::KEY_HOME: return "HOME";

			case Xperrty::KEY_END: return "END";

			case Xperrty::KEY_CAPS_LOCK: return "CAPS_LOCK";

			case Xperrty::KEY_SCROLL_LOCK: return "SCROLL_LOCK";

			case Xperrty::KEY_NUM_LOCK: return "NUM_LOCK";

			case Xperrty::KEY_PRINT_SCREEN: return "PRINT_SCREEN";

			case Xperrty::KEY_PAUSE: return "PAUSE";

			case Xperrty::KEY_F1: return "F1";

			case Xperrty::KEY_F2: return "F2";

			case Xperrty::KEY_F3: return "F3";

			case Xperrty::KEY_F4: return "F4";

			case Xperrty::KEY_F5: return "F5";

			case Xperrty::KEY_F6: return "F6";

			case Xperrty::KEY_F7: return "F7";

			case Xperrty::KEY_F8: return "F8";

			case Xperrty::KEY_F9: return "F9";

			case Xperrty::KEY_F10: return "F10";

			case Xperrty::KEY_F11: return "F11";

			case Xperrty::KEY_F12: return "F12";

			case Xperrty::KEY_F13: return "F13";

			case Xperrty::KEY_F14: return "F14";

			case Xperrty::KEY_F15: return "F15";

			case Xperrty::KEY_F16: return "F16";

			case Xperrty::KEY_F17: return "F17";

			case Xperrty::KEY_F18: return "F18";

			case Xperrty::KEY_F19: return "F19";

			case Xperrty::KEY_F20: return "F20";

			case Xperrty::KEY_F21: return "F21";

			case Xperrty::KEY_F22: return "F22";

			case Xperrty::KEY_F23: return "F23";

			case Xperrty::KEY_F24: return "F24";

			case Xperrty::KEY_F25: return "F25";

			case Xperrty::KEY_KP_0: return "KP_0";

			case Xperrty::KEY_KP_1: return "KP_1";

			case Xperrty::KEY_KP_2: return "KP_2";

			case Xperrty::KEY_KP_3: return "KP_3";

			case Xperrty::KEY_KP_4: return "KP_4";

			case Xperrty::KEY_KP_5: return "KP_5";

			case Xperrty::KEY_KP_6: return "KP_6";

			case Xperrty::KEY_KP_7: return "KP_7";

			case Xperrty::KEY_KP_8: return "KP_8";

			case Xperrty::KEY_KP_9: return "KP_9";

			case Xperrty::KEY_KP_DECIMAL: return "KP_DECIMAL";

			case Xperrty::KEY_KP_DIVIDE: return "KP_DIVIDE";

			case Xperrty::KEY_KP_MULTIPLY: return "KP_MULTIPLY";

			case Xperrty::KEY_KP_SUBTRACT: return "KP_SUBTRACT";

			case Xperrty::KEY_KP_ADD: return "KP_ADD";

			case Xperrty::KEY_KP_ENTER: return "KP_ENTER";

			case Xperrty::KEY_KP_EQUAL: return "KP_EQUAL";

			case Xperrty::KEY_LEFT_SHIFT: return "LEFT_SHIFT";

			case Xperrty::KEY_LEFT_CONTROL: return "LEFT_CONTROL";

			case Xperrty::KEY_LEFT_ALT: return "LEFT_ALT";

			case Xperrty::KEY_LEFT_SUPER: return "LEFT_SUPER";

			case Xperrty::KEY_RIGHT_SHIFT: return "RIGHT_SHIFT";

			case Xperrty::KEY_RIGHT_CONTROL: return "RIGHT_CONTROL";

			case Xperrty::KEY_RIGHT_ALT: return "RIGHT_ALT";

			case Xperrty::KEY_RIGHT_SUPER: return "RIGHT_SUPER";

			case Xperrty::KEY_MENU: return "MENU";

			default:
				break;
			}
		}
	}
}