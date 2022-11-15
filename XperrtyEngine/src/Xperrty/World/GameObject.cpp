#include "xppch.h"
#include "GameObject.h"
//#include <math.h>
namespace Xperrty {
	GameObject::GameObject() :GameObject("GameObject", Vector2::zero(), Vector2(1.0f, 1.0f), 0, Vector2(0.5f, 0.5f))
	{
	}
	GameObject::GameObject(const std::string& name) :GameObject(name, Vector2::zero(), Vector2(1.0f, 1.0f), 0, Vector2(0.5f, 0.5f))
	{
	}
	GameObject::GameObject(const std::string& name, const Vector2& position) :GameObject(name, position, Vector2(1.0f, 1.0f), 0, Vector2(0.5f, 0.5f))
	{
	}
	GameObject::GameObject(const std::string& name, const Vector2& position, const Vector2& scale) :GameObject(name, position, scale, 0, Vector2(0.5f, 0.5f))
	{
	}
	GameObject::GameObject(const std::string& name, const Vector2& position, const Vector2& scale, float angle) :GameObject(name, position, scale, angle, Vector2(0.5f, 0.5f))
	{
	}
	GameObject::GameObject(const std::string& name, const Vector2& position, const Vector2& scale, float angle, const Vector2& anchor) :name(name), position(position), scale(scale), angle(angle), rotation(toRadians(angle)), alpha(1), anchor(anchor), width(100), height(100), transformChanged(true), visible(false), transformMatrix(scale.x, 0, 0, scale.y, position.x, position.y), worldBounds(0, 0, 0, 0), worldAlpha(1), parent(nullptr), children(), components(), material(nullptr), worldRotation(0), worldScale{ 1,1 },worldPosition{0,0}, isStatic(false)
	{
	}
	void GameObject::updateTransform()
	{
		TransformMatrix2D& pt = parent != nullptr ? parent->transformMatrix : TransformMatrix2D();
		TransformMatrix2D& wt = transformMatrix;
		float sr = sin(rotation);
		float cr = cos(rotation);
		float a = cr * scale.x;
		float b = sr * scale.x;
		float c = -sr * scale.y;
		float d = cr * scale.y;
		float tx = position.x;
		float ty = position.y;
		//if (anchor.x || anchor.y) {
		tx -= anchor.x * a + anchor.y * c;
		ty -= anchor.x * b + anchor.y * d;
		//}
		wt.setA(a * pt.getA() + b * pt.getC());
		wt.setB(a * pt.getB() + b * pt.getD());
		wt.setC(c * pt.getA() + d * pt.getC());
		wt.setD(c * pt.getB() + d * pt.getD());
		wt.setTx(tx * pt.getA() + ty * pt.getC() + pt.getTx());
		wt.setTy(tx * pt.getB() + ty * pt.getD() + pt.getTy());

		worldPosition.x = wt.getTx();
		worldPosition.y = wt.getTy();

		worldScale.x = sqrt(wt.getA() * wt.getA() + wt.getB() * wt.getB());
		worldScale.y = sqrt(wt.getC() * wt.getC() + wt.getD() * wt.getD());
		worldRotation = atan2(-wt.getC(), wt.getD());
		float worldW = width * worldScale.x;
		float worldH = height * worldScale.y;
		worldAlpha = alpha;
		//this.worldBounds.set(this.worldX - worldW * this.anchor.x, this.worldY - worldH * this.anchor.y, worldW, worldH)
		worldBounds = Rect(worldPosition.x - worldW * anchor.x, worldPosition.y - worldH * anchor.y, worldW, worldH);
		//no rotation
		//--------
			//float a = scale.x;
			//float d = scale.y;
			//float tx = position.x - anchor.x * a;
			//float ty = position.y - anchor.y * d;
			//wt.setA(a * pt.getA());
			//wt.setB(a * pt.getB());
			//wt.setC(d * pt.getC());
			//wt.setD(d * pt.getD());
			//wt.setTx(tx * pt.getA() + ty * pt.getC() + pt.getTx());
			//wt.setTy(tx * pt.getB() + ty * pt.getD() + pt.getTy());
		//--------

	}
	void GameObject::setMaterial(Material* m)
	{
		material = m;
	}

	GameObject::~GameObject() {
		for (int i = 0; i < components.size(); i++)
		{
			delete components[i];
		}
	}
}