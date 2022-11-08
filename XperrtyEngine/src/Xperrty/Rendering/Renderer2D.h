#pragma once
#include "Utils/Color.h"
#include "Xperrty/Rendering/Material.h"
#include "Xperrty/Math/Rect.h"
#include "Xperrty/Rendering/Window.h"
#include "Batch.h"
namespace Xperrty {
	class Renderer2D
	{
	public:
		Renderer2D();
		static Renderer2D* instance;
		void renderBatch(Batch& batch);

		void renderQuadImmediate(Rect bounds, Shader* shader, Texture* texture, const Color& color);

		~Renderer2D();

	private:
		Shader* activeShader;
		Shader* lastUsedShader;
		unsigned int immediate_VAO;
		unsigned int immediate_vertBuffer;
		unsigned int immediate_indexBuffer;
		void generateImmediatBuffers();
	};

}
