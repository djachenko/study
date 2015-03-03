package ru.nsu.fit.djachenko.javaperfomance.сфы;

import java.util.concurrent.locks.ReentrantLock;

public class UtilConcurrent extends ConcurrentIncrementable
{
	@Override
	public void increment()
	{
		ReentrantLock lock = new ReentrantLock();

		lock.lock();

		inc();

		lock.unlock();
	}
}
