#pragma once
#include "Xperrty/Containers/Array.h"
namespace Xperrty {

	template <typename T>
	class ObjectPool
	{
	public:
		ObjectPool(int chunkSize) :chunkSize(chunkSize), lastPointer(0),debug(false) {
			//TODO: Check if fragmentation breaks the pool performance.... Micro optimization.
			//TODO: Implement chunk reduction if not needed.
			freePositions.reserve(32);//2 cache lines 128/4
			memoryChunks.reserve(2);
			allocateNewChunk();
		}
		template<typename... Args>
		T* newObject(Args... args) {
			
			char* memorySpot = getNextAvailableSpot();
			if (debugAllocArray.contains(memorySpot)) XP_ERROR("TRYING TO INSTANTIATE THE SAME MEMORY SPOT TWICE!");
			debugAllocArray.push_back(memorySpot);
			return new(memorySpot) T(args...);
		}
		void deleteObject(T* object) {
			return;
			if (debugAllocArray.contains((char*)object)) {
				debugAllocArray.remove((char*)object);

			}
			else XP_ERROR(" TRYING TO REMOVE AN OBJECT TWICE!");

			int objectIndex = findObjectIndex(object);
			object->~T();
			freePositions.push_back(objectIndex);
			//if (debug) XP_INFO("Deleted object at memLocation {0} and freed index {1}", (unsigned long long)object, objectIndex);
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
		bool debug;
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
			//if (debug) XP_INFO("Created object at memLocation {0} Chunk{1} Index in Chunk{2} ", (unsigned long long)(memoryChunks[chunkNr] + indexInChunk * sizeof(T)),chunkNr,indexInChunk);

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
				char* chunkOffset = (char*)(objectCharPtr - chunk);
				//We found the chunk
				if (objectCharPtr >= chunk && (int)chunkOffset < chunkSizeInBytes) {
					return i * chunkSize + (int)chunkOffset / sizeof(T);
				}
			}
			findObjectIndexDebug(object);
			return -1;
		}
		int findObjectIndexDebug(T* object) {
			int chunkSizeInBytes = chunkSize * sizeof(T);
			char* objectCharPtr = (char*)object;
			for (int i = 0; i < memoryChunks.size(); i++)
			{
				char* chunk = memoryChunks[i];
				char* chunkOffset = (char*)(objectCharPtr - chunk);
				XP_WARN("Chunk {0}, ChunkOffset{1}, ChunkSize{2}, ObjectCharPtr{3}, IntCHunkOffset{4}", (long long)chunk, (long long)chunkOffset, chunkSize, (long long)objectCharPtr, (int)chunkOffset);
				//We found the chunk
				if (objectCharPtr >= chunk && (int)chunkOffset <= chunkSizeInBytes) {
					return i * chunkSize + (int)chunkOffset / sizeof(T);
				}
			}
			return -1;
		}

		Array<char*> memoryChunks;
		Array<char*> debugAllocArray;
		Array<int> freePositions;
		int lastPointer;
		int chunkSize;

	};
}
