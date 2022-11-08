#pragma once
#include "Xperrty/Rendering/Shader.h"
namespace Xperrty {
	//Buffer Data for simple sprites: 4 vertices 6 indices for each sprite.
	class BufferData
	{
	public:
		BufferData(unsigned int bufferSize, unsigned int vertexSize, Shader* shader);
		inline char* getVertexBufferData() { return vertexData; }
		inline char* getVertex(unsigned int index) { return (vertexData + vertexSize * 4 * index); }
		inline unsigned int getVertexId() const { return glVertexId; }
		inline unsigned int getIndexId() const { return glIndexId; }
		inline int* getIndexBufferData() { return indexData.data(); }
		void uploadData();
		~BufferData();
		BufferData(const BufferData& other) = delete;
		BufferData(BufferData& other) = delete;
	private:
		unsigned int bufferSize;
		unsigned int vertexSize;
		unsigned int glVertexId;
		unsigned int glIndexId;
		unsigned int glVAOId;
		unsigned int bufferByteSize;
		Shader* shader;
		char* vertexData;
		Array<int> indexData;
	};

}
