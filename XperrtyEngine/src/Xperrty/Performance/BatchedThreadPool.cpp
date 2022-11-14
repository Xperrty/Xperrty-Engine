#include "xppch.h"
#include "BatchedThreadPool.h"

namespace Xperrty {
	//Creates A batched Thread pool. Must use start and waitAll otherwise functions will not be called.

	 BatchedThreadPool::BatchedThreadPool(int cores) :threadCount(cores), done(false), activeThreads(threadCount), index(0) {
		callbacks.reserve(2000);
		threads.reserve(threadCount);
		for (int i = 0; i < threadCount; i++)
		{
			dataLoaded.push_back(false);
			threads.push_back(std::thread(&BatchedThreadPool::run, this, i));
			//std::thread::
		}
		waitAll();
	}
	void BatchedThreadPool::start() {
		//XP_INFO("Data size {0}", callbacks.size());
		std::lock_guard<std::mutex> startWorkGuard(startWorkMutex);
		activeThreads = threadCount;
		index = 0;
		for (int i = 0; i < threads.size(); i++)
		{
			dataLoaded[i] = true;

		}
		startWorkCond.notify_all();
	}
	void BatchedThreadPool::waitAll() {
		std::unique_lock<std::mutex> waitLock(waitMutex);
		if (activeThreads != 0 || callbacks.size() != 0) {
			waitCond.wait(waitLock, [&, this] {return activeThreads == 0 && callbacks.size() == 0; });
		}
	}
	BatchedThreadPool::~BatchedThreadPool() {
		done = true;
		start();
		for (int i = 0; i < threadCount; i++)
		{
			threads[i].join();
		}
	}
	void BatchedThreadPool::run(int threadId) {
		while (!done) {
			int myIndex = index.fetch_add(1);
			if (myIndex < callbacks.size()) {
				callbacks[myIndex]();
			}
			else {
				std::unique_lock<std::mutex> startWorkLock(startWorkMutex);
				activeThreads--;
				if (activeThreads == 0) {
					std::lock_guard<std::mutex> waitGuard(waitMutex);
					callbacks.clear();
					waitCond.notify_all();
				}
				dataLoaded[threadId] = false;
				startWorkCond.wait(startWorkLock, [&, this, id = threadId] {return dataLoaded[id]; });
				//startWorkCond.wait(startWorkLock);
			}
		}
	}
}