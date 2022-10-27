#pragma once
#include "Shader.h"
#include "Utils/Color.h"
#include "Texture.h"
#include "Xperrty/Math/Rect.h"
namespace Xperrty {
	class Renderer2D
	{
	public:
		Renderer2D();



		void renderQuadImmediate(Rect bounds, Shader* shader, Texture* texture, const Color& color);
		void batchRenderQuadImmediate(Rect bounds, Shader* shader, Texture* texture, const Color& color,int count);

		~Renderer2D();

	private:
		Shader* activeShader;

		unsigned int immediate_VAO;
		unsigned int immediate_vertBuffer;
		unsigned int immediate_indexBuffer;
		void generateImmediatBuffers();
	};

}
