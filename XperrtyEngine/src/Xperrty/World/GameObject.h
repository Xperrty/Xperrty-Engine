#pragma once
#include "Component.h"
#include "Xperrty/Rendering/Material.h"
#include "Xperrty/Math/TransformMatrix2D.h"
#include "Xperrty/Math/MathDefines.h"
namespace Xperrty {

	class GameObject
	{
	public:
		GameObject();
		GameObject(const std::string& name);
		GameObject(const std::string& name, const Vector2& position);
		GameObject(const std::string& name, const Vector2& position, const Vector2& scale);
		GameObject(const std::string& name, const Vector2& position, const Vector2& scale, float angle);
		GameObject(const std::string& name, const Vector2& position, const Vector2& scale, float angle, const Vector2& anchor);

		void updateTransform();



		inline TransformMatrix2D& getWorldTransformMatrix() { return transformMatrix; }

		inline void setX(float x) { position.x = x; transformChanged = true; }
		inline void setY(float y) { position.y = y; transformChanged = true; }
		inline void setScaleX(float x) { scale.x = x; transformChanged = true; }
		inline void setScaleY(float y) { scale.y = y; transformChanged = true; }
		inline void setAngle(float angle) { angle = angle; rotation = toRadians(angle); transformChanged = true; }
		inline void setRotation(float rotation) { rotation = rotation; angle = toDegrees(rotation); transformChanged = true; }
		inline void setAnchorX(float x) { anchor.x = x; transformChanged = true; }
		inline void setAnchorY(float y) { anchor.y = y; transformChanged = true; }
		inline void setName(std::string newName) { name = newName; }
		void setMaterial(Material* m );

		inline float getX() { return position.x; }
		inline float getY() { return position.y; }
		inline float getScaleX() { return scale.x; }
		inline float getScaleY() { return scale.y; }
		inline float getAngle() { return angle; }
		inline float getRotation() { return rotation; }
		inline float getAnchorX() { return anchor.x; }
		inline float getAnchorY() { return anchor.y; }
		inline float getAlpha() { return alpha; }
		inline float getWorldAlpha() { return worldAlpha; }
		inline std::string& getName() { return name; }
		inline Material* getMaterial() { return material; }

	private:
		Vector2 position;
		Vector2 scale;
		float angle;
		float rotation;
		float alpha;
		float worldAlpha;
		Vector2 anchor;
		TransformMatrix2D transformMatrix;
		bool transformChanged;
		bool visible;
		std::string name;
		GameObject* parent;
		Array<GameObject*> children;
		Array<Component*> components;
		Material* material;
	};
}

