#pragma once
#include "Xperrty/Rendering/Texture.h"
#include "Xperrty/Rendering/Shader.h"
//#include "Xperrty/World/Gameo"
namespace Xperrty {
	//Check: maybe this might break something
	class GameObject;
	struct MaterialVertexData {
		float position[2];
		float UV[2];
		float alpha;
		int texId;
		MaterialVertexData() :position{ 0,0 }, UV{ 0,0 }, alpha(1), texId(0) {}
		MaterialVertexData(float x, float y, float u, float v, float alpha, int texId) :position{ x,y }, UV{ u,v }, alpha(alpha), texId(texId) {}
	};
	class Material
	{
	public:
		Material(Shader* shader, Texture* texture, GameObject* object);

		//Preallocated memory location to fit 4 Vertices.
		void setVerticesMemLocation(MaterialVertexData* location);
		void updateVertices();
		void createVertices();
		void uploadUniforms();
		inline int getVertexSize() const { return sizeof(MaterialVertexData); }
		inline Shader* getShader() { return shader; }
	private:
		Shader* shader;
		Texture* texture;
		GameObject* gameObject;
		MaterialVertexData* memLocation;
		MaterialVertexData* bl;
		MaterialVertexData* br;
		MaterialVertexData* tr;
		MaterialVertexData* tl;
	};

	

}
