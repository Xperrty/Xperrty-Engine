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

		template <typename T>
		T* addComponent() {
			T* component = new T();
			components.push_back(component);
			component->setGameObject(this);
			component->onAddedToObject();
			return component;
		}
		//At the moment slow, cache the results!
		template <typename T>
		T* getComponent() {
			for (int i = 0; i < components.size(); i++)
			{
				T* rez = dynamic_cast<T*>(components[i]);
					if (rez) return rez;
			}
			return nullptr;
		}



		inline TransformMatrix2D& getWorldTransformMatrix() { return transformMatrix; }

		inline void setX(float x) { position.x = x; }
		inline void setY(float y) { position.y = y; }
		inline void setScaleX(float x) { scale.x = x; }
		inline void setScaleY(float y) { scale.y = y; }
		inline void setAngle(float angle) { this->angle = angle; rotation = toRadians(angle); }
		inline void setRotation(float rotation) { this->rotation = rotation; angle = toDegrees(rotation); }
		inline void setAnchorX(float x) { anchor.x = x; }
		inline void setAnchorY(float y) { anchor.y = y; }
		inline void setWidth(float width) { this->width = width; }
		inline void setHeight(float height) { this->height = height; }
		inline void setAlpha(float alpha) { this->alpha = alpha; }
		inline void setName(std::string newName) { name = newName; }
		inline void setIsStatic(bool isStatic) { this->isStatic = isStatic; }
		inline void translate(float x, float y) { position.x += x; position.y += y; }
		void setMaterial(Material* m);
		inline void resetToOriginalDimensions() { setWidth(material->getTexture()->getWidth()); setHeight(material->getTexture()->getHeight()); }

		inline float getX() const { return position.x; }
		inline float getY() const { return position.y; }
		inline float getScaleX() const { return scale.x; }
		inline float getScaleY() const { return scale.y; }
		inline float getAngle() const { return angle; }
		inline float getRotation() const { return rotation; }
		inline float getAnchorX() const { return anchor.x; }
		inline float getAnchorY() const { return anchor.y; }
		inline float getWidth() const { return width; }
		inline float getHeight() const { return height; }
		inline float getAlpha() const { return alpha; }
		inline float getWorldAlpha() const { return worldAlpha; }
		inline float getIsStatic() const { return isStatic; }

		inline Rect& getWorldBounds() { return worldBounds; }
		inline Vector2& getWorldPosition() { return worldPosition; }
		inline Vector2& getWorldScale() { return worldScale; }
		inline std::string& getName() { return name; }
		inline Material* getMaterial() { return material; }

		~GameObject();

	private:
		Vector2 position;
		Vector2 scale;
		float angle;
		float rotation;
		Vector2 anchor;
		float width;
		float height;
		TransformMatrix2D transformMatrix;
		Vector2 worldPosition;
		Vector2 worldScale;
		float worldRotation;
		Rect worldBounds;
		float alpha;
		float worldAlpha;
		bool transformChanged;
		bool visible;
		bool isStatic;
		Material* material;
		GameObject* parent;
		std::string name;
		Array<GameObject*> children;
		Array<Component*> components;
	};
}

