#include "xppch.h"
#include "Rect.h"
//#include "Xperrty/Utils/Log.h"
namespace Xperrty {



	Rect::Rect() :x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 }
	{
	}

	void Rect::rescale(float scaleX, float scaleY)
	{
		float cx = getCenterX();
		float cy = getCenterY();
		width *= scaleX;
		height *= scaleY;
		setCenterX(cx);
		setCenterY(cy);

	}

	Rect::Rect(float x, float y, float width, float height) :x(x), y(y), width(width), height(height)
	{
	}

	bool Rect::intersects(const Rect& first, const Rect& second)
	{
		return first.x < second.x + second.width &&
			first.x + first.width > second.x &&
			first.y < second.y + second.height &&
			first.y + first.height > second.y;
	}

	bool Rect::intersects(const Rect& first, float rotationFirst, const Rect& second, float rotationSecond)
	{
		return false;
	}

	bool Rect::intersects(const Rect& first, float rotationFirst, const Vector2& anchorFirst, const Rect& second, float rotationSecond, const Vector2& anchorSecond)
	{
		return false;
	}

	Rect::~Rect()
	{
	}
}
