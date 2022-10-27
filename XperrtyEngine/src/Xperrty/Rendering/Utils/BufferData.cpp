#include "xppch.h"
#include "BufferData.h"

namespace Xperrty {
	BufferData::BufferData(unsigned int bufferSize,unsigned int vertexSize) :bufferSize(bufferSize), vertexSize(vertexSize),vertexData(),indexData()
	{
		vertexData.reserve(bufferSize * vertexSize*4);
		indexData.reserve(bufferSize * 6);
		//ToDo:this is a massive performance hit... multithreaded please...

		for (int i = 0; i < bufferSize; i++)
		{
			int i4 = i * 4;
			indexData.push_back(i4 + 0);
			indexData.push_back(i4 + 1);
			indexData.push_back(i4 + 2);
			indexData.push_back(i4 + 2);
			indexData.push_back(i4 + 3);
			indexData.push_back(i4 + 0);
		}
	}
	BufferData::~BufferData()
	{
	}
}