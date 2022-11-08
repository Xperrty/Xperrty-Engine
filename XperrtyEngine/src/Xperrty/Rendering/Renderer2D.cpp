#include "xppch.h"
#include "Renderer2D.h"
//#include "glad/glad.h"
#include "Xperrty/Math/Rect.h"
#include "Cameras/Camera.h"
#include "glad/glad.h"
#include <filesystem>
//#include ""
static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}
static void GLCheckError() {
	while (unsigned int error = glGetError()) {
		XP_ERROR("OPENGL Error {0}", error);
	}
}
namespace Xperrty {

	Renderer2D* Renderer2D::instance;
	Renderer2D::Renderer2D() :immediate_VAO(0), immediate_indexBuffer(0), immediate_vertBuffer(0)
	{
		//ToDo:Please remove this...
		activeShader = Shader::getShader("E:\\Projects\\Git\\Xperrty-Engine\\XperrtyEngine\\src\\Xperrty\\Rendering\\Shaders\\MultiTextureShader.glsl");
		//activeShader = Shader::getShader(std::filesystem::current_path().string() + "\\..\\..\\..\\XperrtyEngine\\src\\Xperrty\\Rendering\\Shaders\\MultiTextureShader.glsl");
		instance = this;
		activeShader->initOpenGl();
		generateImmediatBuffers();//DEBUG
		glUseProgram(activeShader->getShaderId());

		glViewport(0, 0, Window::instance->getWidth(), Window::instance->getHeight());
		int maxTextures = 0;
		glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS, &maxTextures);
		XP_INFO("Texture slots available: {0}", maxTextures);
		
	}
	void Renderer2D::renderBatch(Batch& batch) {
		Shader* batchShader = batch.getMaterial()->getShader();
		if (batchShader == lastUsedShader) {

		}
		else {
			lastUsedShader = batchShader;
		}
		lastUsedShader->bind();
		batch.getMaterial()->uploadUniforms();
		BufferData& buffer = batch.getBufferData();
		buffer.uploadData();

		glDrawElements(GL_TRIANGLES, batch.size()*6, GL_UNSIGNED_INT, nullptr);
		//batch.
		//glBindVertexArray(buffer.)
	}

	void Renderer2D::renderQuadImmediate(Rect bounds, Shader* shader, Texture* texture, const Color& color)
	{
		GLClearError();
		//ToDo: Remove all this, it is testing code!
		float vertices[40]{
			bounds.getX(),bounds.getBot(),0,0,0, color.getComponents()[0], color.getComponents()[1], color.getComponents()[2], color.getComponents()[3],1,
			bounds.getRight(),bounds.getBot(),1,0,0, color.getComponents()[0], color.getComponents()[1], color.getComponents()[2], color.getComponents()[3],1,
			bounds.getRight(),bounds.getY(),1,1,0, color.getComponents()[0], color.getComponents()[1], color.getComponents()[2], color.getComponents()[3],1,
			bounds.getX(),bounds.getY(),0,1,0, color.getComponents()[0], color.getComponents()[1], color.getComponents()[2], color.getComponents()[3],1
		};

		unsigned int indices[6]{
			0,1,2,
			2,3,0
		};
		glBindVertexArray(immediate_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, immediate_vertBuffer);


		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 40, vertices, GL_DYNAMIC_DRAW);
		//glBindTe

		activeShader->initAttributesForBuffer();
		glUniform2f(glGetUniformLocation(activeShader->getShaderId(), ("uResolution")), Window::instance->getWidth(), Window::instance->getHeight());
		glUniform2f(glGetUniformLocation(activeShader->getShaderId(), ("uProjectionVector")), Window::instance->getWidth() / 2, -Window::instance->getHeight() / 2);
		glUniform3f(glGetUniformLocation(activeShader->getShaderId(), ("uCameraPosition")), Camera::getActiveCamera()->getBounds().getX(), Camera::getActiveCamera()->getBounds().getY(), Camera::getActiveCamera()->getScale());

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_DYNAMIC_DRAW);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		GLCheckError();
		//GLCheckError();
	}

	void Renderer2D::batchRenderQuadImmediate(Rect bounds, Shader* shader, Texture* texture, const Color& color, int count)
	{
		Array<float> arr;
		Array<float> ind;
		arr.reserve(1000 * 32);
		ind.reserve(1000 * 6);
		//ToDo: Remove all this, it is testing code!
		for (int i = 0; i < 1000; i++)
		{
			arr.push_back(bounds.getX());
			arr.push_back(bounds.getBot());
			arr.push_back(color.getComponents()[0]);
			arr.push_back(color.getComponents()[1]);
			arr.push_back(color.getComponents()[2]);
			arr.push_back(color.getComponents()[3]);
			arr.push_back(0);
			arr.push_back(0);
			arr.push_back(bounds.getRight());
			arr.push_back(bounds.getBot());
			arr.push_back(color.getComponents()[0]);
			arr.push_back(color.getComponents()[1]);
			arr.push_back(color.getComponents()[2]);
			arr.push_back(color.getComponents()[3]);
			arr.push_back(1);
			arr.push_back(0);
			arr.push_back(bounds.getRight());
			arr.push_back(bounds.getY());
			arr.push_back(color.getComponents()[0]);
			arr.push_back(color.getComponents()[1]);
			arr.push_back(color.getComponents()[2]);
			arr.push_back(color.getComponents()[3]);
			arr.push_back(1);
			arr.push_back(1);
			arr.push_back(bounds.getX());
			arr.push_back(bounds.getY());
			arr.push_back(color.getComponents()[0]);
			arr.push_back(color.getComponents()[1]);
			arr.push_back(color.getComponents()[2]);
			arr.push_back(color.getComponents()[3]);
			arr.push_back(0);
			arr.push_back(1);
		}
		/*float vertices[32]{
			bounds.getX(),bounds.getBot(), color.getComponents()[0], color.getComponents()[1], color.getComponents()[2], color.getComponents()[3],0,0,
			bounds.getRight(),bounds.getBot(), color.getComponents()[0], color.getComponents()[1], color.getComponents()[2], color.getComponents()[3],1,0,
			bounds.getRight(),bounds.getY(), color.getComponents()[0], color.getComponents()[1], color.getComponents()[2], color.getComponents()[3],1,1,
			bounds.getX(),bounds.getY(), color.getComponents()[0], color.getComponents()[1], color.getComponents()[2], color.getComponents()[3],0,1
		};*/
		for (int i = 0; i < 1000; i++)
		{
			int i3 = i * 4;
			ind.push_back(i3 + 0);
			ind.push_back(i3 + 1);
			ind.push_back(i3 + 2);
			ind.push_back(i3 + 2);
			ind.push_back(i3 + 3);
			ind.push_back(i3 + 0);
		}

		/*unsigned int indices[6]{
			0,1,2,
			2,3,0
		};*/
		glBindVertexArray(immediate_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, immediate_vertBuffer);


		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32000, arr.data(), GL_STATIC_DRAW);
		//glBindTe

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)8);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6*1000, ind.data(), GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}


	Renderer2D::~Renderer2D()
	{
	}

	void Renderer2D::generateImmediatBuffers()
	{
		glGenVertexArrays(1, &immediate_VAO);
		glBindVertexArray(immediate_VAO);

		glGenBuffers(1, &immediate_vertBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, immediate_vertBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32000, 0, GL_STATIC_DRAW);

		glGenBuffers(1, &immediate_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, immediate_indexBuffer);
	}

}
