#pragma once
#include "Xperrty/Containers/Array.h"
template <typename T>
class ObjectPool
{
public:
	ObjectPool(int chunkSize) :chunkSize(chunkSize), lastPointer(0) {
		//TODO: Check if fragmentation breaks the pool.... Micro optimization.
		//TODO: Implement chunk reduction if not needed.
		freePositions.reserve(32);//2 cache lines 128/4
		memoryChunks.reserve(8);
		allocateNewChunk();
	}
	template<typename... Args>
	T* newObject(Args... args) {
		char* memorySpot = getNextAvailableSpot();
		return new(memorySpot) T(args...);
	}
	void deleteObject(T* object) {
		object->~T();
		int objectIndex = findObjectIndex(object);
		freePositions.push_back(objectIndex);
	}
	inline int getIndex() { return lastPointer; }
	inline int totalChunks() { return memoryChunks.size(); }

	~ObjectPool() {
		//Call destructors of objects.
		for (int i = 0; i < lastPointer; i++)
		{
			if (freePositions.contains(i)) continue;
			int chunk = i / chunkSize;
			int indexInChunk = i % chunkSize;
			T* objectPtr = (T*)(memoryChunks[chunk] + indexInChunk * sizeof(T));
			objectPtr->~T();
		}

		//Free all the chunks.
		for (int i = 0; i < memoryChunks.size(); i++)
		{
			free(memoryChunks[i]);
		}
		XP_WARN("Object Pool Deleted!");
	}

private:
	inline char* getNextAvailableSpot() {
		int indexInPool = lastPointer;
		if (freePositions.size() != 0) {
			int lastPosition = freePositions.back();
			freePositions.pop_back();
			indexInPool = lastPosition;
		}
		else {
			lastPointer++;
		}
		//if (lastPointer > chunkSize) {
		int chunkNr = indexInPool / chunkSize;
		int indexInChunk = indexInPool % chunkSize;
		//We need to allocate another chunk;
		while (chunkNr >= memoryChunks.size()) {
			allocateNewChunk();
		}

		return memoryChunks[chunkNr] + indexInChunk * sizeof(T);
		//}
	}
	void allocateNewChunk() {
		memoryChunks.push_back((char*)malloc(sizeof(T) * chunkSize));
	}
	int findObjectIndex(T* object) {
		int chunkSizeInBytes = chunkSize * sizeof(T);
		char* objectCharPtr = (char*)object;
		for (int i = 0; i < memoryChunks.size(); i++)
		{
			char* chunk = memoryChunks[i];
			char* chunkOffset =(char*) (objectCharPtr - chunk);
			//We found the chunk
			if (objectCharPtr >chunk && (int)chunkOffset <= chunkSizeInBytes) {
				return i * chunkSize + (int)chunkOffset / sizeof(T);
			}
		}
		return 0;
	}

	Array<char*> memoryChunks;
	Array<int> freePositions;
	int lastPointer;
	int chunkSize;

};
