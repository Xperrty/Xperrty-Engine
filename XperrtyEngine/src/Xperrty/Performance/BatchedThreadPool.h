#pragma once
namespace Xperrty {
	class BatchedThreadPool
	{
	public:
		//Creates A batched Thread pool. Must use start and waitAll otherwise functions will not be called.
		BatchedThreadPool(int cores);
		//Adds a callback to the queue. *NOT thread safe. DO NOT queue items between start and waitAll!*
		inline void queue(const std::function<void()>& func) { callbacks.push_back(func); }
		//Begins the processing of the queue.
		void start();
		//Waits for all the threads to finish work (Blocks calling thread).
		void waitAll();

		//Returns the worker count in this pool.
		inline unsigned int getWorkerCount() { return static_cast<unsigned int>(threads.size()); }
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