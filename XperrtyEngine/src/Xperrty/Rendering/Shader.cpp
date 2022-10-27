#include "xppch.h"
#include "Shader.h"
#include <iostream>
#include <fstream>
#include "glad/glad.h"

namespace Xperrty {
	Shader::Shader(const std::string& shaderSrc) :shaderSrc(shaderSrc), vertSrc(), fragSrc(), shaderId(-1)
	{
		parseShaders();
	}
	void Shader::initOpenGl()
	{
		//ToDo: Move in separate functions...;
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


		//glDeleteShader(vertProgram);
		//glDeleteShader(fragProgram);
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
	}

	Shader::~Shader()
	{
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
		}
	}
}