#include "xppch.h"
#include "BufferData.h"
#include "glad/glad.h"
#
namespace Xperrty {
	BufferData::BufferData(unsigned int bufferSize, unsigned int vertexSize, Shader* shader) :bufferSize(bufferSize), vertexSize(vertexSize), vertexData(), indexData(), glVertexId(0), glIndexId(0), bufferByteSize(0)
	{
		XP_ERROR("Created Buffer Data! {0}", vertexSize);
		bufferByteSize = bufferSize * vertexSize * 4;
		vertexData = (char*)malloc(bufferByteSize);
		indexData.reserve(bufferSize * 6);

		for (int i = 0; i < bufferSize; i++)
		{
			int i6 = i * 6;
			indexData.push_back(i6 + 0);
			indexData.push_back(i6 + 1);
			indexData.push_back(i6 + 2);
			indexData.push_back(i6 + 2);
			indexData.push_back(i6 + 3);
			indexData.push_back(i6 + 0);
		}
		//Generating Buffers
		glGenVertexArrays(1, &glVAOId);
		glBindVertexArray(glVAOId);

		glGenBuffers(1, &glVertexId);
		glBindBuffer(GL_ARRAY_BUFFER, glVertexId);
		glBufferData(GL_ARRAY_BUFFER, bufferByteSize, 0, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &glIndexId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIndexId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize * sizeof(int) * 6, indexData.data(), GL_DYNAMIC_DRAW);

		//Setting up Attribs
		shader->initAttributesForBuffer();
		//vec2 i_position;
		//vec4 i_color;
		//vec2 i_textureCoords;
		
	}

	void BufferData::uploadData() {
		//Bind vertex Buffer
		glBindVertexArray(glVAOId);
		//glBindBuffer(GL_ARRAY_BUFFER, glVertexId);
		glBufferData(GL_ARRAY_BUFFER, bufferByteSize, vertexData, GL_DYNAMIC_DRAW);

		//Bind index buffer.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIndexId);
		//No point reuploading data... We use 6 indices every time for a sprite.
	}

	BufferData::~BufferData()
	{
	}
}