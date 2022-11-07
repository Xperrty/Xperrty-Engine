#pragma once
namespace Xperrty {
	class BatchedThreadPool
	{
	public:
		//Creates A batched Thread pool. Must use start and waitAll otherwise functions will not be called.
		BatchedThreadPool(int cores);
		//Adds a callback to the queue. *NO MT*
		inline void queue(const std::function<void()>& func) { callbacks.push_back(func); }
		void start();
		void waitAll();
		BatchedThreadPool(const BatchedThreadPool& other) = delete;
		~BatchedThreadPool();

	private:
		std::vector<std::function<void()>> callbacks;
		std::mutex startWorkMutex;
		std::mutex waitMutex;
		std::condition_variable startWorkCond;
		std::condition_variable waitCond;
		std::atomic<int> index;
		int threadCount;
		int activeThreads;
		bool done;
		std::vector<bool> dataLoaded;
		std::vector<std::thread> threads;

		void run(int threadId);
	};

}