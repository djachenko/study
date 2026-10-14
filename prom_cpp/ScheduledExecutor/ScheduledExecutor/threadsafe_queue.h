#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

using namespace std;

template<typename T>
class threadsafe_queue
{
private:
	mutable mutex mut;
	queue<T> data_queue;
	condition_variable condition;
public:
	threadsafe_queue()
	{}

	void push(T new_value)
	{
		lock_guard<mutex> lk(mut);

		data_queue.push(std::move(new_value));
		
		condition.notify_one();
	}

	void wait_and_pop(T& value)
	{
		unique_lock<mutex> uniqueLock(mut);
		
		condition.wait(uniqueLock, [this]{ return !data_queue.empty(); });
		
		value = std::move(data_queue.front());

		data_queue.pop();
	}
};
