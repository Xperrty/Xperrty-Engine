#include "xppch.h"
#include "Test.h"
#include "WorldBoundsTest.h"
//#include "Xperrty/Events/EventDispatcher.h"
namespace Xperrty {
	namespace Tests {
		Test::Test() {
			XP_INFO("Should start tests!");
			WorldBoundsTest test;
		}
	}
}
