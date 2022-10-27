#pragma once
#include "Xperrty/Rendering/Texture.h"
#include "Xperrty/Rendering/Shader.h"
//#include "Xperrty/World/Gameo"
namespace Xperrty {
	//Check: maybe this might break something
	class GameObject;
	class Material
	{
	public:
		Material(Shader* shader, Texture* texture);

		void setVerticesMemLocation(float* location);
		void updateVertices(GameObject* gameObject);
	private:
		Shader* shader;
		Texture* texture;
		float* memLocation;
	};

}
