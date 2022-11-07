#include "xppch.h"
#include "BufferData.h"
#include "glad/glad.h"
namespace Xperrty {
	BufferData::BufferData(unsigned int bufferSize, unsigned int vertexSize) :bufferSize(bufferSize), vertexSize(vertexSize), vertexData(), indexData(), glVertexId(0), glIndexId(0), bufferByteSize(0)
	{
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


		glGenBuffers(1, &glVertexId);
		glBindBuffer(GL_ARRAY_BUFFER, glVertexId);
		glBufferData(GL_ARRAY_BUFFER, bufferByteSize, 0, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &glIndexId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIndexId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize * sizeof(int) * 6, indexData.data(), GL_DYNAMIC_DRAW);
	}

	void BufferData::uploadData() {
		//Bind vertex Buffer
		glBindBuffer(GL_ARRAY_BUFFER, glVertexId);
		glBufferData(GL_ARRAY_BUFFER, bufferByteSize, &vertexData, GL_DYNAMIC_DRAW);

		//Bind index buffer.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIndexId);
		//No point reuploading data... We use 6 indices every time for a sprite.
	}

	BufferData::~BufferData()
	{
	}
}