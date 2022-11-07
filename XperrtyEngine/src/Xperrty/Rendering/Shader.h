#pragma once
namespace Xperrty {

	class Shader
	{
	public:
		Shader(const Shader& other) = delete;

		void initOpenGl();
		void bind();
		void unbind();

		void setUniform1f(unsigned int location, float a);
		void setUniform2f(unsigned int location, float a, float b);
		void setUniform3f(unsigned int location, float a, float b, float c);
		void setUniform4f(unsigned int location, float a, float b, float c, float d);

		void initAttributesForBuffer();

		inline virtual unsigned int getVertSize() { return 10 * sizeof(float); }
		inline unsigned int getShaderId() { return shaderId; };
		inline unsigned int getUniformLocation(const std::string& uniformName) { return uniformLocations[uniformName]; };
		//Creates or returns an already created shader;
		static Shader* getShader(const std::string& shaderSrc);
		//Always creates a new shader.
		static  Shader* createShader(const std::string& shaderSrc);
		~Shader();
	protected:
		Shader(const std::string& shaderSrc);
		std::string shaderSrc;
		std::string vertSrc;
		std::string fragSrc;
		std::string shaderType;
		unsigned int shaderId;
		bool checkShaderCompileError(const char* shaderType, unsigned int program);
		Dictionary<std::string, unsigned int> uniformLocations;
		static Dictionary<std::string, Shader*> shaderSrcMap;
		void getUniformLocations();

		void parseShaders();
	};

}
