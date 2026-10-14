#pragma once

#include <chrono>
#include <future>
#include <set>
#include "thread_pool.h"


using namespace std;
using namespace chrono;


class Task {
	bool _periodic;
	milliseconds _period;

	static int count;

	function<void()> _func;
public:
	class comp {
	public:
		bool operator()(const Task &a, const Task &b) const {
			return a.nextStart < b.nextStart;
		}
	};

	steady_clock::time_point nextStart;
	int id;

	explicit Task(const function<void()> &func,
		const milliseconds &delay, 
		const milliseconds &period = milliseconds(0))
		: _periodic(period.count() > 0), 
		_period(period), 
		_func(func), 
		nextStart(steady_clock::now() + delay), 
		id(count++) {}

	bool isPeriodic() const {
		return _periodic;
	}

	const milliseconds& period() const {
		return _period;
	}


	const function<void()>& func() const {
		return _func;
	}
};

int Task::count = 0;

class ScheduledExecutor {

public:
	typedef int TaskID;

private:
	thread_pool threadPool;

	atomic<bool> done;
	set<Task, Task::comp> taskSet;
	
	mutex notifierMutex;
	condition_variable notifierVariable;
	thread notifier;

	void notifierThread() {
		while (!done)
		{
			unique_lock<mutex> lock(notifierMutex);

			auto taskIterator = taskSet.begin();
			
			if (taskIterator != taskSet.end()) {
				auto now = steady_clock::now();
				auto nextStart = taskIterator->nextStart;

				if (nextStart < now) {
					auto task = *taskIterator;

					taskSet.erase(taskIterator);

					threadPool.submit(task.func());

					if (task.isPeriodic()) {
						task.nextStart += task.period();

						taskSet.insert(move(task));
					}
				}
				else {
					auto delay = nextStart - now;

					notifierVariable.wait_for(lock, delay);
				}
			}
			else {
				notifierVariable.wait(lock);
			}
		}
	}

	TaskID enqueue_task(const Task &&task) {
		auto ret = task.id;

		unique_lock<mutex> lock(notifierMutex);

		taskSet.insert(move(task));

		notifierVariable.notify_all();

		return ret;
	}
public:
	explicit ScheduledExecutor(const size_t &threadPoolSize = 4)
	:threadPool(threadPoolSize),
	done(false),
	notifier(&ScheduledExecutor::notifierThread, this){}

	virtual ~ScheduledExecutor() {
		shutdown();

		threadPool.shutdown();

		notifier.join();
	}	

	ScheduledExecutor(ScheduledExecutor const &) = delete;
	ScheduledExecutor(ScheduledExecutor &&) = delete;
	ScheduledExecutor &operator=(ScheduledExecutor const &) = delete;
	ScheduledExecutor &operator=(ScheduledExecutor &&) = delete;

	template<typename Fn>
	TaskID ScheduleDelayedTask(Fn && fn, milliseconds delay = milliseconds(0)) {
		Task task(fn, delay);

		return enqueue_task(move(task));
	}

	template<typename Fn>
	TaskID SchedulePeriodicTask(Fn &&fn, milliseconds delay, milliseconds period) {
		Task task(fn, delay, period);

		return enqueue_task(move(task));
	}

	template<typename Fn>
	auto ScheduleLazyTask(Fn fn) -> future<typename result_of<Fn>::type> {
		return async(launch::deferred, fn);
	}

	void CancelPeriodicTask(TaskID const & id) {
		unique_lock<mutex> lock(notifierMutex);

		for (auto i = taskSet.begin(); i != taskSet.end();) {
			if (i->id == id) {
				i = taskSet.erase(i);
			}
			else {
				i++;
			}
		}

		notifierVariable.notify_all();
	}

	void shutdown() {
		done = true;

		notifierVariable.notify_all();
	}
};