#include "xppch.h"
#include "MathFunctions.h"

namespace Xperrty {
	bool isPowerOfTwo(int number)
	{
		while (number > 1) {
			if (number % 2) return false;
			number /= 2;
		}
		return true;
	}
	bool isPowerOfTwo(unsigned int number)
	{
		while (number > 1) {
			if (number % 2) return false;
			number /= 2;
		}
		return true;
	}
	int roundUpToPowerOfTwo(int number)
	{
		int rez = 1;
		while (rez < number)
		{
			rez << 1;
		}
		return rez;
	}
	unsigned int roundUpToPowerOfTwo(unsigned int number)
	{
		unsigned int rez = 1;
		while (rez < number)
		{
			rez = rez << 1;
		}
		return rez;
	}
}