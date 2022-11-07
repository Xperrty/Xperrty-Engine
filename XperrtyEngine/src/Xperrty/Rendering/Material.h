#pragma once
#include "Xperrty/Rendering/Texture.h"
#include "Xperrty/Rendering/Shader.h"
//#include "Xperrty/World/Gameo"
namespace Xperrty {
	//Check: maybe this might break something
	class GameObject;
	struct MaterialVertexData {
		float position[2];
		float UV[3];
		float colors[4];
		float alpha;
		MaterialVertexData() :position{ 0,0 }, UV{ 0,0,0 }, colors{ 1,1,1,1 }, alpha(1) {}
		//ToDO:Add constructor for colors as well...
		MaterialVertexData(float x, float y, float u, float v, float alpha, int texId) :position{ x,y }, UV{ u,v,(float)texId }, colors{ 1,1,1,1 }, alpha(alpha) {}
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
