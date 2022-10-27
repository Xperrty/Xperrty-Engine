#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <math.h>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Xperrty/Utils/Log.h"
#include "Xperrty/Containers/Array.h"
#include "Xperrty/Containers/Dictionary.h"
#include "Xperrty/Core.h"
#include "Xperrty/Events/EventManager.h"

//Math
#include "Xperrty/Math/Vector2.h"
#include "Xperrty/Math/Vector3.h"
#include "Xperrty/Math/Rect.h"

//Input 
#include "Xperrty/Input/KeyCodes.h"

//GLFW

#ifdef XP_PLATFORM_WINDOWS
#include <Windows.h>
#endif // XP_PLATFORM_WINDOWS
