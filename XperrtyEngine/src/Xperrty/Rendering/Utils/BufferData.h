#pragma once
namespace Xperrty {
	//Buffer Data for simple sprites: 4 vertices 6 indices for each sprite.
	class BufferData
	{
	public:
		BufferData(unsigned int bufferSize, unsigned int vertexSize );
		inline float* getVertexBufferData() { return vertexData.data(); }
		inline int* getIndexBufferData() { return indexData.data(); }
		inline void addDataToBuffer(float data) { vertexData.push_back(data); }

		~BufferData();
	private:
		unsigned int bufferSize;
		unsigned int vertexSize;
		Array<float> vertexData;
		Array<int> indexData;
	};

}
