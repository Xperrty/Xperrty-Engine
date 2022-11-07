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
	GameObject::GameObject(const std::string& name, const Vector2& position, const Vector2& scale, float angle, const Vector2& anchor) :name(name), position(position), scale(scale), angle(angle), rotation(toRadians(angle)), alpha(1), anchor(anchor), transformChanged(true), visible(false), transformMatrix(scale.x, 0, 0, scale.y, position.x, position.x), worldAlpha(1), parent(nullptr), children(), components(), material(nullptr)
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
		float& tx = position.x;
		float& ty = position.y;
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

		//out of bounds optimizations
		//if (material != nullptr) material->updateVertices(this);
		//this.worldPosition.set(wt.tx, wt.ty);
		//this.worldScale.set(Math.sqrt(wt.a * wt.a + wt.b * wt.b), Math.sqrt(wt.c * wt.c + wt.d * wt.d));
		//this.worldRotation = Math.atan2(-wt.c, wt.d);
		//if (this.texture) {
		//    var w = this.texture.width * this.scale.x;
		//    var h = this.texture.height * this.scale.y;
		//    var worldW = this.texture.width * this.worldScale.x;
		//    var worldH = this.texture.height * this.worldScale.y;
		//    this.bounds.set(this.x - w * this.anchor.x, this.y - h * this.anchor.y, w, h);
		//    this.worldBounds.set(this.worldX - worldW * this.anchor.x, this.worldY - worldH * this.anchor.y, worldW, worldH);
		//    this.outOfBounds = this.worldBounds.right < 0 || this.worldBounds.bottom < 0 || this.worldBounds.left > this.game.scale.renderResolution.x || this.worldBounds.top > this.game.scale.renderResolution.y;
	}
	void GameObject::setMaterial(Material* m)
	{
		material = m;
	}
}