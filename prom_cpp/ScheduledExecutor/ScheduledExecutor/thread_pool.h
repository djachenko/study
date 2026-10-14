#pragma once

#include <atomic>
#include <functional>
#include <vector>
#include <thread>
#include "threadsafe_queue.h"

using namespace std;

class thread_pool
{
	class join_threads
	{
		vector<thread>& _threads;
	public:
		explicit join_threads(vector<thread>& _threads) :
			_threads(_threads)
		{}

		~join_threads()
		{
			for (unsigned int i = 0; i < _threads.size(); ++i)
			{
				if (_threads[i].joinable()) {
					_threads[i].join();
				}
			}
		}
	};

	atomic<bool> done;
	threadsafe_queue<function<void()>> work_queue;
	vector<thread> threads;
	join_threads joiner;

	void worker_thread()
	{
		while (!done)
		{
			function<void()> task;

			work_queue.wait_and_pop(task);

			task();
		}
	}
public:
	explicit thread_pool(const unsigned int thread_count = thread::hardware_concurrency()) :
		done(false), joiner(threads)
	{
		try
		{
			for (unsigned int i = 0; i < thread_count; ++i)
			{
				threads.push_back(thread(&thread_pool::worker_thread, this));
			}
		}
		catch (...)
		{
			shutdown();

			throw;
		}
	}

	~thread_pool()
	{
		shutdown();
	}

	template<typename FunctionType>
	void submit(FunctionType &&f)
	{
		work_queue.push(std::function<void()>(move(f)));
	}

	void shutdown() {
		done = true;

		for (unsigned int i = 0; i < threads.size(); i++) {
			work_queue.push([](){});
		}
	}
};