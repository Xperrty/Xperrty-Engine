#pragma once
#include "Xperrty/Memory/ObjectPool.h"
namespace Xperrty {

	class MemoryPoolTest {
	public:
		MemoryPoolTest() {
			XP_INFO("Starting Object Pool Test:");
			ObjectPool<int> intPool(1000);

			int* ptr1 = intPool.newObject();
			int* ptr2 = intPool.newObject();
			int* ptr3 = intPool.newObject();

			*ptr1 = 1;
			*ptr2 = 2;
			*ptr3 = 3;

			if (intPool.getIndex() != 3) throw 1;
			if (intPool.totalChunks() != 1) throw 1;

			intPool.deleteObject(ptr2);
			int* ptr4 = intPool.newObject();
			if (intPool.getIndex() != 3) throw 1;
			if (ptr4 != ptr2) throw "Pointer Locations are not EQUAL!";

			for (int i = 0; i < 1001; i++)
			{
				intPool.newObject();
			}
			if (intPool.getIndex() != 1004) throw 1;
			if (intPool.totalChunks() != 2) throw 1;

			{

				ObjectPool<int> intPool2(1000);

				for (int i = 0; i < 100000; i++)
				{
					intPool2.newObject();
				}
			}

			XP_INFO("Object Pool Test Completed Successfully!");
		}
	};
}