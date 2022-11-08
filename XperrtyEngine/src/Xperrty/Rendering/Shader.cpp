#include "xppch.h"
#include "Shader.h"
#include <iostream>
#include <fstream>
#include "glad/glad.h"
static void GLCheckError() {
	while (unsigned int error = glGetError()) {
		XP_ERROR("OPENGL Error {0}", error);
	}
}
namespace Xperrty {
	Shader::Shader(const std::string& shaderSrc) :shaderSrc(shaderSrc), vertSrc(), fragSrc(), shaderType("Shader"), shaderId(-1), uniformLocations()
	{
		XP_TRACE("Parsing Shader Type: {0}", shaderType);
		XP_TRACE("----------------------------------------------------");
		parseShaders();
		initOpenGl();
	}
	void Shader::initOpenGl()
	{
		//ToDo: Move in separate functions...;
		int lastShaderBound;
		glGetIntegerv(GL_CURRENT_PROGRAM, &lastShaderBound);

		auto vertProgram = glCreateShader(GL_VERTEX_SHADER);
		const char* vertCSrc = vertSrc.c_str();
		glShaderSource(vertProgram, 1, &vertCSrc, NULL);
		glCompileShader(vertProgram);
		if (!checkShaderCompileError("Vertex", vertProgram))return;

		auto fragProgram = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragCSrc = fragSrc.c_str();
		glShaderSource(fragProgram, 1, &fragCSrc, NULL);
		glCompileShader(fragProgram);
		if (!checkShaderCompileError("Fragment", fragProgram)) {
			glDeleteProgram(vertProgram);
		}
		auto program = glCreateProgram();

		glAttachShader(program, vertProgram);
		glAttachShader(program, fragProgram);

		glLinkProgram(program);
		glValidateProgram(program);
		shaderId = program;
		bind();
		getUniformLocations();
		XP_TRACE("----------------------------------------------------");

		glDeleteShader(vertProgram);
		glDeleteShader(fragProgram);

		//Restor the last shader
		if (lastShaderBound) glUseProgram(lastShaderBound);
	}

	bool Shader::checkShaderCompileError(const char* shaderType, unsigned int program) {
		int vertResult;
		glGetShaderiv(program, GL_COMPILE_STATUS, &vertResult);
		if (vertResult == GL_FALSE) {
			XP_ERROR("Invalid {0} Shader!", shaderType);

			int messageLength;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &messageLength);
			char* message = new char[messageLength];
			glGetShaderInfoLog(program, messageLength, &messageLength, message);
			XP_ERROR(message);
			glDeleteShader(program);
			delete[] message;
			return false;
		}
		return true;
	}
	void Shader::bind()
	{
		glUseProgram(shaderId);
	}

	//Initializes the attributes for the currently bound buffer.
	void Shader::initAttributesForBuffer() {
		int aPosition = glGetAttribLocation(shaderId, "aPosition");//2 floats
		int aTextureCoords = glGetAttribLocation(shaderId, "aTextureCoords");// 3 floats
		int aColor = glGetAttribLocation(shaderId, "aColor");//4 floats
		int aAlpha = glGetAttribLocation(shaderId, "aAlpha");//1 float

		unsigned int positionOffset = 0;//0								->2 floats
		unsigned int textureCoordsOffset = 2 * sizeof(float);//0 + 2	->3 floats
		unsigned int colorOffset = 5 * sizeof(float);//2 + 3			->4 floats
		unsigned int alphaOffset = 9 * sizeof(float);//5+4				->1 float

		unsigned int stride = getVertSize();
		if (aPosition != -1)glEnableVertexAttribArray(aPosition);
		if (aTextureCoords != -1)glEnableVertexAttribArray(aTextureCoords);
		if (aColor != -1)glEnableVertexAttribArray(aColor);
		if (aAlpha != -1)glEnableVertexAttribArray(aAlpha);
		stride = 40;
		if (aPosition != -1)glVertexAttribPointer(aPosition, 2, GL_FLOAT, false, stride, (void*)positionOffset);
		if (aTextureCoords != -1)glVertexAttribPointer(aTextureCoords, 3, GL_FLOAT, false, stride, (void*)textureCoordsOffset);
		if (aColor != -1)glVertexAttribPointer(aColor, 4, GL_FLOAT, false, stride, (void*)colorOffset);
		if (aAlpha != -1)glVertexAttribPointer(aAlpha,1, GL_FLOAT, false, stride, (void*)alphaOffset);
	}

	void Shader::unbind() {
		//glActiveShaderProgram()
		glUseProgram(0);
	}

	void Shader::setUniform1f(unsigned int location, float a)
	{
		glUniform1f(location, a);
	}

	void Shader::setUniform2f(unsigned int location, float a, float b)
	{
		glUniform2f(location, a, b);
	}

	void Shader::setUniform3f(unsigned int location, float a, float b, float c)
	{
		glUniform3f(location, a, b, c);
	}

	void Shader::setUniform4f(unsigned int location, float a, float b, float c, float d)
	{
		glUniform4f(location, a, b, c, d);
	}

	Dictionary < std::string, Shader*> Shader::shaderSrcMap;
	Shader* Shader::getShader(const std::string& shaderSrc)
	{
		if (!shaderSrcMap.contains(shaderSrc)) shaderSrcMap.add(shaderSrc, new Shader(shaderSrc));
		return shaderSrcMap[shaderSrc];
	}

	Shader* Shader::createShader(const std::string& shaderSrc)
	{
		return new Shader(shaderSrc);
	}

	Shader::~Shader()
	{
		glDeleteProgram(shaderId);
	}
	void Shader::parseShaders()
	{
		std::ifstream shaderFile(shaderSrc);
		std::string line;
		bool fragmentSrc = false;
		//ToDo: change this... maybe support for other shader types
		//ToDo: also please fix this string concat...

		while (std::getline(shaderFile, line)) {
			if (line.find("<Fragment>") != std::string::npos) fragmentSrc = true;
			else if (!fragmentSrc) vertSrc.append(line + "\n");
			else if (fragmentSrc) fragSrc.append(line + "\n");
			//Searching for uniforms
			if (line.find("uniform") != std::string::npos) {
				//It's not a texture
				if (line.find("sampler2D") == std::string::npos) {
					//ToDo: clean this mess
					//--
					size_t pos = 0;
					size_t lastPos = 0;
					std::string uniformDeclaration;
					int nonEmpty = 0;
					if ((pos = line.find(";")) != std::string::npos) {
						uniformDeclaration = line.substr(0, pos);
						std::string token;
						while ((pos = uniformDeclaration.find(" ")) != std::string::npos) {
							token = uniformDeclaration.substr(0, pos);
							if (token.size() != 0)nonEmpty++;
							//We found our uniform name;
							if (nonEmpty == 3) {
								uniformLocations.add(token, 0);
								XP_TRACE("Found Uniform mid string -{0}- len {1} ", token, token.size());
								break;
							}
							uniformDeclaration.erase(0, pos + 1);
							lastPos = pos;
						}
						if (nonEmpty != 3) {
							uniformLocations.add(uniformDeclaration, 0);
							XP_TRACE("Found Uniform at the end of the string -{0}- len {1} ", uniformDeclaration, uniformDeclaration.size());
						}
					}
					//--
				}
			}
		}
	}
	void Shader::getUniformLocations() {
		for each (const auto & kv in uniformLocations)
		{
			unsigned int uniformLocation = glGetUniformLocation(shaderId, kv.first.c_str());
			uniformLocations.add(kv.first, uniformLocation);
			XP_INFO("Found Uniform {0} with location {1}", kv.first, uniformLocation);
		}
	}
}