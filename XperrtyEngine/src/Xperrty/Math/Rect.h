#pragma once
namespace Xperrty {

	class Rect
	{
	public:
		inline float getX() const { return x; };
		inline float getY() const { return y; };
		inline float getWidth() const { return width; };
		inline float getHeight() const { return height; };
		inline float getRight() const { return x + width; };
		inline float getBot() const { return y + height; };
		inline float getCenterX() const { return x + width / 2; };
		inline float getCenterY() const { return y + height / 2; };
		inline Vector2 getCenter() const { return Vector2(getCenterX(), getCenterY()); };

		inline void setX(float newX) { x = newX; };
		inline void setY(float newY) { y = newY; };
		inline void setWidth(float newW) { width = newW; };
		inline void setHeight(float newH) { height = newH; };
		inline void setCenterX(float newCX) { x = newCX - width / 2; };
		inline void setCenterY(float newCY) { y = newCY - height / 2; };
		inline void setCenter(const Vector2& newC) {
			x = newC.x - width / 2;
			y = newC.y - height / 2;
		};

		Rect();
		void rescale(float scaleX, float scaleY);
		Rect(float x, float y, float width, float height);
		//Quick AABB Collision
		static bool intersects(const Rect& first, const Rect& second);
		//AABB With rotation. NOT IMPLEMENTED! ToDo:implement
		static bool intersects(const Rect& first, float rotationFirst, const Rect& second, float rotationSecond);
		//AABB With rotation and anchors. NOT IMPLEMENTED! ToDo:implement
		static bool intersects(const Rect& first, float rotationFirst, const Vector2& anchorFirst, const Rect& second, float rotationSecond, const Vector2& anchorSecond);
		~Rect();
		float x;
		float y;
		float width;
		float height;
	private:

		//void recalculateCenter();
	};

}
