#include "xppch.h"
#include "Rect.h"
namespace Xperrty {



	Rect::Rect() :x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 }
	{
	}

	Rect::Rect(float x, float y, float width, float height) :x(x), y(y), width(width), height(height)
	{
	}

	Rect::~Rect()
	{
	}
}
