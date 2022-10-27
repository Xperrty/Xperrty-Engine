#pragma once
#include "Xperrty/Rendering/Utils/BufferData.h"
namespace Xperrty {

	class Shader
	{
	public:
		Shader(const std::string& shaderSrc);

		void initOpenGl();
		void bind();
		inline unsigned int getShaderId() { return shaderId; };
		~Shader();
	protected:
		std::string shaderSrc;
		std::string vertSrc;
		std::string fragSrc;
		unsigned int shaderId;
		bool checkShaderCompileError(const char* shaderType, unsigned int program);

		void parseShaders();
	};

}
